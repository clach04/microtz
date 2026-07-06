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

UTEST(microtz, china_offset_summer) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 6, 28, 19, 44, 14);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_winter) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2025, 1, 1, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, india_offset_summer) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 6, 28, 19, 44, 14);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_winter) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2025, 1, 1, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, germany_offset_summer) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 6, 28, 19, 44, 14);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_winter) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2025, 1, 1, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_summer) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 6, 28, 19, 44, 14);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_winter) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2025, 1, 1, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, usa_texas_offset_summer) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 6, 28, 19, 44, 14);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_winter) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2025, 1, 1, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-360, off);
}

UTEST(microtz, china_offset_LA_winter_to_DST_2026_03_08__09_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 8, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_LA_winter_to_DST_2026_03_08__09_59_59) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 8, 9, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_LA_winter_to_DST_2026_03_08__10_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 8, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_LA_winter_to_DST_2026_03_08__11_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 8, 11, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_11_01__07_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 11, 1, 7, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_11_01__08_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 11, 1, 8, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_11_01__08_59_59) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 11, 1, 8, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_11_01__09_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 11, 1, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_11_01__10_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 11, 1, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_winter_to_DST_2026_03_29__00_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 29, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_winter_to_DST_2026_03_29__00_59_59) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 29, 0, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_winter_to_DST_2026_03_29__01_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 29, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_winter_to_DST_2026_03_29__01_59_59) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 29, 1, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_winter_to_DST_2026_03_29__02_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 29, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_winter_to_DST_2026_03_29__02_59_59) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 29, 2, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_winter_to_DST_2026_03_29__03_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 29, 3, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_winter_to_DST_2026_03_29__04_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 3, 29, 4, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_10_24__22_59_59) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 10, 24, 22, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_10_24__23_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 10, 24, 23, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_10_24__23_59_59) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 10, 24, 23, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_10_25__00_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 10, 25, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_10_25__01_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 10, 25, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, china_offset_London_DST_to_winter_2026_10_25__02_00_00) {
    microtz_info info = microtz_parse("CST-8");
    time_t ts = mktime_utc(2026, 10, 25, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(480, off);
}

UTEST(microtz, india_offset_LA_winter_to_DST_2026_03_08__09_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 8, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_LA_winter_to_DST_2026_03_08__09_59_59) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 8, 9, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_LA_winter_to_DST_2026_03_08__10_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 8, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_LA_winter_to_DST_2026_03_08__11_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 8, 11, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_11_01__07_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 11, 1, 7, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_11_01__08_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 11, 1, 8, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_11_01__08_59_59) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 11, 1, 8, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_11_01__09_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 11, 1, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_11_01__10_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 11, 1, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_winter_to_DST_2026_03_29__00_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 29, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_winter_to_DST_2026_03_29__00_59_59) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 29, 0, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_winter_to_DST_2026_03_29__01_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 29, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_winter_to_DST_2026_03_29__01_59_59) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 29, 1, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_winter_to_DST_2026_03_29__02_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 29, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_winter_to_DST_2026_03_29__02_59_59) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 29, 2, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_winter_to_DST_2026_03_29__03_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 29, 3, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_winter_to_DST_2026_03_29__04_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 3, 29, 4, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_10_24__22_59_59) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 10, 24, 22, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_10_24__23_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 10, 24, 23, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_10_24__23_59_59) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 10, 24, 23, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_10_25__00_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 10, 25, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_10_25__01_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 10, 25, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, india_offset_London_DST_to_winter_2026_10_25__02_00_00) {
    microtz_info info = microtz_parse("IST-5:30");
    time_t ts = mktime_utc(2026, 10, 25, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(330, off);
}

UTEST(microtz, germany_offset_LA_winter_to_DST_2026_03_08__09_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_LA_winter_to_DST_2026_03_08__09_59_59) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 9, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_LA_winter_to_DST_2026_03_08__10_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_LA_winter_to_DST_2026_03_08__11_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 11, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_11_01__07_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 7, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_11_01__08_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 8, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_11_01__08_59_59) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 8, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_11_01__09_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_11_01__10_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_winter_to_DST_2026_03_29__00_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_winter_to_DST_2026_03_29__00_59_59) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 0, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_winter_to_DST_2026_03_29__01_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_winter_to_DST_2026_03_29__01_59_59) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 1, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_winter_to_DST_2026_03_29__02_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_winter_to_DST_2026_03_29__02_59_59) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 2, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_winter_to_DST_2026_03_29__03_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 3, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_winter_to_DST_2026_03_29__04_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 4, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_10_24__22_59_59) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 22, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_10_24__23_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 23, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_10_24__23_59_59) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 23, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_10_25__00_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(120, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_10_25__01_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, germany_offset_London_DST_to_winter_2026_10_25__02_00_00) {
    microtz_info info = microtz_parse("CET-1CEST,M3.5.0,M10.5.0/3:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, utc_offset_LA_winter_to_DST_2026_03_08__09_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 8, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_LA_winter_to_DST_2026_03_08__09_59_59) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 8, 9, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_LA_winter_to_DST_2026_03_08__10_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 8, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_LA_winter_to_DST_2026_03_08__11_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 8, 11, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_11_01__07_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 11, 1, 7, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_11_01__08_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 11, 1, 8, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_11_01__08_59_59) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 11, 1, 8, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_11_01__09_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 11, 1, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_11_01__10_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 11, 1, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_winter_to_DST_2026_03_29__00_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 29, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_winter_to_DST_2026_03_29__00_59_59) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 29, 0, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_winter_to_DST_2026_03_29__01_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 29, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_winter_to_DST_2026_03_29__01_59_59) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 29, 1, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_winter_to_DST_2026_03_29__02_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 29, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_winter_to_DST_2026_03_29__02_59_59) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 29, 2, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_winter_to_DST_2026_03_29__03_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 29, 3, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_winter_to_DST_2026_03_29__04_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 3, 29, 4, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_10_24__22_59_59) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 10, 24, 22, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_10_24__23_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 10, 24, 23, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_10_24__23_59_59) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 10, 24, 23, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_10_25__00_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 10, 25, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_10_25__01_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 10, 25, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, utc_offset_London_DST_to_winter_2026_10_25__02_00_00) {
    microtz_info info = microtz_parse("UTC");
    time_t ts = mktime_utc(2026, 10, 25, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_LA_winter_to_DST_2026_03_08__09_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_LA_winter_to_DST_2026_03_08__09_59_59) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 9, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_LA_winter_to_DST_2026_03_08__10_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_LA_winter_to_DST_2026_03_08__11_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 11, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_11_01__07_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 7, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_11_01__08_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 8, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_11_01__08_59_59) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 8, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_11_01__09_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_11_01__10_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_winter_to_DST_2026_03_29__00_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_winter_to_DST_2026_03_29__00_59_59) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 0, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_winter_to_DST_2026_03_29__01_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_winter_to_DST_2026_03_29__01_59_59) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 1, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_winter_to_DST_2026_03_29__02_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_winter_to_DST_2026_03_29__02_59_59) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 2, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_winter_to_DST_2026_03_29__03_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 3, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_winter_to_DST_2026_03_29__04_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 4, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_10_24__22_59_59) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 22, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_10_24__23_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 23, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_10_24__23_59_59) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 23, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_10_25__00_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(60, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_10_25__01_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, uk_offset_London_DST_to_winter_2026_10_25__02_00_00) {
    microtz_info info = microtz_parse("GMT0BST,M3.5.0/1:00:00,M10.5.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(0, off);
}

UTEST(microtz, usa_newyork_offset_LA_winter_to_DST_2026_03_08__09_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 8, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_LA_winter_to_DST_2026_03_08__09_59_59) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 8, 9, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_LA_winter_to_DST_2026_03_08__10_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 8, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_LA_winter_to_DST_2026_03_08__11_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 8, 11, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_11_01__07_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 7, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_11_01__08_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 8, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_11_01__08_59_59) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 8, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_11_01__09_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_11_01__10_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_newyork_offset_London_winter_to_DST_2026_03_29__00_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_winter_to_DST_2026_03_29__00_59_59) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 0, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_winter_to_DST_2026_03_29__01_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_winter_to_DST_2026_03_29__01_59_59) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 1, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_winter_to_DST_2026_03_29__02_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_winter_to_DST_2026_03_29__02_59_59) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 2, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_winter_to_DST_2026_03_29__03_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 3, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_winter_to_DST_2026_03_29__04_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 4, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_10_24__22_59_59) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 24, 22, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_10_24__23_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 24, 23, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_10_24__23_59_59) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 24, 23, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_10_25__00_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 25, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_10_25__01_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 25, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_newyork_offset_London_DST_to_winter_2026_10_25__02_00_00) {
    microtz_info info = microtz_parse("EST5EDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 25, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-240, off);
}

UTEST(microtz, usa_texas_offset_LA_winter_to_DST_2026_03_08__09_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 8, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_LA_winter_to_DST_2026_03_08__09_59_59) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 8, 9, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_LA_winter_to_DST_2026_03_08__10_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 8, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_LA_winter_to_DST_2026_03_08__11_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 8, 11, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_11_01__07_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 7, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-360, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_11_01__08_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 8, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-360, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_11_01__08_59_59) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 8, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-360, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_11_01__09_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-360, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_11_01__10_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 11, 1, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-360, off);
}

UTEST(microtz, usa_texas_offset_London_winter_to_DST_2026_03_29__00_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_winter_to_DST_2026_03_29__00_59_59) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 0, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_winter_to_DST_2026_03_29__01_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_winter_to_DST_2026_03_29__01_59_59) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 1, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_winter_to_DST_2026_03_29__02_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_winter_to_DST_2026_03_29__02_59_59) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 2, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_winter_to_DST_2026_03_29__03_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 3, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_winter_to_DST_2026_03_29__04_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 3, 29, 4, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_10_24__22_59_59) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 24, 22, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_10_24__23_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 24, 23, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_10_24__23_59_59) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 24, 23, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_10_25__00_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 25, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_10_25__01_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 25, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_texas_offset_London_DST_to_winter_2026_10_25__02_00_00) {
    microtz_info info = microtz_parse("CST6CDT,M3.2.0,M11.1.0");
    time_t ts = mktime_utc(2026, 10, 25, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-300, off);
}

UTEST(microtz, usa_losangeles_offset_LA_winter_to_DST_2026_03_08__09_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-480, off);
}

UTEST(microtz, usa_losangeles_offset_LA_winter_to_DST_2026_03_08__09_59_59) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 9, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-480, off);
}

UTEST(microtz, usa_losangeles_offset_LA_winter_to_DST_2026_03_08__10_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_LA_winter_to_DST_2026_03_08__11_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 8, 11, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_11_01__07_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 7, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_11_01__08_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 8, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_11_01__08_59_59) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 8, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_11_01__09_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 9, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-480, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_11_01__10_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 11, 1, 10, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-480, off);
}

UTEST(microtz, usa_losangeles_offset_London_winter_to_DST_2026_03_29__00_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_winter_to_DST_2026_03_29__00_59_59) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 0, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_winter_to_DST_2026_03_29__01_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_winter_to_DST_2026_03_29__01_59_59) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 1, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_winter_to_DST_2026_03_29__02_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_winter_to_DST_2026_03_29__02_59_59) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 2, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_winter_to_DST_2026_03_29__03_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 3, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_winter_to_DST_2026_03_29__04_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 3, 29, 4, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_10_24__22_59_59) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 22, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_10_24__23_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 23, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_10_24__23_59_59) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 24, 23, 59, 59);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_10_25__00_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 0, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_10_25__01_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 1, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST(microtz, usa_losangeles_offset_London_DST_to_winter_2026_10_25__02_00_00) {
    microtz_info info = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    time_t ts = mktime_utc(2026, 10, 25, 2, 0, 0);
    int off = microtz_offset(&info, ts);
    ASSERT_EQ(-420, off);
}

UTEST_MAIN()
