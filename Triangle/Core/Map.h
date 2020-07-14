#pragma once
#ifndef _TRI_MAP_H_
#define _TRI_MAP_H_

#include "TypeDef.h"
#include "SysInterfaces.h"
#include "List.h"
#include "MapNode.h"


#if __cplusplus
extern "C" {
#endif

    // create a map to storing the key-value pair
    EXTERN map_node* map_create_empty();

    // append a key-val node to the map
    EXTERN void map_append(map_node* m, map_node* node);

    // remove a key-val pair from the map by using a key
    EXTERN map_node* map_remove(map_node* m, void const* key, size_n const size);

    // access an element by given a key
    EXTERN map_node const* map_access(map_node* m, void const* key, size_n const size);

    // use this method to get a copy of the keys list
    EXTERN list const* map_keys(map_node* m);

    // use this method to get a copy of the vals list 
    EXTERN list const* map_vals(map_node* m);

    // elements in this map
    EXTERN size_n map_elements(map_node* m);

    // empty this map
    EXTERN void map_empty(map_node* m);

    // dispose this map
    EXTERN void map_dispose(map_node* m);

#if __cplusplus
};
#endif


#endif
