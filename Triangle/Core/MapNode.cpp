#include "MapNode.h"
#include "CommonTool.h"
#include <iostream>
#include <memory.h>
#include <string.h>

map_node* mnode_create()
{
    map_node* node = (map_node*)malloc(sizeof(map_node));
    if (node == nullptr) {
        std::cerr << "malloc node for map failed" << std::endl;
        return nullptr;
    }

    // zero all spaces
    memset(node, 0, sizeof(map_node));

    // return to caller
    return node;
}

map_node* mnode_wrap_data(type_n type, void const* key, size_n key_size, 
    void const* val, size_n data_size)
{
    // obtain a new map node
    map_node* node = mnode_create();

    if (node) { // valid ptr
        // copy key
        size_n min = minVal((size_n)64, key_size);
        memcpy(node->key, key, min);
        
        node->key_size = min;
        node->val_size = data_size;
        node->type = type;
        node->val = (void*) val;
    }
    return node;
}

map_node* mnode_copy_data(type_n type, void const* key, size_n key_size, 
    void const* val, size_n data_size)
{
    // obtain a new map node
    map_node* node = mnode_wrap_data(type, key, key_size, nullptr, data_size);

    if (node) {
        // copy data
        node->val = malloc(data_size);

        if (node->val == nullptr) {
            std::cerr << "malloc space for storing data failed" << std::endl;
            mnode_dispose(node);
            return nullptr;
        }

        // copy data to node
        memcpy(node->val, val, data_size);
    }

    return node;
}

void mnode_dispose(map_node* ptr)
{
    if (ptr) { //valid ptr
        if (ptr->val) // valid ptr
        {
            SAFE_FREE(ptr->val); // dispose its content ptr
        }
        SAFE_FREE(ptr); // dispose itself
    }
}
