#pragma once
#ifndef _TRI_STR_UTILS_H_
#define _TRI_STR_UTILS_H_

#include "SysInterfaces.h"
#include "TypeDef.h"
#include "List.h"

#ifdef __cplusplus
extern "C" {
#endif

    EXTERN const char* str_trim(char const* str);

    EXTERN bool_n str_cmp(char const* s1, char const* s2);

    EXTERN void str_split(char const* str, char const* delim, list* l);

    EXTERN const char* str_fmt(char const* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
