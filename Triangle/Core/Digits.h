#pragma once
#ifndef _TRI_DIGITS_H_
#define _TRI_DIGITS_H_

#include "TypeDef.h"
#include "SysInterfaces.h"

#ifdef __cplusplus
extern "C" {
#endif

    // convert int_n to byte_n array
    EXTERN byte_n const* convert_itob(int_n const n, byte_n** p = nullptr);

    // convert long_n to byte_n array
    EXTERN byte_n const* convert_ltob(long_n const n, byte_n** p = nullptr);

    // convert float_n to byte_n array
    EXTERN byte_n const* convert_ftob(float_n const n, byte_n** p = nullptr);

    // convert double_n to byte_n array
    EXTERN byte_n const* convert_dtob(double_n const n, byte_n** p = nullptr);

    // convert byte_n array to int_n
    EXTERN int_n const convert_btoi(byte_n* p);

    // convert byte_n array to long_n
    EXTERN long_n const convert_btol(byte_n* p);

    // convert byte_n array to float_n
    EXTERN float_n const convert_btof(byte_n* p);

    // convert byte_n array to double_n
    EXTERN double_n const convert_btod(byte_n* p);

#ifdef __cplusplus
};
#endif

#endif