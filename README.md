# microtz - the micro size posix TZ C library

microtz implements a small POSIX TZ parser suitable for use in embedded environments where IANA is not realistic.

POSIX TZ predates IANA. Example

    TZ="PST8PDT,M3.2.0,M11.1.0"
    TZ="PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00"
    TZ="IST-5:30"

It's expected to use microtz with the stdlib `time.h`:

  * `time()`
  * `gmtime()` and/or `gmtime_r()`
