#include "StrUtils.h"
#include "StrUtils.h"

#include <string.h>
#include <ctype.h>

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

const char* str_trim(char const* s)
{
    char* p = (char*)s;
    return rtrim(ltrim(p));
}

#include <string>
#include <iostream>
#include "TypeDef.h"

bool_n str_cmp(char const* s1, char const* s2)
{
    if (s1 == nullptr && s2 == nullptr)
    {
        std::cerr << "s1 or s2 is nullptr" << std::endl;
        return FALSE;
    }

    const char* trim1 = str_trim(s1);
    const char* trim2 = str_trim(s2);

    return strcmp(trim1, trim2) == 0;
};



void str_split(char const* str, char const* delim, list* ptrlist)
{
    if (str == nullptr)
    {
        std::cout << "str cannot be null" << std::endl;
        return;
    }

    if (ptrlist == nullptr)
    {
        std::cout << "list cannot be null" << std::endl;
        return;
    }

    // empty list
    list_empty(ptrlist);

    // temporary vals
    std::string s(str);
    std::string delimiter(delim);

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        // std::cout << token << std::endl;
        basic_node* node = node_copy_data(token.length(), DATA_STRING, token.c_str());
        list_append(ptrlist, node);
        s.erase(0, pos + delimiter.length());
    }

    basic_node* node = node_copy_data(s.length(), DATA_STRING, s.c_str());
    list_append(ptrlist, node);
};

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

const size_n nStrSize = 1024;
char szGlobal[nStrSize] = { 0 };

const char* str_fmt(char const* fmt, ...)
{
    // zero temp buffer
    memset(szGlobal, 0, nStrSize);

    // use a temporary buffer, to avoid such a case
    // str_fmt(str_fmt(...))
    // this calling style will probably caused some 
    // uncertain errors
    va_list ap;
    va_start(ap, fmt);
#if _WIN32
    vsprintf_s(szGlobal, nStrSize, fmt, ap);
#else
    vsprintf(szGlobal, fmt, ap);
#endif
    va_end(ap);

    // return final data
    return szGlobal;
};
