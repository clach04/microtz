#!/usr/bin/env python3
"""Generate C tests for microtz library - offset tests only."""

import sys

from posix_tz import parse_tz, mktime, localtime  # from https://github.com/clach04/py-posix_tz


TIMEZONES = {
    'CST-8': 'china',
    'IST-5:30': 'india',
    'CET-1CEST,M3.5.0,M10.5.0/3:00:00': 'germany',
    'UTC': 'utc',
    'GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00': 'uk',
    'EST5EDT,M3.2.0,M11.1.0': 'usa_newyork',
    'CST6CDT,M3.2.0,M11.1.0': 'usa_texas',
    'PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00': 'usa_losangeles',
}

TEST_FILE = 'test_microtz.c'

TEST_TIMESTAMPS = [
    # 2026 Interesting Los Angeles winter to DST transition period
    ("2026-03-08 09:00:00", 'LA_winter_to_DST'),
    ("2026-03-08 09:59:59", 'LA_winter_to_DST'),
    ("2026-03-08 10:00:00", 'LA_winter_to_DST'),
    ("2026-03-08 11:00:00", 'LA_winter_to_DST'),

    # 2026 Interesting Los Angeles DST over transition period
    ("2026-11-01 07:00:00", 'London_DST_to_winter'),
    ("2026-11-01 08:00:00", 'London_DST_to_winter'),
    ("2026-11-01 08:59:59", 'London_DST_to_winter'),
    ("2026-11-01 09:00:00", 'London_DST_to_winter'),
    ("2026-11-01 10:00:00", 'London_DST_to_winter'),


    # 2026 Interesting London winter to DST transition period
    ("2026-03-29 00:00:00", 'London_winter_to_DST'),
    ("2026-03-29 00:59:59", 'London_winter_to_DST'),
    ("2026-03-29 01:00:00", 'London_winter_to_DST'),
    ("2026-03-29 01:59:59", 'London_winter_to_DST'),
    ("2026-03-29 02:00:00", 'London_winter_to_DST'),
    ("2026-03-29 02:59:59", 'London_winter_to_DST'),
    ("2026-03-29 03:00:00", 'London_winter_to_DST'),
    ("2026-03-29 04:00:00", 'London_winter_to_DST'),

    # 2026 Interesting London DST over transition period
    ("2026-10-24 22:59:59", 'London_DST_to_winter'),
    ("2026-10-24 23:00:00", 'London_DST_to_winter'),
    ("2026-10-24 23:59:59", 'London_DST_to_winter'),
    ("2026-10-25 00:00:00", 'London_DST_to_winter'),
    ("2026-10-25 01:00:00", 'London_DST_to_winter'),
    ("2026-10-25 02:00:00", 'London_DST_to_winter'),
]


def timestamp_to_c_args(ts_str):
    ts_str = ts_str.replace('-', ' ').replace(':', ' ')
    return tuple(map(int, ts_str.split()))


def timestamp_to_tuple(ts_str):
    ts_str = ts_str.replace('-', ' ').replace(':', ' ')
    return tuple(map(int, ts_str.split()))


def generate_offset_test(tz_string, tz_name, ts_str, season, expected_offset):
    args = timestamp_to_c_args(ts_str)
    return '''UTEST(microtz, %s_offset_%s) {
    microtz_info info = microtz_parse("%s");
    time_t ts = mktime_utc(%d, %d, %d, %d, %d, %d);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(%d, off);
}''' % (tz_name, season, tz_string, args[0], args[1], args[2], args[3], args[4], args[5], expected_offset)


def generate_tests():
    tests = []
    for tz_string, tz_name in TIMEZONES.items():
        parsed = parse_tz(tz_string)
        for ts_str, season in TEST_TIMESTAMPS:
            t = timestamp_to_tuple(ts_str)
            ts = mktime(t)
            tt = localtime(ts, parsed)
            is_dst = tt[8]
            if is_dst:
                expected_offset = (parsed.offset + 3600) // 60
            else:
                expected_offset = parsed.offset // 60
            season += '_%04d_%02d_%02d__%02d_%02d_%02d' % (t[0], t[1], t[2], t[3], t[4], t[5])
            tests.append(generate_offset_test(tz_string, tz_name, ts_str, season, expected_offset))
    return '\n\n'.join(tests)


def update_test_file():
    with open(TEST_FILE, 'r') as f:
        content = f.read()
    marker = 'UTEST_MAIN()'
    idx = content.find(marker)
    if idx == -1:
        print("Error: UTEST_MAIN() not found in %s" % TEST_FILE)
        return
    new_tests = generate_tests()
    new_content = content[:idx] + new_tests + '\n\n' + content[idx:]
    preview = True
    #preview = False
    if preview:
        print('%s' % (new_content,))
    else:
        with open(TEST_FILE, 'w') as f:
            f.write(new_content)
    print("Updated %s" % TEST_FILE)


if __name__ == '__main__':
    update_test_file()
