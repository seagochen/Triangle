#include "CJson.h"
#include <rapidjson/writer.h>
#include <string.h>
#include <memory.h>

using namespace sge;

JsonHandler::~JsonHandler()
{
}

JsonHandler::JsonHandler()
{
    // an empty json string
    handler.Parse("{}");
}

JsonHandler::JsonHandler(const std::string& str)
{
    // parse an empty string
    if (str.empty()) {
        handler.Parse("{}");
    } 
    elif(Validator::match_filepath(str)) { 
        // this string contains a valid file path
        const char* fz = FileIO::read(str);
        handler.Parse(fz);
        
        // to avoid memory leak
        SAFE_DELETE(fz);
    }
    else {
        // just a string, try to parse it directly
        handler.Parse(str.c_str());
    }
}

bool_n JsonHandler::has_item(std::string key)
{
    return handler.HasMember(key.c_str());
}

JsonHandler& sge::JsonHandler::append_null(std::string skey)
{
    // create a pair value
    rapidjson::Value val;
    rapidjson::Value key(skey.c_str(), skey.size(),
        handler.GetAllocator());
    val.SetNull();

    // add val to document
    handler.AddMember(key, val, handler.GetAllocator());

    // return this
    return *this;
}

JsonHandler& JsonHandler::append_item(std::string skey, bool_n b)
{
    // create a pair value
    rapidjson::Value val;
    rapidjson::Value key(skey.c_str(), skey.size(),
        handler.GetAllocator());
    val.SetBool(true);

    // add val to document
    handler.AddMember(key, val, handler.GetAllocator());

    // return this
    return *this;
}

JsonHandler& JsonHandler::append_item(std::string skey, int_n n)
{
    // create a pair value
    rapidjson::Value val;
    rapidjson::Value key(skey.c_str(), skey.size(),
        handler.GetAllocator());
    val.SetInt(n);

    // add val to document
    handler.AddMember(key, val, handler.GetAllocator());

    // return this
    return *this;
}

JsonHandler& JsonHandler::append_item(std::string skey, double_n n)
{
    // create a pair value
    rapidjson::Value val;
    rapidjson::Value key(skey.c_str(), skey.size(),
        handler.GetAllocator());
    val.SetDouble(n);

    // add val to document
    handler.AddMember(key, val, handler.GetAllocator());

    // return this
    return *this;
}

JsonHandler& JsonHandler::append_item(std::string skey, std::string str)
{
    // create a pair value
    rapidjson::Value val;
    rapidjson::Value key(skey.c_str(), skey.size(),
        handler.GetAllocator());
    val.SetString(str.c_str(), str.length());

    // add val to document
    handler.AddMember(key, val, handler.GetAllocator());

    // return this
    return *this;
}

template<typename T>
void generic_append_array(rapidjson::Document &handler,
    std::string skey, T list[], size_n size) 
{
    // create an object type
    rapidjson::Value key(skey.c_str(), skey.size(),
        handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    rapidjson::Document::AllocatorType& allocator = handler.GetAllocator();
    // value object to stores the array
    rapidjson::Value value(rapidjson::kArrayType);

    // iterative appending the values
    for (int i = 0; i < size; i++) {
        value.PushBack(list[i], allocator);
    }

    // add the value to the document
    handler.AddMember(key, value, allocator);
}

JsonHandler& sge::JsonHandler::append_array(std::string key, bool_n list[], size_n size)
{
    // use generic method to avoid wasteful duplication of effort.
    generic_append_array<bool_n>(handler, key, list, size);

    // return this
    return *this;
}

JsonHandler& sge::JsonHandler::append_array(std::string key, int_n list[], size_n size)
{
    // use generic method to avoid wasteful duplication of effort.
    generic_append_array<int_n>(handler, key, list, size);

    // return this
    return *this;
}

JsonHandler& JsonHandler::append_array(std::string skey, const char* list[], size_n elems)
{
    // create an object key
    rapidjson::Value key(skey.c_str(), skey.size(), handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    rapidjson::Document::AllocatorType& allocator = handler.GetAllocator();

    // value object to stores the array
    rapidjson::Value value(rapidjson::kArrayType);

    // iterative appending the values
    for (int i = 0; i < elems; i++) {
        rapidjson::Value val(list[i], strlen(list[i]), handler.GetAllocator());
        value.PushBack(val, allocator);
    }

    // add the value to the document
    handler.AddMember(key, value, allocator);

    // return this
    return *this;
}

JsonHandler& sge::JsonHandler::append_array(std::string key, double_n list[], size_n size)
{
    // use generic method to avoid wasteful duplication of effort.
    generic_append_array<double_n>(handler, key, list, size);

    // return this
    return *this;
}

JsonHandler& JsonHandler::append_json(std::string key, JsonHandler& handler)
{
    // parsing existing json string
    return this->append_json(key, handler.to_cstr());
}

JsonHandler& JsonHandler::append_json(std::string skey, std::string json)
{
    // create an object key
    rapidjson::Value key(skey.c_str(), skey.size(), handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    rapidjson::Document::AllocatorType& allocator = handler.GetAllocator();

    // generate nested object
    rapidjson::Value value(rapidjson::kObjectType);
    JsonHandler sub(json.c_str());

    // iterate the given json object and add each item to handler
    std::vector<std::string> keys = sub.keys();

    // return this
    return *this;
}

void JsonHandler::operator=(const JsonHandler& D)
{
}

std::string JsonHandler::to_cstr()
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer< rapidjson::StringBuffer> writer(buffer);
    handler.Accept(writer);

    return std::string(buffer.GetString());
}


std::vector<std::string> sge::JsonHandler::keys()
{
    std::vector<std::string> keys;

    // iterate the given json object and add each item to handler
    rapidjson::Value::MemberIterator m;
    for (m = handler.MemberBegin(); m != handler.MemberEnd(); m++) {

        std::string str(m->name.GetString());
        keys.push_back(str);
    }

    return keys;
}