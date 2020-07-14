#pragma once
#ifndef _TRI_CONVERT_H_
#define _TRI_CONVERT_H_

#include "TypeDef.h"
#include "SysInterfaces.h"

#ifdef __cplusplus
extern "C" {
#endif

    EXTERN int_n  convert_str_int(char const* str, size_n size);

    EXTERN long_n convert_str_long(char const* str, size_n size);

    EXTERN float_n convert_str_float(char const* str, size_n size);

    EXTERN double_n convert_str_double(char const* str, size_n size);

    EXTERN bool_n convert_int_str(int_n const n, char* out, size_n& size);

    EXTERN bool_n convert_long_str(long_n const n, char* out, size_n& size);

    EXTERN bool_n convert_float_str(float_n const n, char* out, size_n& size);

    EXTERN bool_n convert_double_str(double_n const n, char* out, size_n& size);

    EXTERN size_n tstrlen(char_n const* ptr);

    /// ptr converter for local machine ///
    /// This method will create a backup
    /// so you need to pay attention to the memory release 
    /// after the end of use.
    EXTERN char_n const* cstr_wrap(char const* ptr);

    /// ptr converter for local machine ///
    /// This method will create a backup
    /// so you need to pay attention to the memory release 
    /// after the end of use.
    EXTERN char const* cstr_uwrap(char_n const* ptr);

#ifdef __cplusplus
};
#endif

#endif