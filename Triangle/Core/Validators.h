#pragma once
#ifndef _TRI_VALIDATORS_H_
#define _TRI_VALIDATORS_H_


#include "SysInterfaces.h"
#include "TypeDefinition.h"
#include <string>

namespace sge {

    class Validator {

    public:

        EXTERN static bool_n match_email(std::string str);

        EXTERN static bool_n match_phone(std::string str);

        EXTERN static bool_n match_number(std::string str);

        EXTERN static bool_n match_words(std::string str);

        EXTERN static bool_n match_filepath(std::string str);

        EXTERN static bool_n match_time_24f(std::string str);

        EXTERN static bool_n match_time_12f(std::string str);

        EXTERN static bool_n match_datetime(std::string str);

        EXTERN static bool_n match_ipv4(std::string str);

        EXTERN static bool_n match_ipv4_group(std::string str, type_n CLASS);

        EXTERN static bool_n match_pattern(std::string str, std::string pattern);

        EXTERN static bool_n contains_pattern(std::string str, std::string pattern);
    };

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
}

#endif