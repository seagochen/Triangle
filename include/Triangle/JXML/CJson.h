#pragma once
#ifndef _C_JSON_H_
#define _C_JSON_H_

/// triangle core libraries
#include <Core/Core.hpp>

/// c++ libraries
#include <string>
#include <memory>
#include <vector>

/// rapid libraries
#include <rapidjson/document.h>

namespace sge
{
    class JsonHandler
    {
    private:
        rapidjson::Document handler;

    private:
        EXTERN bool_n is_list(std::string key);

    public:
        EXTERN virtual ~JsonHandler();

        enum ValueType {
            NoneEntity,

            VaccumValue,
            BooleanValue,
            IntegerValue,
            DoubleValue,
            StringValue,

            EmptyList,
            VaccumList,
            BooleanList,
            IntegerList,
            DoubleList,
            StringList,
            ArrayList,
            JsonList,

            JsonObject
        };

    public:

        /*-------------------------------------------------------------------------*/
        
        /// <summary>
        /// default constructor
        /// </summary>
        EXTERN JsonHandler();

        /// <summary>
        /// default constructor with string
        /// </summary>
        /// <param name="str">json string or path to a json file</param>
        EXTERN JsonHandler(std::string& str);

        /*-------------------------------------------------------------------------*/

        EXTERN std::string to_str(bool_n well_format=FALSE);

        EXTERN bool_n has_item(std::string key);

        EXTERN std::vector<std::string> keys();

        EXTERN ValueType item_type(std::string key);

        EXTERN void remove(std::string key);
        
        EXTERN void clear();

        /*-------------------------------------------------------------------------*/

        EXTERN JsonHandler& set_bool(std::string key, bool_n b);

        EXTERN bool_n get_bool(std::string key);

        
        EXTERN JsonHandler& set_int(std::string key, int_n n);

        EXTERN int_n get_int(std::string key);

        
        EXTERN JsonHandler& set_double(std::string key, double_n n);

        EXTERN double_n get_double(std::string key);

        
        EXTERN JsonHandler& set_string(std::string key, std::string str);

        EXTERN const char* get_string(std::string key);


        EXTERN JsonHandler& set_null(std::string key);

        EXTERN bool_n is_null(std::string key);

        /*-------------------------------------------------------------------------*/

        EXTERN JsonHandler& set_bool_list(std::string key, bool_n list[], size_n size);

        EXTERN std::vector<bool_n> get_bool_list(std::string key);


        EXTERN JsonHandler& set_int_list(std::string key, int_n list[], size_n size);

        EXTERN std::vector<int_n> get_int_list(std::string key);


        EXTERN JsonHandler& set_double_list(std::string key, double_n list[], size_n size);

        EXTERN std::vector<double_n> get_double_list(std::string key);


        EXTERN JsonHandler& set_string_list(std::string skey, const char* list[], size_n elems);

        EXTERN std::vector<std::string> get_string_list(std::string key);


        EXTERN JsonHandler& set_json(std::string key, std::string json);

        EXTERN JsonHandler& set_json(std::string key, JsonHandler& json);

        EXTERN std::string get_json(std::string key);
    };
} // namespace sge

#endif