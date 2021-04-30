#include <string.h>
#include "Core/StrUtils.h"

char* ltrim(char const* s)
{
    if (s == nullptr || strlen(s) <= 0)
        return nullptr;

    char* p = (char*)s;
    while (isspace(*p)) p++;
    return p;
}

char* rtrim(char* s)
{
    if (s == nullptr || strlen(s) <= 0)
        return nullptr;
    
    char* back = s + strlen(s);
    while (isspace(*--back));
    if (*(back + 1) != '\0')* (back + 1) = '\0';
    return s;
}

const char* trimstr(char const* s)
{
    char* p = (char*)s;
    return rtrim(ltrim(p));
}

std::string sge::StringUtils::trim(std::string &str)
{
    const char* trimed_str = trimstr(str.c_str());
    str = trimed_str;
    return str;
}

#include <iostream>

std::vector<std::string> sge::StringUtils::split(std::string str,
    std::string delim, std::vector<std::string> &sub_strs)
{
    // 先清空一下
    sub_strs.clear();

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delim)) != std::string::npos) {
        token = str.substr(0, pos);
        sub_strs.push_back(token);
        str.erase(0, pos + delim.length());
    }
    sub_strs.push_back(str);

    return sub_strs;
}
