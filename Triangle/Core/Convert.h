#pragma once
#ifndef _TRI_CONVERT_H_
#define _TRI_CONVERT_H_

#include "SysInterfaces.h"
#include "TypeDefinition.h"
#include <string>

namespace sge {

    class Converter {

    public:

        EXTERN static int_n str_to_int(std::string str);

        EXTERN static long_n str_to_long(std::string str);

        EXTERN static float_n str_to_float(std::string str);

        EXTERN static double_n str_to_double(std::string str);

        EXTERN static bool_n int_to_str(int_n const n, std::string &str);

        EXTERN static bool_n long_to_str(long_n const n, std::string& str);

        EXTERN static bool_n float_to_str(float_n const n, std::string& str);

        EXTERN static bool_n double_to_str(double_n const n, std::string& str);

        /**
        * convert int_n to byte_n array
        * @param n, the number to convert
        * @param p, the pointer could be a nullptr
        */
        EXTERN static byte_n* itob(int_n const n, byte_n** p = nullptr);

        /**
        * convert long_n to byte_n array
        * @param n, the number to convert
        * @param p, the pointer could be a nullptr
        */
        EXTERN static byte_n* ltob(long_n const n, byte_n** p = nullptr);

        /**
        * convert float_n to byte_n array
        * @param n, the number to convert
        * @param p, the pointer could be a nullptr
        */
        EXTERN static byte_n* ftob(float_n const n, byte_n** p = nullptr);

        /**
        * convert double_n to byte_n array
        * @param n, the number to convert
        * @param p, the pointer could be a nullptr
        */
        EXTERN static byte_n* dtob(double_n const n, byte_n** p = nullptr);

        /**
        * convert byte_n array to int_n
        * @param n, the number to convert
        * @param p, the pointer could be a nullptr
        */
        EXTERN static int_n btoi(byte_n const* p);

        /**
        * convert byte_n array to long_n
        * @param n, the number to convert
        */
        EXTERN static long_n btol(byte_n const* p);

        /**
        * convert byte_n array to float_n
        * @param n, the number to convert
        */
        EXTERN static float_n btof(byte_n const* p);

        /**
        * convert byte_n array to double_n
        * @param n, the number to convert
        */
        EXTERN static double_n btod(byte_n const* p);
    };

};

#endif
