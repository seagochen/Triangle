#pragma once
#ifndef _TRI_BASIC_LIST_H_
#define _TRI_BASIC_LIST_H_

#include <memory.h>
#include <string.h>

#include "Iterator.hpp"
#include "../Core/List.h"

template <typename T>
class ListContainer : public Iterator<T>
{
private:
    size_n items = 0;
    list* container;

public:

    ListContainer():anchor(nullptr) {
        container = list_create_empty();
    }

    ListContainer(list* ptrData) : anchor(nullptr) {
        if (ptrData != nullptr) {
            container = ptrData;
        }
        else {
            container = list_create_empty();
        }
    }

    // dispose container, and auto-release its resources
    ~ListContainer() {
        if (container != nullptr) {
            list_dispose(container);
            container = nullptr;
            anchor = nullptr;
            items = 0;
        }
    }

    // enqueue a list
    bool_n extend(list* listElem) {
        if (container != nullptr) {
            list_append(container, listElem);
            items += list_elements(listElem);
            return TRUE;
        }
        return FALSE;
    }

    // enqueue element as queue
    bool_n enqueue(T const& t) {
        if (container != nullptr) {
            basic_node* node = node_copy_data(sizeof(t), DATA_DEFAULT, (void*)& t);
            list_append(container, node);
            items += 1;
            return TRUE;
        }
        return FALSE;
    };

    // dequeue element as queue
    // returning cannot be modified, caller should copy the 
    bool_n dequeue(T& output) {
        if (container != nullptr and items > 0) {
            basic_node* node = list_remove(container, list_elements(container) - 1);

            if (node != nullptr) {
                memcpy(&output, node->content, sizeof(T));
                node_dispose(node);
                items -= 1;
                return TRUE;
            }
        }
        return FALSE;
    };

    // push element as stack
    bool_n push(T const& t) { return enqueue(t); }

    // popup element as stack
    bool_n popup(T& output) {
        if (container != nullptr and items > 0) {
            list* node = list_popup(container);

            if (node != nullptr) {
                memcpy(&output, node->content, sizeof(T));
                node_dispose(node);
                items -= 1;
                return TRUE;
            }
        }
        return FALSE;
    }

    // insert an element to queue, not thread safety
    bool_n insert(T const& t, int pos) {
        if (container == nullptr) return FALSE;

        list* node = node_copy_data(sizeof(t), DATA_DEFAULT, (void*)& t);
        if (list_insert(container, node, pos) == FALSE) {
            node_dispose(node);
            return FALSE;
        }
        items += 1;
        return TRUE;
    };

    // pick an element from queue, not thread safety
    bool_n pick(int pos, T& outT) {
        if (container == nullptr or items <= 0) return FALSE;

        list* node = list_remove(container, pos);
        if (node != nullptr) {
            memcpy(&outT, node->content, sizeof(T));
            node_dispose(node);
            items -= 1;
            return TRUE;
        }

        return FALSE;
    };

    // access an element by indicate the position
    T const* access(size_n pos) {
        list const* node = list_access(container, pos);
        if (node == nullptr) return nullptr;
        return (T*)node->content;
    }

    // the number of available elements inside
    const size_n length() {
        if (container == nullptr) return 0;
        return items;
    };

    // clean all elements up
    void clean() {
        if (container != nullptr) {
            list_empty(container);
            items = 0;
        }
    };

public: // operator overwrite
    T const* operator[](size_n pos) {
        return this->access(pos);
    }

private:
    list* anchor;

public:
    // loop, return true if not reaches list's tail
    virtual bool_n has_next() override {
        return anchor->next != nullptr;
    };

    // loop, return true if not reaches list's head
    virtual bool_n has_prev() override {
        return anchor->prev != nullptr;
    };

    // access the element
    virtual T* ptr() override {
        if (anchor->size > 0) {
            return (T*)anchor->content;
        }
        return nullptr;
    };

    // move to next element
    virtual void next() override {
        if (anchor->next != nullptr) {
            anchor = anchor->next;
        }
    };

    // move to prev element
    virtual void prev() override {
        if (anchor->prev != nullptr) {
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
};

#endif