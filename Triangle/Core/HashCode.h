#pragma once
#ifndef _TRI_HASH_CODE_H_
#define _TRI_HASH_CODE_H_

#include "SysInterfaces.h"
#include "TypeDef.h"

#if __cplusplus
extern "C" {
#endif

    // get the string of md5
    // This method will create a new space of md5 string
    // so you need to pay attention to the memory release 
    // after the end of use.
    EXTERN char* code_md5(void const* dataset, size_n len);

    // get the string of sha256
    // This method will create a new space of sha256 string
    // so you need to pay attention to the memory release 
    // after the end of use.
    EXTERN char* code_sha256(void const* dataset, size_n len);


    EXTERN char* code_sha1(void const* dataset, size_n len);

#if __cplusplus
};
#endif

#endif
