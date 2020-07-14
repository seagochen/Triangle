#include "HashCode.h"
#include "MD5.h"
#include "SHA256.h"
#include "SHA1.h"
#include <iostream>

char* code_md5(void const* dataset, size_n len)
{
    if (dataset == nullptr) return FALSE;
    unsigned char tmp[16];

    std::string t = md5(dataset, len);

    // malloc space
    char* md5str = (char*)calloc(33, sizeof(char));

    if (md5str == nullptr) {
        std::cerr << "malloc space for md5 failed" << std::endl;
        return nullptr;
    }

    // copy data
    memcpy(md5str, t.c_str(), 32);

    // return to caller
    return md5str;
}

char* code_sha256(void const* dataset, size_n len)
{
    unsigned char* src_c_array = (unsigned char*)dataset;
    std::string hash_hex_str;
    picosha2::hash256_hex_string(src_c_array, src_c_array + len, hash_hex_str);

    // malloc space
    char* sha256str = (char*)calloc(65, sizeof(char));

    if (sha256str == nullptr) {
        std::cerr << "malloc space for sha256 failed" << std::endl;
        return nullptr;
    }

    // copy data
    memcpy(sha256str, hash_hex_str.c_str(), 64);
    
    // return to caller
    return sha256str;
}

char* code_sha1(void const* dataset, size_n len)
{
    SHA1 checksum;
    checksum.update(dataset, len);
    std::string hash = checksum.final();

    // malloc space
    char* sha1str = (char*)calloc(hash.length() + 1, sizeof(char));

    if (sha1str == nullptr) {
        std::cerr << "malloc space for sha1 failed" << std::endl;
        return nullptr;
    }

    // copy data
    memcpy(sha1str, hash.c_str(), hash.length());

    // return to caller
    return sha1str;
}
