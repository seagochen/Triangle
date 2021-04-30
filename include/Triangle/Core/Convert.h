#pragma once
#ifndef _TRI_CONVERT_H_
#define _TRI_CONVERT_H_

#include "SysInterfaces.h"
#include "TypeDefinition.h"
#include <string>

namespace sge {

    class Converter {

    public:

        /// <summary>
        /// convert the string number to integer type
        /// </summary>
        EXTERN static int_n str_to_int(std::string str);

        /// <summary>
        /// convert the string number to long type
        /// </summary>
        EXTERN static long_n str_to_long(std::string str);

        /// <summary>
        /// convert the string number to float type
        /// </summary>
        EXTERN static float_n str_to_float(std::string str);

        /// <summary>
        /// convert the string number to double type
        /// </summary>
        EXTERN static double_n str_to_double(std::string str);

        /// <summary>
        /// convert the integer to string type
        /// </summary>
        EXTERN static bool_n int_to_str(int_n const n, std::string &str);

        /// <summary>
        /// convert the long to string type
        /// </summary>
        EXTERN static bool_n long_to_str(long_n const n, std::string& str);

        /// <summary>
        /// convert the float to string type
        /// </summary>
        EXTERN static bool_n float_to_str(float_n const n, std::string& str);

        /// <summary>
        /// convert the double to string type
        /// </summary>
        EXTERN static bool_n double_to_str(double_n const n, std::string& str);

        /// <summary>
        /// convert int_n to byte_n array
        /// </summary>
        /// <param name="n">the number to convert</param>
        /// <param name="p">json the pointer could be a nullptr</param>
        EXTERN static byte_n* itob(int_n const n, byte_n** p = nullptr);

        /// <summary>
        /// convert long_n to byte_n array
        /// </summary>
        /// <param name="n">the number to convert</param>
        /// <param name="p">json the pointer could be a nullptr</param>
        EXTERN static byte_n* ltob(long_n const n, byte_n** p = nullptr);

        /// <summary>
        /// convert float_n to byte_n array
        /// </summary>
        /// <param name="n">the number to convert</param>
        /// <param name="p">json the pointer could be a nullptr</param>
        EXTERN static byte_n* ftob(float_n const n, byte_n** p = nullptr);

        /// <summary>
        /// convert double_n to byte_n array
        /// </summary>
        /// <param name="n">the number to convert</param>
        /// <param name="p">json the pointer could be a nullptr</param> 
        EXTERN static byte_n* dtob(double_n const n, byte_n** p = nullptr);

        /// <summary>
        /// convert a byte array to int_n
        /// </summary>
        /// <param name="p">the pointer to the byte array</param> 
        EXTERN static int_n btoi(byte_n const* p);

        /// <summary>
        /// convert a byte array to long_n
        /// </summary>
        /// <param name="p">the pointer to the byte array</param> 
        EXTERN static long_n btol(byte_n const* p);

        /// <summary>
        /// convert a byte array to float_n
        /// </summary>
        /// <param name="p">the pointer to the byte array</param> 
        EXTERN static float_n btof(byte_n const* p);

        /// <summary>
        /// convert a byte array to double_n
        /// </summary>
        /// <param name="p">the pointer to the byte array</param> 
        EXTERN static double_n btod(byte_n const* p);
    };

};

#endif
