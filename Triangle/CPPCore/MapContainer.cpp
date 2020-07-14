#include "MapContainer.h"
#include <memory.h>
#include <string.h>

map_node* MapSet::mkSet(std::string key, void const* val, size_n valsize)
{
    return mnode_copy_data(DATA_DEFAULT, key.c_str(), key.length(), val, valsize);
}

map_node* MapSet::mkSet(double_n key, void const* val, size_n valsize)
{
    return mnode_copy_data(DATA_DEFAULT, &key, sizeof(key), val, valsize);
}

map_node* MapSet::mkSet(long_n key, void const* val, size_n valsize)
{
    return mnode_copy_data(DATA_DEFAULT, &key, sizeof(key), val, valsize);
}

map_node* MapSet::mkSet(int_n key, void const* val, size_n valsize)
{
    return mnode_copy_data(DATA_DEFAULT, &key, sizeof(key), val, valsize);
}

map_node* MapSet::mkSet(std::string key, std::string val)
{
    return mkSet(key, val.c_str(), val.length());
}

map_node* MapSet::mkSet(double_n key, std::string val)
{
    return mkSet(key, val.c_str(), val.length());
}

map_node* MapSet::mkSet(long_n key, std::string val)
{
    return mkSet(key, val.c_str(), val.length());
}

map_node* MapSet::mkSet(int_n key, std::string val)
{
    return mkSet(key, val.c_str(), val.length());
}

map_node* MapSet::mkSet(void const* key, size_n keysize, void const* val, size_n valsize)
{
    return mnode_copy_data(DATA_DEFAULT, &key, sizeof(key), val, valsize);
}

std::string MapSet::toStrVal(map_node* node)
{
    std::string str = "";

    if (node != nullptr) {
        // assign val to str
        char* cs = (char*)node->val;
        str.assign(cs, node->val_size);
    }

    return str;
}


/********************** Map Container **********************/


MapContainer::MapContainer() : container(nullptr), anchor(nullptr), items(0) {
    if (container == nullptr) {
        container = map_create_empty();
    }
}

MapContainer::~MapContainer()
{
    if (container != nullptr) {
        map_dispose(container);
        container = nullptr;
        anchor = nullptr;
        items = 0;
    }
}

bool_n MapContainer::append(map_node* node)
{
    if (container != nullptr) {

        // append the node to map
        if (node != nullptr) {

            // append a node to map
            map_append(container, node);

            // count increase by one
            items++;

            // return
            return TRUE;
        }
    }
    return FALSE;
}

bool_n MapContainer::remove(std::string key, map_node* val)
{
    if (container != nullptr and length() > 0) {

        // remove entry from map
        map_node* node = map_remove(container, key.c_str(), key.length());

        if (node != nullptr) {
            // map node
            memcpy(val, node, sizeof(map_node));

            // dispose map node
            mnode_dispose(node);

            // count decrease by one
            items--;

            // return
            return TRUE;
        }
    }
    return FALSE;
}

template<typename K>
bool_n remove_by_num_key(map_node* container, K key, map_node* val) {
    
    if (container != nullptr and map_elements(container) > 0) {
        // remove entry from map
        map_node* node = map_remove(container, &key, sizeof(key));

        if (node != nullptr) {
            // map node
            memcpy(val, node, sizeof(map_node));

            // dispose map node
            mnode_dispose(node);

            // return
            return TRUE;
        }
    }
    return FALSE;
}

bool_n MapContainer::remove(int_n key, map_node* val)
{
    if (remove_by_num_key(container, key, val))
    {
        items--;
        return TRUE;
    }
    return FALSE;
}

bool_n MapContainer::remove(long_n key, map_node* val)
{
    if (remove_by_num_key(container, key, val))
    {
        items--;
        return TRUE;
    }
    return FALSE;
}

bool_n MapContainer::remove(double_n key, map_node* val)
{
    if (remove_by_num_key(container, key, val))
    {
        items--;
        return TRUE;
    }
    return FALSE;
}

map_node const* MapContainer::operator[](std::string key)
{
    if (container != nullptr and length() > 0) {
        
        // trying to access map node by given a string key
        map_node const* node = map_access(container, key.c_str(), key.length());

        // return
        return node;
    }

    // return a nullptr
    return nullptr;
}

template<typename K>
map_node const* access(map_node* container, K key) {
    if (container != nullptr and map_elements(container) > 0) {

        // trying to access map node by given a string key
        map_node const* node = map_access(container, &key, sizeof(key));

        // return
        return node;
    }

    // return a nullptr
    return nullptr;
}

map_node const* MapContainer::operator[](int_n key)
{
    return access(container, key);
}

map_node const* MapContainer::operator[](long_n key)
{
    return access(container, key);
}

map_node const* MapContainer::operator[](double_n key)
{
    return access(container, key);
}

size_n const MapContainer::length()
{
    if (container == nullptr) return 0;
    return items;
}

void MapContainer::clean()
{
    if (container != nullptr and length() > 0) {
        map_empty(container);
        items = 0;
    }
}


list const* MapContainer::keys() {
    if (container != nullptr) {
        return map_keys(container);
    }
    return nullptr;
};


list const* MapContainer::vals() {
    if (container != nullptr) {
        return map_vals(container);
    }
    return nullptr;
}