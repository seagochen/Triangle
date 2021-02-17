#include "CJson.h"
#include <rapidjson/writer.h>
#include <string.h>
#include <memory.h>

/// rapid libraries
#include <rapidjson/document.h>

using namespace std;
using namespace sge;
using namespace rapidjson;



JsonHandler::~JsonHandler() {}


JsonHandler::JsonHandler() { handler.Parse("{}"); }


JsonHandler::JsonHandler(string& str)
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


string JsonHandler::to_str()
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    handler.Accept(writer);

    return std::string(buffer.GetString());
}


bool_n JsonHandler::has_item(string key)
{
    return handler.HasMember(key.c_str());
}


bool_n sge::JsonHandler::is_list(std::string key)
{
    return has_item(key) && handler[key.c_str()].IsArray();
}


JsonHandler& JsonHandler::set_null(std::string k)
{
    if (!has_item(k)) {
        // create a pair value
        Value val;
        Value key(k.c_str(), k.length(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetNull();
    }

    // return this
    return *this;
}


bool_n JsonHandler::is_null(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].IsNull();
    }

    return FALSE;
}


JsonHandler& JsonHandler::set_bool(std::string k, bool_n b)
{
    if (!has_item(k)) {
        // create a pair value
        Value val(true);
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetBool(b);
    }
 

    // return this
    return *this;
}


bool_n JsonHandler::get_bool(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].GetBool();
    }

    return FALSE;
}


bool_n JsonHandler::is_bool(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].IsBool();
    }
    return FALSE;
}


JsonHandler& JsonHandler::set_int(std::string k, int_n n)
{
    if (!has_item(k)) {
        // create a pair value
        Value val(n);
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetInt(n);
    }

    // return this
    return *this;
}


int_n JsonHandler::get_int(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].GetInt();
    }

    return 0;
}


bool_n JsonHandler::is_int(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].IsInt();
    }

    return FALSE;
}


JsonHandler& JsonHandler::set_double(std::string k, double_n n)
{
    if (!has_item(k)) {
        // create a pair value
        Value val(n);
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetDouble(n);
    }

    // return this
    return *this;
}


double_n JsonHandler::get_double(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].GetDouble();
    }

    return 0;
}


bool_n JsonHandler::is_double(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].IsDouble();
    }

    return FALSE;
}


JsonHandler& JsonHandler::set_string(std::string k, std::string str)
{
    if (!has_item(k)) {
        // create a pair value
        Value val(str.c_str(), str.length(), handler.GetAllocator());
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetString(str.c_str(), str.length(), handler.GetAllocator());
    }

    // return this
    return *this;
}


const char* JsonHandler::get_string(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].GetString();
    }

    return nullptr;
}


void JsonHandler::clear() { handler.RemoveAllMembers(); }


vector<std::string> JsonHandler::keys()
{
    vector<string> keys;

    // iterate the given json object and add each item to handler
    rapidjson::Value::MemberIterator m;
    for (m = handler.MemberBegin(); m != handler.MemberEnd(); m++) {

        std::string str(m->name.GetString());
        keys.push_back(str);
    }

    return keys;
}


template<typename T>
void generic_append_array(Document& handler, string k, T list[], size_n size)
{
    // create an object type
    Value key(k.c_str(), k.size(), handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    Document::AllocatorType& allocator = handler.GetAllocator();
    // value object to stores the array
    Value value(rapidjson::kArrayType);

    // iterative appending the values
    for (int i = 0; i < size; i++) {
        value.PushBack(list[i], allocator);
    }

    // add the value to the document
    handler.AddMember(key, value, allocator);
}


template<typename T>
void generic_update_array(Document& handler, string k, T list[], size_n size)
{
    // get value object from document
    Value& val = handler[k.c_str()];

    // clear entities up
    val.RemoveAllMembers();

    // to get the allocator handler to iteratively append the values to the value object
    rapidjson::Document::AllocatorType& allocator = handler.GetAllocator();

    // iterative appending the values
    for (int i = 0; i < size; i++) {
        value.PushBack(list[i], allocator);
    }
}


JsonHandler& JsonHandler::set_bool_list(std::string key, bool_n list[], size_n size)
{
    if (!has_item(key)) {
        generic_append_array<bool_n>(handler, key, list, size);
    }
    else {
        generic_update_array<bool_n>(handler, key, list, size);
    }

    // return this
    return *this;
}


std::vector<bool_n> sge::JsonHandler::get_bool_list(std::string key)
{
    vector<bool_n> list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];
        
        for (SizeType i = 0; i < a.Size(); i++) {
            list.push_back(a[i].GetBool());
        }
    }

    return list;
}


JsonHandler& sge::JsonHandler::set_int_list(std::string key, int_n list[], size_n size)
{
    if (!has_item(key)) {
        generic_append_array<int_n>(handler, key, list, size);
    }
    else {
        generic_update_array<int_n>(handler, key, list, size);
    }

    // return this
    return *this;
}


std::vector<int_n> sge::JsonHandler::get_int_list(std::string key)
{
    vector<int_n> list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            list.push_back(a[i].GetInt());
        }
    }

    return list;
}


JsonHandler& sge::JsonHandler::set_double_list(std::string key, double_n list[], size_n size)
{
    if (!has_item(key)) {
        generic_append_array<double_n>(handler, key, list, size);
    }
    else {
        generic_update_array<double_n>(handler, key, list, size);
    }

    // return this
    return *this;
}

std::vector<double_n> sge::JsonHandler::get_double_list(std::string key)
{
    vector<double_n> list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            list.push_back(a[i].GetDouble());
        }
    }

    return list;
}

JsonHandler& sge::JsonHandler::set_string_list(std::string k, const char* list[], size_n elems)
{
    if (!has_item(k)) {
        // create an object key
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // to get the allocator handler to iteratively append the values to the value object
        Document::AllocatorType& allocator = handler.GetAllocator();

        // value object to stores the array
        Value value(kArrayType);

        // iterative appending the values
        for (int i = 0; i < elems; i++) {
            Value item(list[i], strlen(list[i]), handler.GetAllocator());
            value.PushBack(item, allocator);
        }

        // add the value to the document
        handler.AddMember(key, value, allocator);
    }
    else {
        Value& val = handler[k.c_str()];
        val.RemoveAllMembers();

        // to get the allocator handler to iteratively append the values to the value object
        Document::AllocatorType& allocator = handler.GetAllocator();

        // iterative appending the values
        for (int i = 0; i < elems; i++) {
            Value item(list[i], strlen(list[i]), handler.GetAllocator());
            val.PushBack(item, allocator);
        }
    }



    // return this
    return *this;
}

std::vector<std::string> sge::JsonHandler::get_string_list(std::string key)
{
    vector<string> list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            string str(a[i].GetString());
            list.push_back(str);
        }
    }

    return list;
}

JsonHandler& sge::JsonHandler::set_json(std::string k, std::string json)
{
    if (!has_item(k)) {
        
        // create key-value pair
        Value key(k.c_str(), k.size(), handler.GetAllocator());
        Value value(kObjectType);

        JsonHandler handler(json);

        for (string sk : handler.keys()) {
            if (handler.is_bool(sk)) {
                //TODO
            }
        }

        
    }

   

    return *this;
}

