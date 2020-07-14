#include "StringContainer.h"

bool_n StringContainer::has_next()
{
    if (anchor != nullptr) {
        return anchor->next != nullptr;
    }
    return FALSE;
}

bool_n StringContainer::has_prev()
{
    if (anchor != nullptr) {
        return anchor->prev != nullptr;
    }
    return FALSE;
}

std::string* StringContainer::ptr()
{
    if (anchor != nullptr and anchor->size > 0) {
        temp.assign((char*)anchor->content);
    }
    return &temp;
}

void StringContainer::next()
{
    if (has_next()) {
        anchor = anchor->next;
    }
}

void StringContainer::prev()
{
    if (has_prev()) {
        anchor = anchor->prev;
    }
}

void StringContainer::reset()
{
    if (container != nullptr) {
        anchor = container;
        if (has_next()) {
            next();
        }
    }
}

StringContainer::StringContainer() :
    container(nullptr), anchor(nullptr), items(0)
{
    if (container == nullptr) {
        container = list_create_empty();
    }
}

StringContainer::~StringContainer()
{
    if (container != nullptr) {
        list_dispose(container);
        container = nullptr;
        anchor = nullptr;
        items = 0;
    }
}

StringContainer::StringContainer(list* lists) 
    :StringContainer()
{
    char temp[1024] = { 0 };

    for (basic_node* ptr = lists; ptr->next != nullptr; ptr = ptr->next) {
        if (ptr->size > 0) {
            memset(temp, 0, 1024);
            memcpy(temp, ptr->content, ptr->size);
            std::string str(temp);
            enqueue(str);
        }
    }
}

bool_n StringContainer::enqueue(std::string const& str)
{
    if (container != nullptr) {
        basic_node* node = node_copy_data(str.length() + 1, DATA_DEFAULT, str.c_str());
        list_append(container, node);
        items += 1;
        return TRUE;
    }
    return FALSE;
}

#include "../Core/CommonTool.h"

std::string& StringContainer::dequeue()
{
    if (container != nullptr and items > 0) {
        basic_node* node = list_remove(container, list_elements(container) - 1);

        if (node != nullptr) {
            // replace
            temp.assign((char*)node->content);

            node_dispose(node);
            items -= 1;
        }
    }
    return temp;
}

const size_n StringContainer::length()
{
    if (container != nullptr) {
        return items;
    }
    return 0;
}

void StringContainer::clean()
{
    if (container != nullptr) {
        list_empty(container);
        items = 0;
    }
}
