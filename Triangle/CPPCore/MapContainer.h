#pragma once
#ifndef _TRI_UNORDERED_CONTAINER_H_
#define _TRI_UNORDERED_CONTAINER_H_

#include "../Core/TypeDef.h"
#include "../Core/Map.h"
#include "DLLExpo.h"
#include <string>

class MapSet {
public:
    DLL_EXPO static map_node* mkSet(std::string key, void const* val, size_n valsize);

    DLL_EXPO static map_node* mkSet(double_n key, void const* val, size_n valsize);

    DLL_EXPO static map_node* mkSet(long_n key, void const* val, size_n valsize);

    DLL_EXPO static map_node* mkSet(int_n key, void const* val, size_n valsize);

    DLL_EXPO static map_node* mkSet(std::string key, std::string val);

    DLL_EXPO static map_node* mkSet(double_n key, std::string val);

    DLL_EXPO static map_node* mkSet(long_n key, std::string val);

    DLL_EXPO static map_node* mkSet(int_n key, std::string val);

    DLL_EXPO static map_node* mkSet(void const* key, size_n keysize,
        void const* val, size_n valsize);

    DLL_EXPO static std::string toStrVal(map_node* node);


public: /// generic methods
    template<typename V>
    static V* toObjVal(map_node* node) {
        if (node != nullptr) {
            V* obj = (V*) node->val;
            return obj;
        }
    }
};

#include "Iterator.hpp"


class MapContainer : public Iterator<map_node>
{
public:

    // loop, return true if not reaches list's tail
    virtual bool_n has_next() override {
        if (anchor != nullptr) {
            return anchor->next != nullptr;
        }
        return FALSE;
    };

    // loop, return true if not reaches list's head
    virtual bool_n has_prev() override {
        if (anchor != nullptr) {
            return anchor->prev != nullptr;
        }
        return FALSE;
    };

    // access the element
    virtual map_node* ptr() override {
        if (anchor->val_size > 0) {
            return anchor;
        }
        return nullptr;
    };

    // move to next element
    virtual void next() override {
        if (has_next()) {
            anchor = anchor->next;
        }
    };

    // move to prev element
    virtual void prev() override {
        if (has_prev()) {
            anchor = anchor->prev;
        }
    };

    // reset the iterator
    virtual void reset() override {
        anchor = container;
        if (has_next()) {
            next();
        }
    }

private:
    size_n items;
    map_node* container;
    map_node* anchor;

public:

    DLL_EXPO MapContainer();

    DLL_EXPO ~MapContainer();

public:
    DLL_EXPO bool_n append(map_node* node);

    DLL_EXPO bool_n remove(std::string key, map_node* val);

    DLL_EXPO bool_n remove(int_n key, map_node* val);
    
    DLL_EXPO bool_n remove(long_n key, map_node* val);

    DLL_EXPO bool_n remove(double_n key, map_node* val);

    DLL_EXPO map_node const* operator[](std::string key);

    DLL_EXPO map_node const* operator[](int_n key);

    DLL_EXPO map_node const* operator[](long_n key);

    DLL_EXPO map_node const* operator[](double_n key);

    DLL_EXPO size_n const length();

    DLL_EXPO void clean();

    DLL_EXPO list const* keys();

    DLL_EXPO list const* vals();
};

#endif