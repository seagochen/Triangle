#pragma once
#ifndef _TRI_TIMEVAL_H_
#define _TRI_TIMEVAL_H_

#include "../Core/DefTime.h"
#include "../Core/TypeDef.h"
#include "DLLExpo.h"

#if _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

class Timeval {
public:

    DLL_EXPO long_n seconds() const;

    DLL_EXPO long_n useconds() const;

    DLL_EXPO bool_n operator>=(Timeval const& arg2) const;

    DLL_EXPO bool_n operator<=(Timeval const& arg2) const;

    DLL_EXPO bool_n operator<(Timeval const& arg2) const;

    DLL_EXPO bool_n operator>(Timeval const& arg2) const;

    DLL_EXPO bool_n operator==(Timeval const& arg2) const;

    DLL_EXPO bool_n operator!=(Timeval const& arg2) const;

    DLL_EXPO void operator+=(Timeval const& arg2);

    DLL_EXPO void operator=(double_n const args);

    // returns ZERO if arg2 >= arg1
    DLL_EXPO void operator-=(Timeval const& arg2);

    // convert timeval to double
    DLL_EXPO double_n toVal() const;

    // convert double to timeval
    DLL_EXPO void fromVal(double_n time);

    // constructor
    DLL_EXPO Timeval(long_n seconds, long_n useconds);

    DLL_EXPO Timeval(struct timeval& val);

    DLL_EXPO Timeval(Timeval const& tv);

    DLL_EXPO Timeval(double_n since1970);

    // default constructor
    DLL_EXPO Timeval();

private:

    long_n& secs();

    long_n& usecs();

    struct timeval tv;
};

#endif


