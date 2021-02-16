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

    public:
        EXTERN ~JsonHandler();

    public:
        /// <summary>
        /// create an empty json object
        /// </summary>
        EXTERN JsonHandler();

        /// <summary>
        /// parse a file with json string or just a json string directly
        /// </summary>
        /// <param name="str">the file path, or the json string</param>
        EXTERN JsonHandler(const std::string& str);

        /// <summary>
        /// test json object contains a valid object with the given key
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        EXTERN bool_n has_item(std::string key);

        /// <summary>
        /// append bool value to json string
        /// </summary>
        /// <param name="key"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_item(std::string key, bool_n b);

        /// <summary>
        /// append integer to json string
        /// </summary>
        /// <param name="key"></param>
        /// <param name="n"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_item(std::string key, int_n n);

        /// <summary>
        /// append double to json string
        /// </summary>
        /// <param name="key"></param>
        /// <param name="n"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_item(std::string key, double_n n);

        /// <summary>
        /// append string to json string
        /// </summary>
        /// <param name="key"></param>
        /// <param name="str"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_item(std::string key, std::string str);

        /// <summary>
        /// 
        /// </summary>
        EXTERN JsonHandler& append_null(std::string key);

        /// <summary>
        /// append bool array to json string
        /// </summary>
        /// <param name="key"></param>
        /// <param name="list"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_array(std::string key, bool_n list[], size_n size);

        /// <summary>
        /// append integer array to json string
        /// </summary>
        /// <param name="key"></param>
        /// <param name="list"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_array(std::string key, int_n list[], size_n size);

        /// <summary>
        /// append double array to json string
        /// </summary>
        /// <param name="key"></param>
        /// <param name="list"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_array(std::string key, double_n list[], size_n size);


        /// <summary>
        /// append string array to json string
        /// </summary>
        /// <param name="key"></param>
        /// <param name="list"></param>
        /// <param name="elems"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_array(std::string key, const char* list[], size_n elems);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <param name="handler"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_json(std::string key, JsonHandler& handler);
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <param name="handler"></param>
        /// <returns></returns>
        EXTERN JsonHandler& append_json(std::string key, std::string json);

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        EXTERN std::vector<std::string> keys();

        /// <summary>
        /// assign json handler to another, operator overload
        /// </summary>
        /// <param name="D"></param>
        EXTERN void operator=(const JsonHandler& D);

        /// <summary>
        /// get string from json handler
        /// </summary>
        EXTERN std::string to_cstr();
    };
} // namespace sge


#endif