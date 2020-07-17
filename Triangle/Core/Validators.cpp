#include "Validators.h"
#include "CommonTool.hpp"
#include "StrUtils.h"
#include "Convert.h"

#include <vector>
#include <iostream>
#include <regex>
#include <string>

using namespace std;
using namespace sge;

bool_n Validator::match_email(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+\\.[a-zA-Z0-9_-]+$");
    return regex_match(str, re);
};

bool_n Validator::match_phone(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^[+]*[(]{0,1}[0-9]{1,4}[)]{0,1}[-\\s\\./0-9]*$");
    return regex_match(str, re);
};

bool_n Validator::match_number(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^[0-9]+$");
    return regex_match(str, re);
};

bool_n Validator::match_words(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^[A-Z][a-z]+$");
    return regex_match(str, re);
};

bool_n Validator::match_filepath(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^(\\|/|\\.|\\w).*");
    return regex_match(str, re);
};

bool_n Validator::match_time_24f(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^(2[0-3]|[01]?[0-9]):([0-5]?[0-9]):([0-5]?[0-9])$");
    return regex_match(str, re);
};

bool_n Validator::match_time_12f(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^(1[0-2]|0?[1-9]):([0-5]?[0-9]):([0-5]?[0-9]) ([AP]M)?$");
    return regex_match(str, re);
};

bool_n Validator::match_datetime(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^(19|20)\\d\\d[- /.](0[1-9]|1[012])[- /.](0[1-9]|[12][0-9]|3[01])$");
    return regex_match(str, re);
};

bool_n Validator::match_ipv4(std::string str)
{
    if (str.length() <= 0) return false;
    regex re("^((?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d))))$");
    return regex_match(str, re);
};

bool_n Validator::match_ipv4_group(std::string str, type_n CLASS)
{
    if (match_ipv4(str) == TRUE)
    {
        vector<string> tokens;
        StringUtils::split(str, ".", tokens);

        if (tokens.size() != 4) {
            cerr << "Convert ip address failed! " << str << endl;
            return FALSE;
        }

        // 把IP地址（文本）进行转换
        std::vector<int_n> nips;
        for (auto token : tokens) {
            int_n n = Converter::str_to_int(token);
            nips.push_back(n);
        }

        // check the ip class 
        bool_n flag = true;
        switch (CLASS)
        {
        case 1 /* 10.0.0.0~10.255.255.255 */:
            if (nips[0] != 10) { flag = false; }
            if (nips[1] > 255 or nips[1] < 0) { flag = false; }
            if (nips[2] > 255 or nips[2] < 0) { flag = false; }
            if (nips[3] > 255 or nips[3] < 0) { flag = false; }
            break;

        case 2 /* 172.16.0.0~172.31.255.255 */:
            if (nips[0] != 172) { flag = false; }
            if (nips[1] > 31 or nips[1] < 16) { flag = false; }
            if (nips[2] > 255 or nips[2] < 0) { flag = false; }
            if (nips[3] > 255 or nips[3] < 0) { flag = false; }
            break;

        case 3 /* 192.168.0.0~192.168.255.255 */:
            if (nips[0] != 192) { flag = false; }
            if (nips[1] != 168) { flag = false; }
            if (nips[2] > 255 or nips[2] < 0) { flag = false; }
            if (nips[3] > 255 or nips[3] < 0) { flag = false; }
            break;

        case 4 /* 224.0.0.0~239.255.255.255 */:
            if (nips[0] > 239 or nips[0] < 224) { flag = false; }
            if (nips[1] > 255 or nips[1] < 0) { flag = false; }
            if (nips[2] > 255 or nips[2] < 0) { flag = false; }
            if (nips[3] > 255 or nips[3] < 0) { flag = false; }
            break;

        case 5 /* 240.0.0.0~255.255.255.255 */:
            if (nips[0] > 255 or nips[0] < 240) { flag = false; }
            if (nips[1] > 255 or nips[1] < 0) { flag = false; }
            if (nips[2] > 255 or nips[2] < 0) { flag = false; }
            if (nips[3] > 255 or nips[3] < 0) { flag = false; }
            break;

        default /* from 0.0.0.0 ~ 255.255.255.255 */:
            if (nips[0] > 255 or nips[0] < 0) { flag = false; }
            if (nips[1] > 255 or nips[1] < 0) { flag = false; }
            if (nips[2] > 255 or nips[2] < 0) { flag = false; }
            if (nips[3] > 255 or nips[3] < 0) { flag = false; }
            break;
        }
        return flag;
    }
    return FALSE;
};

bool_n Validator::match_pattern(std::string str, std::string pattern)
{
    if (str.length() <= 0 || pattern.length() <= 0) return false;
    regex re(pattern);
    return regex_match(str, re);
};

bool_n Validator::contains_pattern(std::string str, std::string pattern)
{
    if (str.length() <= 0 || pattern.length() <= 0) return false;
    regex re(pattern);
    return regex_search(str, re);
};