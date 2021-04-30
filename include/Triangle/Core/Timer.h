#pragma once
#ifndef _TRI_DEF_TIME_H_
#define _TRI_DEF_TIME_H_

#include "SysInterfaces.h"
#include "TypeDefinition.h"
#include <chrono>

#if _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace sge {
    class Timeval {
    public:

        EXTERN long_n seconds() const;

        EXTERN long_n useconds() const;

        EXTERN bool_n operator>=(Timeval const& arg2) const;

        EXTERN bool_n operator<=(Timeval const& arg2) const;

        EXTERN bool_n operator<(Timeval const& arg2) const;

        EXTERN bool_n operator>(Timeval const& arg2) const;

        EXTERN bool_n operator==(Timeval const& arg2) const;

        EXTERN bool_n operator!=(Timeval const& arg2) const;

        EXTERN void operator+=(Timeval const& arg2);

        EXTERN void operator=(double_n const args);

        // returns ZERO if arg2 >= arg1
        EXTERN void operator-=(Timeval const& arg2);

        // convert timeval to double
        EXTERN double_n toVal() const;

        // convert double to timeval
        EXTERN void fromVal(double_n time);

        // constructor
        EXTERN Timeval(long_n seconds, long_n useconds);

        EXTERN Timeval(struct timeval& val);

        EXTERN Timeval(Timeval const& tv);

        EXTERN Timeval(double_n since1970);

        // default constructor
        EXTERN Timeval();

    private:

        long_n& secs();

        long_n& usecs();

        struct timeval tv;
    };

    
    class Timer {
    private:
        std::chrono::time_point<std::chrono::system_clock> t1;

    public:
        EXTERN static double_n since1970();

        EXTERN static double_n to_double(timeval& tmval);

        EXTERN static void to_timeval(double_n time, timeval& tmval);

    public:
        inline void start() {
            t1 = std::chrono::system_clock::now();
        }

        inline size_n stop() {
            auto t2 = std::chrono::system_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        }

#if _WIN32
        EXTERN static int_n gettimeofday(struct timeval* tp, struct timezone* tzp);
#endif
    };
};



#endif
