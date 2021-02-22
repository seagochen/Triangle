#include "Core/Convert.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

#if _WIN32
#include <malloc.h>
#endif

using namespace sge;

int_n Converter::str_to_int(std::string str) {
    try {
        int_n n = boost::lexical_cast<int_n>(str.c_str(), str.length());
        return n;
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return -1;
}

long_n Converter::str_to_long(std::string str)
{
    try {
        long_n n = boost::lexical_cast<long_n>(str.c_str(), str.length());
        return n;
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return -1;
}

float_n Converter::str_to_float(std::string str)
{
    try {
        float_n n = boost::lexical_cast<float_n>(str.c_str(), str.length());
        return n;
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return -1;
}

double_n Converter::str_to_double(std::string str)
{
    try {
        double_n n = boost::lexical_cast<double_n>(str.c_str(), str.length());
        return n;
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return -1;
}

template<typename T>
size_n number_to_str(T const n, std::string &out)
{
    out = boost::lexical_cast<std::string>(n);
    return out.length();
}

bool_n Converter::int_to_str(int_n const n, std::string& str)
{
    if (number_to_str(n, str) < 0) { return FALSE; }
    return TRUE;
}

bool_n Converter::long_to_str(long_n const n, std::string& str)
{
    if (number_to_str(n, str) < 0) { return FALSE; }
    return TRUE;
}

bool_n Converter::float_to_str(float_n const n, std::string& str)
{
    if (number_to_str(n, str) < 0) { return FALSE; }
    return TRUE;
}

bool_n Converter::double_to_str(double_n const n, std::string& str)
{
    if (number_to_str(n, str) < 0) { return FALSE; }
    return TRUE;
}

byte_n* Converter::itob(int_n const n, byte_n** p)
{
    byte_n* temp = nullptr;
    if (p == nullptr || *p == nullptr) {
        temp = (byte_n*)malloc(sizeof(int_n));
    }
    else {
        temp = *p;
    }

    // to avoid nullptr
    if (temp == nullptr) return nullptr;

    // convert data to ptr
    memcpy(temp, &n, sizeof(int_n));
    return temp;
}

byte_n* Converter::ltob(long_n const n, byte_n** p)
{
    byte_n* temp = nullptr;
    if (p == nullptr || *p == nullptr) {
        temp = (byte_n*)malloc(sizeof(long_n));
    }
    else {
        temp = *p;
    }

    // to avoid nullptr
    if (temp == nullptr) return nullptr;

    // convert data to ptr
    memcpy(temp, &n, sizeof(long_n));
    return temp;
}

byte_n* Converter::ftob(float_n const n, byte_n** p)
{
    byte_n* temp = nullptr;
    if (p == nullptr || *p == nullptr) {
        temp = (byte_n*)malloc(sizeof(float_n));
    }
    else {
        temp = *p;
    }

    // to avoid nullptr
    if (temp == nullptr) return nullptr;

    // convert data to ptr
    memcpy(temp, &n, sizeof(float_n));
    return temp;
}

byte_n* Converter::dtob(double_n const n, byte_n** p)
{
    byte_n* temp = nullptr;
    if (p == nullptr || *p == nullptr) {
        temp = (byte_n*)malloc(sizeof(double_n));
    }
    else {
        temp = *p;
    }

    // to avoid nullptr
    if (temp == nullptr) return nullptr;

    // convert data to ptr
    memcpy(temp, &n, sizeof(double_n));
    return temp;
}

EXTERN int_n Converter::btoi(byte_n const* p)
{
    if (p == nullptr) return 0;

    int_n* temp = (int_n*)p;
    return *temp;
}

long_n Converter::btol(byte_n const* p)
{
    if (p == nullptr) return 0;

    long_n* temp = (long_n*)p;
    return *temp;
}

float_n Converter::btof(byte_n const* p)
{
    if (p == nullptr) return 0;

    float_n* temp = (float_n*)p;
    return *temp;
}

EXTERN double_n Converter::btod(byte_n const* p)
{
    if (p == nullptr) return 0;

    double_n* temp = (double_n*)p;
    return *temp;
}
