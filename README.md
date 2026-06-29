# microtz - the micro size posix TZ C library

microtz implements a small POSIX TZ parser suitable for use in embedded environments where IANA is not realistic.

Also see https://github.com/clach04/py-posix_tz for a similar MicroPython project.

POSIX TZ predates IANA. Example

    TZ="PST8PDT,M3.2.0,M11.1.0"
    TZ="PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00"
    TZ="IST-5:30"

It's expected to use microtz with the stdlib `time.h`:

  * `time()`
  * `gmtime()` and/or `gmtime_r()`


## Sample build, test, and demo

    gcc -o demo demo.c microtz.c

    gcc -o test_microtz test_microtz.c microtz.c -I.


NOTE Under Windows CMD will get ANSI escape sequences, for now recommend running under Terminal (or similar).
