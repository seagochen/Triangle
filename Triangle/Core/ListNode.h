#pragma once
#ifndef _TRI_LIST_NODE_H_
#define _TRI_LIST_NODE_H_

#include "TypeDef.h"
#include "SysInterfaces.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct basic_node {
        void*  content;
        size_n size;
        type_n type;

        // pointer to prev node
        basic_node* prev;
        
        // pointer to next node
        basic_node* next;
    };

    // create an empty node
    EXTERN struct basic_node* node_create();

    // create a node with data wrapped
    EXTERN struct basic_node* node_wrap_data(size_n data_size, type_n type, void const* ptr_data = nullptr);

    // create a node with data copied
    EXTERN struct basic_node* node_copy_data(size_n data_size, type_n type, void const* ptr_data = nullptr);

    // dispose a node
    EXTERN void node_dispose(struct basic_node* ptr);

#ifdef __cplusplus
}
#endif

#endif
