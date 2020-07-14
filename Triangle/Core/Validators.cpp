#include "Validators.h"
#include "List.h"
#include "StrUtils.h"
#include "Convert.h"

#include <iostream>
#include <regex>

using namespace std;

bool_n reg_match_email(const char* str)
{
    if (str == nullptr) return false;
    regex re("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+\\.[a-zA-Z0-9_-]+$");
    return regex_match(str, re);
};

bool_n reg_match_phone(const char* str)
{
    if (str == nullptr) return false;
    regex re("^[+]*[(]{0,1}[0-9]{1,4}[)]{0,1}[-\\s\\./0-9]*$");
    return regex_match(str, re);
};

bool_n reg_match_number(const char* str)
{
    if (str == nullptr) return false;
    regex re("^[0-9]+$");
    return regex_match(str, re);
};

bool_n reg_match_words(const char* str)
{
    if (str == nullptr) return false;
    regex re("^[A-Z][a-z]+$");
    return regex_match(str, re);
};

bool_n reg_match_filepath(const char* str)
{
    if (str == nullptr) return false;
    regex re("^(\\|/|\\.|\\w).*");
    return regex_match(str, re);
};

bool_n reg_match_time_24f(const char* str)
{
    if (str == nullptr) return false;
    regex re("^(2[0-3]|[01]?[0-9]):([0-5]?[0-9]):([0-5]?[0-9])$");
    return regex_match(str, re);
};

bool_n reg_match_time_12f(const char* str)
{
    if (str == nullptr) return false;
    regex re("^(1[0-2]|0?[1-9]):([0-5]?[0-9]):([0-5]?[0-9]) ([AP]M)?$");
    return regex_match(str, re);
};

bool_n reg_match_datetime(const char* str)
{
    if (str == nullptr) return false;
    regex re("^(19|20)\\d\\d[- /.](0[1-9]|1[012])[- /.](0[1-9]|[12][0-9]|3[01])$");
    return regex_match(str, re);
};

bool_n reg_match_ipv4(const char* str)
{
    if (str == nullptr) return false;
    regex re("^((?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d))))$");
    return regex_match(str, re);
};

int* reg_ipv4_convert(list* ptrlist)
{
    int* arrIPSeg = (int*)malloc(sizeof(int) * 4);
    if (arrIPSeg == nullptr) {
        std::cerr << "malloc ip array failed" << std::endl;
        return nullptr;
    }

    int pos = 0;
    for (list* ptr = ptrlist; ptr != nullptr; ptr = ptr->next)
    {
        if (ptr->size > 0)
        {
            // printf("converting pos at %d with %s\n", pos, ptr->ptr_content);
            *(arrIPSeg + pos) = convert_str_int((char*)ptr->content, ptr->size);
            pos += 1;
        }
    }

    return arrIPSeg;
}

bool_n reg_match_ipv4_group(const char* str, type_n CLASS)
{
    if (reg_match_ipv4(str) == TRUE)
    {
        list* ptrlist = list_create_empty();
        str_split(str, ".", ptrlist);

        // printf("size %d\n", list_elements(list));
        if (list_elements(ptrlist) < 4)
        {
            std::cerr << "convert ip address failed" << std::endl;
            return FALSE;
        }

        // convert "192.168.0.1" to [192, 168, 0, 1]
        int* arrIPv4Tokens = reg_ipv4_convert(ptrlist);
        // printf("testing ip %d:%d:%d:%d\n", arrIPv4Tokens[0], arrIPv4Tokens[1], arrIPv4Tokens[2], arrIPv4Tokens[3]);

        // check the ip class 
        bool_n flag = true;
        switch (CLASS)
        {
        case 1 /* 10.0.0.0~10.255.255.255 */:
            if (arrIPv4Tokens[0] != 10) { flag = false; }
            if (arrIPv4Tokens[1] > 255 or arrIPv4Tokens[1] < 0) { flag = false; }
            if (arrIPv4Tokens[2] > 255 or arrIPv4Tokens[2] < 0) { flag = false; }
            if (arrIPv4Tokens[3] > 255 or arrIPv4Tokens[3] < 0) { flag = false; }
            break;

        case 2 /* 172.16.0.0~172.31.255.255 */:
            if (arrIPv4Tokens[0] != 172) { flag = false; }
            if (arrIPv4Tokens[1] > 31 or arrIPv4Tokens[1] < 16) { flag = false; }
            if (arrIPv4Tokens[2] > 255 or arrIPv4Tokens[2] < 0) { flag = false; }
            if (arrIPv4Tokens[3] > 255 or arrIPv4Tokens[3] < 0) { flag = false; }
            break;

        case 3 /* 192.168.0.0~192.168.255.255 */:
            if (arrIPv4Tokens[0] != 192) { flag = false; }
            if (arrIPv4Tokens[1] != 168) { flag = false; }
            if (arrIPv4Tokens[2] > 255 or arrIPv4Tokens[2] < 0) { flag = false; }
            if (arrIPv4Tokens[3] > 255 or arrIPv4Tokens[3] < 0) { flag = false; }
            break;

        case 4 /* 224.0.0.0~239.255.255.255 */:
            if (arrIPv4Tokens[0] > 239 or arrIPv4Tokens[0] < 224) { flag = false; }
            if (arrIPv4Tokens[1] > 255 or arrIPv4Tokens[1] < 0) { flag = false; }
            if (arrIPv4Tokens[2] > 255 or arrIPv4Tokens[2] < 0) { flag = false; }
            if (arrIPv4Tokens[3] > 255 or arrIPv4Tokens[3] < 0) { flag = false; }
            break;

        case 5 /* 240.0.0.0~255.255.255.255 */:
            if (arrIPv4Tokens[0] > 255 or arrIPv4Tokens[0] < 240) { flag = false; }
            if (arrIPv4Tokens[1] > 255 or arrIPv4Tokens[1] < 0) { flag = false; }
            if (arrIPv4Tokens[2] > 255 or arrIPv4Tokens[2] < 0) { flag = false; }
            if (arrIPv4Tokens[3] > 255 or arrIPv4Tokens[3] < 0) { flag = false; }
            break;

        default /* from 0.0.0.0 ~ 255.255.255.255 */:
            if (arrIPv4Tokens[0] > 255 or arrIPv4Tokens[0] < 0) { flag = false; }
            if (arrIPv4Tokens[1] > 255 or arrIPv4Tokens[1] < 0) { flag = false; }
            if (arrIPv4Tokens[2] > 255 or arrIPv4Tokens[2] < 0) { flag = false; }
            if (arrIPv4Tokens[3] > 255 or arrIPv4Tokens[3] < 0) { flag = false; }
            break;
        }

        list_dispose(ptrlist);
        SAFE_FREE(arrIPv4Tokens);
        return flag;
    }
    return FALSE;
};

bool_n reg_match_pattern(const char* str, const char* pattern)
{
    if (str == nullptr || pattern == nullptr) return false;
    regex re(pattern);
    return regex_match(str, re);
};

bool_n reg_contains_pattern(const char* str, const char* pattern)
{
    if (str == nullptr || pattern == nullptr) return false;
    regex re(pattern);
    return regex_search(str, re);
};