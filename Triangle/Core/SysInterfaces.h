#ifndef _TRI_SYS_INTERFACES_H_
#define _TRI_SYS_INTERFACES_H_

#include "SystemEnv.h"

#ifdef _WIN32
    #ifndef MS_CPP_API_EXPORTS
        #define MS_API __declspec(dllexport) 
    #else
        #define MS_API __declspec(dllimport) 
    #endif
#endif

#ifdef _WIN32
    #define EXTERN MS_API
#else
    #define EXTERN
#endif

#endif
