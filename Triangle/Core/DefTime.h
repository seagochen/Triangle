#pragma once
#ifndef _TRI_DEF_TIME_H_
#define _TRI_DEF_TIME_H_

#include "SysInterfaces.h"
#include "TypeDef.h"

#ifdef __cplusplus
extern "C" {
#endif

    EXTERN double_n time_since1970();

    EXTERN double_n time_convert_timeval(struct timeval& tmval);

    EXTERN void time_convert_double(double_n time, struct timeval& tmval);

#if _WIN32
    EXTERN int gettimeofday(struct timeval* tp, struct timezone* tzp);
#endif

#ifdef __cplusplus
};
#endif

#endif
