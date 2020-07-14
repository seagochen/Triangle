#pragma once
#ifndef _TRI_MAP_NODE_H_
#define _TRI_MAP_NODE_H_

#include "TypeDef.h"
#include "SysInterfaces.h"

struct map_node {
    byte_n key[65]; // 64 bytes available, the last should always be 0
    size_n key_size;
    
    void* val;
    size_n val_size;
    
    type_n type;

    // ptr to prev
    struct map_node* prev;
    struct map_node* next;
};

#if __cplusplus
extern "C" {
#endif

    // create an empty node
    EXTERN struct map_node* mnode_create();

    // create a node with data wrapped
    EXTERN struct map_node* mnode_wrap_data(
        type_n type, 
        void const* key, size_n key_size,
        void const* val, size_n data_size);

    // create a node with data copied
    EXTERN struct map_node* mnode_copy_data(
        type_n type,
        void const* key, size_n key_size,
        void const* val, size_n data_size);

    // dispose a node
    EXTERN void mnode_dispose(struct map_node* node);

#if __cplusplus
};
#endif


#endif