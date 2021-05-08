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

        void from_json(std::string str);

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

        // { "foo" : [v1, v2, v3, v4, v5, ..., vn]}
        JsonHandler& set_bool_list(std::string key, bool list[], int size);

        std::vector<bool> get_bool_list(std::string key);


        // { "foo" : [v1, v2, v3, v4, v5, ..., vn]}
        JsonHandler& set_int_list(std::string key, int list[], int size);

        std::vector<int> get_int_list(std::string key);


        // { "foo" : [v1, v2, v3, v4, v5, ..., vn]}
        JsonHandler& set_double_list(std::string key, double list[], int size);

        std::vector<double> get_double_list(std::string key);


        // { "foo" : [v1, v2, v3, v4, v5, ..., vn]}
        JsonHandler& set_string_list(std::string skey, const char* list[], int elems);

        std::vector<std::string> get_string_list(std::string key);


        // { "foo" : {"fo1":"va1", "fo2":"va2", ..., "fon":"van"}}
        JsonHandler& set_json(std::string key, std::string json);

        std::string get_json(std::string key);


        // Json handler as sub json string
        JsonHandler& set_json(std::string key, JsonHandler& json);


        // { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
        JsonHandler& set_multi_int_lists(std::string key, std::vector<std::vector<int>> multi);

        std::vector<std::vector<int>> get_multi_int_lists(std::string key);


        // { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
        JsonHandler& set_multi_bool_lists(std::string key, std::vector<std::vector<bool>> multi);

        std::vector<std::vector<bool>> get_multi_bool_lists(std::string key);


        // { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
        JsonHandler& set_multi_double_lists(std::string key, std::vector<std::vector<double>> multi);

        std::vector<std::vector<double>> get_multi_double_lists(std::string key);


        // { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
        JsonHandler& set_multi_string_lists(std::string key, std::vector<std::vector<std::string>> multi);

        std::vector<std::vector<std::string>> get_multi_string_lists(std::string key);


        // { "foo" : [{"fo1": ...}, {"fo2": ...}, ... {"fon": ...}]}
        JsonHandler& set_multi_json_lists(std::string key, std::vector<std::string> multi);

        JsonHandler& set_multi_json_lists(std::string key, std::vector<JsonHandler> multi);

        std::vector<std::string> get_multi_json_lists(std::string key);
    };
} // namespace sge

#endif