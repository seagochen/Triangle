#include "Digits.h"
#if _WIN32
#include <malloc.h>
#endif
#include <stdlib.h>
#include <string.h>

byte_n const* convert_itob(int_n const n, byte_n** p)
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

byte_n const* convert_ltob(long_n const n, byte_n** p)
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

byte_n const* convert_ftob(float_n const n, byte_n** p)
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

byte_n const* convert_dtob(double_n const n, byte_n** p)
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

int_n const convert_btoi(byte_n* p)
{
    if (p == nullptr) return 0;

    int_n* temp = (int_n*)p;
    return *temp;
}

long_n const convert_btol(byte_n* p)
{
    if (p == nullptr) return 0;

    long_n* temp = (long_n*)p;
    return *temp;
}

float_n const convert_btof(byte_n* p)
{
    if (p == nullptr) return 0;

    float_n* temp = (float_n*)p;
    return *temp;
}

double_n const convert_btod(byte_n* p)
{
    if (p == nullptr) return 0;

    double_n* temp = (double_n*)p;
    return *temp;
}
