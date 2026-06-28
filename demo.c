#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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


//#define LOCAL_OFFSET_IN_MINS 0  // UTC / GMT0
//#define TZ_NAME "UTC"

//#define LOCAL_OFFSET_IN_MINS (-8 * 60)  // Los Angeles Winter time
//#define TZ_NAME "PST"

#define LOCAL_OFFSET_IN_MINS (-7 * 60)  // Los Angeles DST
#define TZ_NAME "PDT"


    utc_time = time(NULL);
    printf("utc_time:           %d\n", utc_time);
    converted_local_tm = utc_time + (60 * LOCAL_OFFSET_IN_MINS);
    printf("converted_local_tm: %d\n", converted_local_tm);
    local_tm = gmtime(&converted_local_tm);
    strftime(buffer, sizeof(buffer), time_format, local_tm);
    snprintf(time_str, sizeof(time_str), "%s %s", TZ_NAME, buffer);
    printf("time: %s\n", time_str);
}
