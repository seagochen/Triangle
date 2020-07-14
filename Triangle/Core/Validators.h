#pragma once
#ifndef _TRI_VALIDATORS_H_
#define _TRI_VALIDATORS_H_


#include "SysInterfaces.h"
#include "TypeDef.h"

#ifdef __cplusplus
extern "C" {
#endif

    EXTERN bool_n reg_match_email(char const* str);

    EXTERN bool_n reg_match_phone(char const* str);

    EXTERN bool_n reg_match_number(char const* str);

    EXTERN bool_n reg_match_words(char const* str);

    EXTERN bool_n reg_match_filepath(char const* str);

    EXTERN bool_n reg_match_time_24f(char const* str);

    EXTERN bool_n reg_match_time_12f(char const* str);

    EXTERN bool_n reg_match_datetime(char const* str);

    EXTERN bool_n reg_match_ipv4(char const* str);

    EXTERN bool_n reg_match_ipv4_group(char const* str, type_n CLASS);

    EXTERN bool_n reg_match_pattern(char const* str, char const* pattern);

    EXTERN bool_n reg_contains_pattern(char const* str, char const* pattern);

#ifdef __cplusplus
}
#endif

/** Other useful patterns for regular check **/

// Class A 10.0.0.0~10.255.255.255
#define IPV4_CLASS_A    1

// Class B 172.16.0.0~172.31.255.255
#define IPV4_CLASS_B    2

// Class C 192.168.0.0~192.168.255.255
#define IPV4_CLASS_C    3

// Class D 224.0.0.0~239.255.255.255
#define IPV4_CLASS_D    4

// Class E 240.0.0.0~255.255.255.255
#define IPV4_CLASS_E    5

// from 0.0.0.0 ~ 255.255.255.255
#define IPV4_CLASS_DEFAULT 0

#endif