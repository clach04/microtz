#include "utest.h"
#include "microtz.h"
#include <string.h>

UTEST(microtz, usa_losangeles_parse_name) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    ASSERT_STREQ("PST", info.name);
}

UTEST(microtz, usa_losangeles_parse_offset) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    ASSERT_EQ(-8 * 60 * 60, info.offset);
}

UTEST(microtz, usa_losangeles_parse_dst_name) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    ASSERT_STREQ("PDT", info.dst_name);
}

UTEST(microtz, usa_losangeles_has_dst) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    ASSERT_TRUE(info.has_dst);
}

UTEST(microtz, usa_losangeles_offset_summer) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 6, 28, 19, 44, 14);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-7 * 60, off);
}

UTEST(microtz, usa_losangeles_offset_winter) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2025, 1, 1, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-8 * 60, off);
}

UTEST(microtz, utc_parse_name) {
    microtz_info info = microtz_parse("UTC");
    ASSERT_STREQ("UTC", info.name);
}

UTEST(microtz, utc_parse_offset) {
    microtz_info info = microtz_parse("UTC");
    ASSERT_EQ(0, info.offset);
}

UTEST(microtz, utc_no_dst) {
    microtz_info info = microtz_parse("UTC");
    ASSERT_FALSE(info.has_dst);
}

UTEST(microtz, utc_offset) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 6, 28, 19, 44, 14);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, china_parse_name) {
    microtz_info info = microtz_parse("CST-8");
    ASSERT_STREQ("CST", info.name);
}

UTEST(microtz, china_parse_offset) {
    microtz_info info = microtz_parse("CST-8");
    int expected = 8 * 60 * 60;
    ASSERT_EQ(expected, info.offset);
}

UTEST(microtz, china_no_dst) {
    microtz_info info = microtz_parse("CST-8");
    ASSERT_FALSE(info.has_dst);
}

UTEST(microtz, usa_newyorkparse_name) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    ASSERT_STREQ("EST", info.name);
}

UTEST(microtz, usa_newyorkparse_offset) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    ASSERT_EQ(-5 * 60 * 60, info.offset);
}

UTEST(microtz, usa_newyorkparse_dst_name) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    ASSERT_STREQ("EDT", info.dst_name);
}

UTEST(microtz, usa_newyorkoffset_summer) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 6, 28, 19, 44, 14);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-4 * 60, off);
}

UTEST(microtz, usa_newyorkoffset_winter) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2025, 1, 1, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-5 * 60, off);
}

UTEST(microtz, india_parse_name) {
    microtz_info info = microtz_parse("IST-5:30");
    ASSERT_STREQ("IST", info.name);
}

UTEST(microtz, india_parse_offset) {
    microtz_info info = microtz_parse("IST-5:30");
    ASSERT_EQ(19800, info.offset);
}

UTEST(microtz, india_no_dst) {
    microtz_info info = microtz_parse("IST-5:30");
    ASSERT_FALSE(info.has_dst);
}

UTEST(microtz, usa_losangeles_rule_start) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    ASSERT_EQ(3, info.start.month);
    ASSERT_EQ(2, info.start.occur);
    ASSERT_EQ(0, info.start.day);
    ASSERT_EQ(2, info.start.hour);
    ASSERT_EQ(0, info.start.min);
    ASSERT_EQ(0, info.start.sec);
}

UTEST(microtz, usa_losangeles_rule_end) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    ASSERT_EQ(11, info.end.month);
    ASSERT_EQ(1, info.end.occur);
    ASSERT_EQ(0, info.end.day);
    ASSERT_EQ(2, info.end.hour);
    ASSERT_EQ(0, info.end.min);
    ASSERT_EQ(0, info.end.sec);
}

UTEST_MAIN()
