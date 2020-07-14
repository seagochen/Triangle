#include "Convert.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#if _WIN32
#include <malloc.h>
#endif

int_n convert_str_int(char const* str, size_n size)
{
    try {
        int_n n = boost::lexical_cast<int_n>(str, size);
        return n;
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return -1;
}

long_n convert_str_long(char const* str, size_n size)
{
    try {
        long_n n = boost::lexical_cast<long_n>(str, size);
        return n;
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return -1;
}

float_n convert_str_float(char const* str, size_n size)
{
    try {
        float_n n = boost::lexical_cast<float_n>(str, size);
        return n;
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return -1;
}

double_n convert_str_double(char const* str, size_n size)
{
    try {
        double_n n = boost::lexical_cast<double_n>(str, size);
        return n;
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << e.what() << std::endl;
    }

    return -1;
};

template<typename T>
bool_n convert_n_str(T const n, char* out, size_n& size)
{
    if (out == nullptr) {
        std::cerr << "ptr cannot be a null" << std::endl;
        return FALSE;
    }

    std::string str = boost::lexical_cast<std::string>(n);
    memcpy(out, str.c_str(), str.length());
    size = str.length();
    return TRUE;
}

bool_n convert_int_str(int_n const n, char* out, size_n& size)
{
    return convert_n_str<int_n>(n, out, size);
};

bool_n convert_long_str(long_n const n, char* out, size_n& size)
{
    return convert_n_str<long_n>(n, out, size);
};

bool_n convert_float_str(float_n const n, char* out, size_n& size)
{
    return convert_n_str<float_n>(n, out, size);
};

bool_n convert_double_str(double_n const n, char* out, size_n& size)
{
    return convert_n_str<double_n>(n, out, size);
}


size_n tstrlen(char_n const* ptr)
{
    size_n n = 0;
    while (ptr[++n] != 0) {}
    return n;
}


char_n const* cstr_wrap(char const* ptr)
{
    size_n size = strlen(ptr);
    char_n* dst = (char_n*)malloc(sizeof(char_n) * (size + 1));

    if (dst == nullptr) {
        std::cerr << "malloc space for cstr failed" << std::endl;
        return nullptr;
    }

    // set the buffer to zero
    memset(dst, 0, sizeof(char_n) * (size + 1));

    // copy data
    for (size_n i = 0; i < size; i++) {
        dst[i] = ptr[i];
    }

    // return to caller
    return dst;
}

char const* cstr_uwrap(char_n const* ptr)
{
    size_n size = tstrlen(ptr);
    char* dst = (char*)malloc(size);

    if (dst == nullptr) {
        std::cerr << "malloc space for char_n of cstr failed" << std::endl;
        return nullptr;
    }

    // copy data
    for (size_n i = 0; i < size; i++) {
        dst[i] = (char)ptr[i];
    }

    // return to caller
    return dst;
};
