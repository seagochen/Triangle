#pragma once
#ifndef _TRI_HASH_CODE_H_
#define _TRI_HASH_CODE_H_

#include "SysInterfaces.h"
#include "TypeDefinition.h"
#include <string>

namespace sge {

    class HashCode {
    //private:
        //static char buffer[128];

    public:

        // get the string of md5
        EXTERN static std::string md5(void const* dataset, size_n len);

        // get the string of sha256
        EXTERN static std::string sha256(void const* dataset, size_n len);

        // get the string of sha1
        EXTERN static std::string sha1(void const* dataset, size_n len);
    };
};

#endif
