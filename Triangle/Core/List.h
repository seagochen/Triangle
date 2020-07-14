#pragma once
#ifndef _TRI_LIST_H_
#define _TRI_LIST_H_

#include "ListNode.h"
#include "TypeDef.h"
#include "SysInterfaces.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct basic_node list;

    // create an empty size list
    EXTERN list* list_create_empty();

    // append a node to the tail of given list
    EXTERN void list_append(list* ptr_list, struct basic_node* ptr_node);

    // append a list to the tail of given list
    EXTERN void list_extend(list* ptr_list, list* ptr_elements);

    // insert a node (or list) to particular position of given list
    EXTERN bool_n list_insert(list* ptr_list, struct basic_node* ptr_node, size_n pos);

    // pop up a node from list
    EXTERN struct basic_node* list_popup(list* ptr_list);

    // remove a node from list by indexing
    EXTERN struct basic_node* list_remove(list* ptr_list, size_n pos);

    // access an element in list, start from [0, n)
    EXTERN struct basic_node const* list_access(list* ptr_list, size_n pos);

    // the number of elements in list
    EXTERN size_n list_elements(list* ptr_list);

    // the content size of list
    EXTERN size_n list_memsize(list* ptr_list);

    // empty the list
    EXTERN void list_empty(list* ptr_list);

    // dispose the list
    EXTERN void list_dispose(list* ptr_list);

#ifdef __cplusplus
};
#endif

/// C++ methods ///
template<typename T>
list* list_convert_array(T* sets, size_n size) {
    list* l = list_create_empty();
    for(size_n i = 0; i < size; i++) {
        T t = sets[i];
        basic_node* node = node_copy_data(sizeof(T), DATA_DEFAULT, &t);
        list_append(l, node);
    }
    return l;
};

#endif