#if _WIN32
#include <Windows.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64 
#else // linux headers
#include <sys/time.h>
#endif

#include "Timer.h"

using namespace sge;

#if _WIN32
int_n Timer::gettimeofday(timeval* tp, timezone* tzp)
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

double_n Timer::since1970()
{
    struct timeval time;
    gettimeofday(&time, NULL);

    return to_double(time);
};


double_n Timer::to_double(struct timeval& tmval)
{
    return tmval.tv_sec + (double_n)tmval.tv_usec / 1000000.0;
};

void Timer::to_timeval(double_n time, struct timeval& tmval)
{
    long_n tv_sec = (long_n)time;
    long_n tv_usec = (long_n)((time - (double_n)tv_sec) * 1000000.0);

    tmval.tv_sec = tv_sec;
    tmval.tv_usec = tv_usec;
};


#define secs secs()
#define usecs usecs()

long_n Timeval::seconds() const { return tv.tv_sec; };

long_n Timeval::useconds() const { return tv.tv_usec; };

bool_n Timeval::operator>=(Timeval const& arg2) const {
    return seconds() > arg2.seconds()
        || (seconds() == arg2.seconds()
            && useconds() >= arg2.useconds());
}

bool_n Timeval::operator<=(Timeval const& arg2) const {
    return arg2 >= *this;
};

bool_n Timeval::operator<(Timeval const& arg2) const {
    return !(*this >= arg2);
};

bool_n Timeval::operator>(Timeval const& arg2) const {
    return arg2 < *this;
};

bool_n Timeval::operator==(Timeval const& arg2) const {
    return *this >= arg2 && arg2 >= *this;
};

bool_n Timeval::operator!=(Timeval const& arg2) const {
    return !(*this == arg2);
};

void Timeval::operator+=(Timeval const& arg2) {
    secs += arg2.seconds();
    usecs += arg2.useconds();

    if (secs < 0) secs = 0;
    if (usecs < 0) usecs = 0;
}

// returns ZERO iff arg2 >= arg1
void Timeval::operator-=(Timeval const& arg2) {
    secs -= arg2.seconds();
    usecs -= arg2.useconds();

    if (secs < 0) {
        secs = usecs = 0;
    }
}

void Timeval::operator=(double_n const args)
{
    fromVal(args);
};

double_n Timeval::toVal() const {
    return tv.tv_sec + (double_n)tv.tv_usec / 1000000.0;
}

void Timeval::fromVal(double_n time) {
    Timer::to_timeval(time, tv);
}

// constructor
Timeval::Timeval(long_n seconds, long_n useconds) {
    secs = seconds;
    usecs = useconds;
};

Timeval::Timeval(struct timeval& val) {
    secs = val.tv_sec;
    usecs = val.tv_usec;
}

Timeval::Timeval(Timeval const& val)
{
    secs = val.useconds();
    usecs = val.seconds();
}

Timeval::Timeval(double_n since1970) {
    Timer::to_timeval(since1970, tv);
}

Timeval::Timeval() : Timeval(0) {}

#ifdef secs
#undef secs
#endif
long_n& Timeval::secs()
{
    return (long_n&)tv.tv_sec;
};

#ifdef usecs
#undef usecs
#endif
long_n& Timeval::usecs()
{
    return (long_n&)tv.tv_usec;
};