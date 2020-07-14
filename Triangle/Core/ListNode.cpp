#include "ListNode.h"
#include <stdlib.h>
#include <memory.h>
#include <iostream>

typedef struct basic_node node;

struct basic_node* node_create()
{
    node* n = (node*)malloc(sizeof(node));
    if (n == nullptr) {
        std::cerr << "create node failed" << std::endl;
        return nullptr;
    }

    // set all contents to zero
    memset(n, 0, sizeof(node));
    return n;
}

struct basic_node* node_wrap_data(size_n data_size, type_n type, void const* ptr_data)
{
    node* n = node_create();
    if (n == nullptr) return nullptr;

    n->size = data_size;
    n->type = type;
    n->content = (void*)ptr_data;

    return n;
}

struct basic_node* node_copy_data(size_n data_size, type_n type, void const* ptr_data)
{
    node* n = node_create();
    if (n == nullptr) return nullptr;

    n->size = data_size;
    n->type = type;

    // copy data
    n->content = calloc(data_size, sizeof(byte_n));
    if (n->content == nullptr) {
        std::cerr << "malloc ptr content failed" << std::endl;
        node_dispose(n);
        return nullptr;
    }

    // copy data to memory
    memcpy(n->content, ptr_data, data_size);

    // return node
    return n;
}

void node_dispose(struct basic_node* ptr)
{
    if (ptr == nullptr) return;

    // free elements
    SAFE_FREE(ptr->content)
    SAFE_FREE(ptr);
}
