#pragma once
#ifndef _TRI_STR_UTILS_H_
#define _TRI_STR_UTILS_H_

#include "SysInterfaces.h"
#include "TypeDefinition.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory.h>

namespace sge {

    class StringUtils {
    public:
        template <typename ...Args>
        static std::string format(char_c* format, Args... args) {
            char buffer[1024] = { 0 };
            memset(buffer, 0, 1024);
            size_t size = snprintf(buffer, 1024, format, args...);
            return std::string(buffer);
        }

        EXTERN static std::string trim(std::string &str);

        EXTERN static std::vector<std::string> split(std::string str, std::string delim,
            std::vector<std::string> &sub_strs);
    };


#define PTR_ERROR(f,l,e) StringUtils::format("File: %s line: %s\n<Error>: %s\n", f, l, e);
#define PTR_INFO(i) StringUtils::format("<Info>: %s\n", i);
};

#endif