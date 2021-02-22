#include "Core/HashCode.h"
#include "Core/StrUtils.h"
#include "Core/MD5.h"
#include "Core/SHA256.h"
#include "Core/SHA1.h"
#include <iostream>
#include <memory.h>

std::string sge::HashCode::md5(void const* dataset, size_n len)
{
    if (dataset == nullptr) {
        throw PTR_ERROR(__FILE__, __LINE__, "Nullptr detected!");
    }
    
    return MD5::md5(dataset, len);
}

std::string sge::HashCode::sha256(void const* dataset, size_n len)
{
    if (dataset == nullptr) {
        throw PTR_ERROR(__FILE__, __LINE__, "Nullptr detected!");
    }

    char buffer[256] = { 0 };
    unsigned char* src_c_array = (unsigned char*)dataset;
    std::string hash_hex_str;
    picosha2::hash256_hex_string(src_c_array, src_c_array + len, hash_hex_str);
    
    // copy data
    memcpy(buffer, hash_hex_str.c_str(), 64);
    
    // return to caller
    return buffer;
}

std::string sge::HashCode::sha1(void const* dataset, size_n len)
{
    if (dataset == nullptr) {
        throw PTR_ERROR(__FILE__, __LINE__, "Nullptr detected!");
    }

    char buffer[256] = { 0 };
    SHA1 checksum;
    checksum.update(dataset, (int) len);
    std::string hash = checksum.final();

    // copy data
    memcpy(buffer, hash.c_str(), hash.length());

    // return to caller
    return buffer;
}