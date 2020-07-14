#pragma once
#ifndef _TRI_STRING_CONTAINER_H_
#define _TRI_STRING_CONTAINER_H_

#include "Iterator.hpp"
#include "DLLExpo.h"

#include <string>

class StringContainer : public Iterator<std::string>{

public:
    // 通过 Iterator 继承
    DLL_EXPO virtual bool_n has_next() override;
    DLL_EXPO virtual bool_n has_prev() override;
    DLL_EXPO virtual std::string* ptr() override;
    DLL_EXPO virtual void next() override;
    DLL_EXPO virtual void prev() override;
    DLL_EXPO virtual void reset() override;

private:
    list* container;
    list* anchor;
    size_n items;

public:

    // constructor
    DLL_EXPO StringContainer();

    // deconstructor
    DLL_EXPO ~StringContainer();

    // constructor from list of strings
    DLL_EXPO StringContainer(list* lists);

    DLL_EXPO bool_n enqueue(std::string const& str);

    DLL_EXPO std::string& dequeue();

    DLL_EXPO const size_n length();

    DLL_EXPO void clean();

private:
    std::string temp;
};

#endif