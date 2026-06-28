#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "microtz.h"

int main (int argc, char *argv[])
{
    struct tm *local_tm=NULL;
    time_t utc_time=time(NULL);
    time_t converted_local_tm=time(NULL);
    //char *time_format = "%I:%M";// AM/PM
    //char *time_format = "%R";  // 24 hours pebble
    char *time_format = "%H:%M";  // 24 hours c99
    static char buffer[]="00:00";
    static char time_str[]="timezonename 00:00";  // need one string per layer, reusing same buffer results in same text

    //microtz_info tz = microtz_parse("UTC");
    //microtz_info tz = microtz_parse("PST8PDT,M3.2.0,M11.1.0");
    microtz_info tz = microtz_parse("PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    //microtz_info tz = microtz_parse("IST-5:30");  // FIXME not implemented / broken
    int local_offset_mins = microtz_offset(&tz, time(NULL));
    const char *tz_name = (local_offset_mins != tz.offset / 60) ? tz.dst_name : tz.name;

    utc_time = time(NULL);
    printf("utc_time:           %d\n", utc_time);
    converted_local_tm = utc_time + (60 * local_offset_mins);
    printf("converted_local_tm: %d\n", converted_local_tm);
    local_tm = gmtime(&converted_local_tm);
    strftime(buffer, sizeof(buffer), time_format, local_tm);
    snprintf(time_str, sizeof(time_str), "%s %s", tz_name, buffer);
    printf("time: %s\n", time_str);
}
