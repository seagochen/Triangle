#include "Map.h"
#include "CommonTool.h"
#include <iostream>

map_node* map_create_empty()
{
    map_node* ptr_head = mnode_create();
    map_node* ptr_tail = mnode_create();

    if (ptr_head == nullptr || ptr_tail == nullptr) {
        std::cerr << "list_create_empty failed" << std::endl;
        mnode_dispose(ptr_head);
        mnode_dispose(ptr_tail);
        return nullptr;
    }

    ptr_head->next = ptr_tail;
    ptr_tail->prev = ptr_head;

    return ptr_head;
}

bool_n are_same_key(map_node* n1, map_node* n2) {
    if (n1 == nullptr || n2 == nullptr) {
        std::cerr << "cannot compare nullptr nodes" << std::endl;
        return FALSE;
    }

    // convert the key to a 4-nums of long array
    long_n* key1 = (long_n*)n1->key;
    long_n* key2 = (long_n*)n2->key;

    return key1[0] == key2[0] and
        key1[1] == key2[1] and
        key1[2] == key2[2] and
        key1[3] == key2[3];
}

void map_append(map_node* m, map_node* node)
{
    if (m == nullptr) {
        std::cerr << "append node failed, cannot append node to a null list" << std::endl;
        return;
    }

    if (node == nullptr) {
        std::cerr << "append node failed, cannot append null node to a list" << std::endl;
        return;
    }

    // append the node to the tail
    map_node* ptr = m;
    for (; ptr->next != nullptr; ptr = ptr->next) {
        // has data inside
        if (ptr->val_size > 0) {
            // if the node has the same node
            if (are_same_key(ptr, node) == TRUE) {

                // update the value
                map_node* prev = ptr->prev;
                map_node* next = ptr->next;

                // relink
                prev->next = node;
                next->prev = node;
                node->prev = prev;
                node->next = next;

                // dispose currrent node
                mnode_dispose(ptr);
                return;
            }
        }
    }

    // nothing found, just append the node to the tail of list
    map_node* prev = ptr->prev;
    map_node* tail = ptr;

    // link the node to the list
    node->next = tail;
    node->prev = prev;
    prev->next = node;
    tail->prev = node;
}

bool_n have_the_key(map_node* node, void* key, size_n size) {
    if (node == nullptr || key == nullptr) {
        std::cerr << "cannot compare nullptr keys" << std::endl;
        return FALSE;
    }

    // convert the key to a 4-nums of long array
    size_n min = minVal(size, (size_n)64);
    byte_n* key_ref = (byte_n*)key;
    for (int i = 0; i < size; i++) {
        if (node->key[i] != key_ref[i]) return FALSE;
    }

    return TRUE;
}

map_node* map_remove(map_node* m, void const* key, size_n const size)
{
    if (m == nullptr) {
        std::cerr << "map container cannot be a null ptr" << std::endl;
        return nullptr;
    }

    for (map_node* ptr = m; ptr->next != nullptr; ptr = ptr->next) {
        if (ptr->val_size > 0) {
            if (have_the_key(ptr, (void*)key, size)) {
                map_node* prev = ptr->prev;
                map_node* next = ptr->next;

                // relink
                prev->next = next;
                next->prev = prev;

                ptr->next = ptr->prev = nullptr;

                // return to caller
                return ptr;
            }
        }
    }

    return nullptr;
}

map_node const* map_access(map_node* m, void const* key, size_n const size)
{
    if (m == nullptr) {
        std::cerr << "map container cannot be a null ptr" << std::endl;
        return nullptr;
    }

    for (map_node* ptr = m; ptr->next != nullptr; ptr = ptr->next) {
        if (ptr->val_size > 0) {
            if (have_the_key(ptr, (void*)key, size)) {
                // return to caller
                return ptr;
            }
        }
    }

    return nullptr;
}

list const* map_keys(map_node* m)
{
    if (m == nullptr) {
        std::cerr << "map container cannot be a null ptr" << std::endl;
        return nullptr;
    }

    list* keys = list_create_empty();

    for (map_node* ptr = m; ptr->next != nullptr; ptr = ptr->next) {
        if (ptr->val_size > 0) {
            
            // copy key to a node
            basic_node* node = node_copy_data(ptr->key_size, DATA_DEFAULT, ptr->key);
            
            // if create the node failed
            if (node == nullptr) return keys;

            // append the node to list
            list_append(keys, node);
        }
    }

    return keys;
}

list const* map_vals(map_node* m)
{
    if (m == nullptr) {
        std::cerr << "map container cannot be a null ptr" << std::endl;
        return nullptr;
    }

    list* vals = list_create_empty();

    for (map_node* ptr = m; ptr->next != nullptr; ptr = ptr->next) {
        if (ptr->val_size > 0) {
            // copy key to a node
            basic_node* node = node_copy_data(ptr->val_size, DATA_DEFAULT, ptr->val);

            // if create the node failed
            if (node == nullptr) return vals;

            // append the node to list
            list_append(vals, node);
        }
    }

    return vals;
}

size_n map_elements(map_node* m)
{
    if (m == nullptr) {
        std::cerr << "map container cannot be a null ptr" << std::endl;
        return -1;
    }

    size_n count = 0;
    for (map_node* ptr = m; ptr->next != nullptr; ptr = ptr->next) {
        if (ptr->val_size > 0) {
            count++;
        }
    }

    return count;
}

void map_empty(map_node* m)
{
    if (m == nullptr) {
        std::cerr << "map cannot be a null" << std::endl;
        return;
    }

    for (map_node* ptr = m; ptr->next != nullptr; ptr = ptr->next) {
        
        // remove this node from map
        if (ptr->val_size > 0) {
            map_node* prev = ptr->prev;
            map_node* next = ptr->next;

            // relink
            prev->next = next;
            next->prev = prev;

            // dispose current node
            mnode_dispose(ptr);

            // relink ptr
            ptr = prev;
        }
    }
}

void map_dispose(map_node* m)
{
    if (map_elements(m) == 0) {
        map_node* head = m;
        map_node* tail = m->next;

        mnode_dispose(head);
        mnode_dispose(tail);
    }
    else {
        map_empty(m);
        map_dispose(m);
    }
}
