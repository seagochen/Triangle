#include "List.h"
#include <iostream>

typedef struct basic_node node;

// create an empty size list
list* list_create_empty()
{
    node* ptr_head = node_create();
    node* ptr_tail = node_create();

    if (ptr_head == nullptr || ptr_tail == nullptr) {
        std::cerr << "list_create_empty failed" << std::endl;
        node_dispose(ptr_head);
        node_dispose(ptr_tail);
        return nullptr;
    }

    ptr_head->next = ptr_tail;
    ptr_tail->prev = ptr_head;

    return ptr_head;
};

// append a node to the tail of list
void list_append(list* ptr_list, struct basic_node* ptr_node)
{
    if (ptr_list == nullptr) {
        std::cerr << "append node failed, cannot append node to a null list" << std::endl;
        return;
    }

    if (ptr_node == nullptr) {
        std::cerr << "append node failed, cannot append null node to a list" << std::endl;
        return;
    }

    if (ptr_node->next != nullptr and ptr_node->next->size > 0) {// this probably is a list not a node.
        list_extend(ptr_list, ptr_node);
    }
    else {
        // append node from header
        list_insert(ptr_list, ptr_node, 0);
    }
}


void list_extend(list* ptr_list, list* ptr_elements)
{
    if (ptr_list == nullptr) {
        std::cerr << "append list failed, cannot append node to a null list" << std::endl;
        return;
    }

    if (ptr_elements == nullptr) {
        std::cerr << "append list failed, cannot append null node to a list" << std::endl;
        return;
    }

    while (true) {
        basic_node* node = list_popup(ptr_elements);

        if (node != nullptr) {
            list_append(ptr_list, node);
        }

        else {
            break;
        }
    }
}

// insert a node to particular position of list
bool_n list_insert(list* ptr_list, struct basic_node* ptr_node, size_n pos)
{
    if (ptr_list == nullptr) {
        std::cerr << "append node failed, cannot append node to a null list" << std::endl;
        return FALSE;
    }

    if (ptr_node == nullptr) {
        std::cerr << "append node failed, cannot append null node to a list" << std::endl;
        return FALSE;
    }

    if (pos < 0 || pos > list_elements(ptr_list)) {
        std::cerr << "append node pos incorrect" << std::endl;
        return FALSE;
    }

    size_n anchor = 0;
    for (list* ptr = ptr_list; ptr->next != nullptr; ptr = ptr->next) {
        if (anchor == pos) {

            node* header = ptr;
            node* tailer = ptr->next;

            // link node to the correct position
            header->next = ptr_node;
            ptr_node->prev = header;

            ptr_node->next = tailer;
            tailer->prev = ptr_node;

            // break the cycle
            break;
        }

        anchor += 1;
    }

    return TRUE;
};

// pop up a node from list
struct basic_node* list_popup(list* ptr_list)
{
    return list_remove(ptr_list, 0);
};

// remove a node from list by indexing
struct basic_node* list_remove(list* ptr_list, size_n pos)
{
    if (ptr_list == nullptr) {
        std::cerr << "list cannot be a null" << std::endl;
        return nullptr;
    }

    if (pos < 0 || pos >= list_elements(ptr_list)) {
        return nullptr;
    }

    size_n anchor = 0;
    for (list* ptr = ptr_list->next; ptr->next != nullptr; ptr = ptr->next) {
        if (anchor == pos) {
            node* header = ptr->prev;
            node* tailer = ptr->next;

            // link node to the correct position
            header->next = tailer;
            tailer->prev = header;

            ptr->next = ptr->prev = nullptr;

            // break the cycle
            return ptr;
        }

        anchor += 1;
    }

    return nullptr;
};


// access an element in list, start from [0, n)
struct basic_node const* list_access(list* ptr_list, size_n pos)
{
    if (ptr_list == nullptr) {
        std::cerr << "list cannot be a null" << std::endl;
        return nullptr;
    }

    size_n anchor = 0;
    for (list* ptr = ptr_list->next; ptr->next != nullptr; ptr = ptr->next) {
        if (anchor == pos) {
            // break the cycle
            return ptr;
        }
        anchor += 1;
    }

    return nullptr;
};

// the number of elements in list
size_n list_elements(list* ptr_list)
{
    if (ptr_list == nullptr) {
        std::cerr << "list cannot be a null" << std::endl;
        return -1;
    }

    size_n anchor = 0;
    for (list* ptr = ptr_list; ptr->next != nullptr; ptr = ptr->next) {
        if (ptr->size > 0) {
            anchor += 1;
        }
    }

    return anchor;
};

// the content size of list
size_n list_memsize(list* ptr_list)
{
    if (ptr_list == nullptr) {
        std::cerr << "list cannot be a null" << std::endl;
        return -1;
    }

    size_n anchor = 0;
    for (list* ptr = ptr_list; ptr->next != nullptr; ptr = ptr->next) {
        if (ptr->size > 0) {
            anchor += ptr->size;
        }
    }

    return anchor;
};

// empty the list
void list_empty(list* ptr_list)
{
    if (ptr_list == nullptr) {
        std::cerr << "list cannot be a null" << std::endl;
        return;
    }

    do {
        node* node = list_popup(ptr_list);
        if (node == nullptr) break;
        else node_dispose(node);
    } while (true);
};

// dispose the list
void list_dispose(list* ptr_list)
{
    if (list_elements(ptr_list) == 0) {
        node* head = ptr_list;
        node* tail = ptr_list->next;

        node_dispose(head);
        node_dispose(tail);
    }
    else {
        list_empty(ptr_list);
        list_dispose(ptr_list);
    }
};