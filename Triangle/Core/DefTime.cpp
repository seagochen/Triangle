#if _WIN32
#include <Windows.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64 
#else // linux headers
#include <sys/time.h>
#endif
#include "DefTime.h"

#if _WIN32
int gettimeofday(struct timeval* tp, struct timezone* tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);
    time = ((uint64_t)file_time.dwLowDateTime);
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec = ((time - EPOCH) / 10000000L);
    tp->tv_usec = (system_time.wMilliseconds * 1000);
    return 0;
}
#endif

double_n time_since1970()
{
    struct timeval time;
    gettimeofday(&time, NULL);

    return time_convert_timeval(time);
};


double_n time_convert_timeval(struct timeval& tmval)
{
    return tmval.tv_sec + (double_n)tmval.tv_usec / 1000000.0;
};

void time_convert_double(double_n time, struct timeval& tmval)
{
    long_n tv_sec = (long_n)time;
    long_n tv_usec = (long_n)((time - (double_n)tv_sec) * 1000000.0);

    tmval.tv_sec = tv_sec;
    tmval.tv_usec = tv_usec;
};