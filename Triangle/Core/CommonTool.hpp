#pragma once
#ifndef _TRI_COMMON_TOOLS_H_
#define _TRI_COMMON_TOOLS_H_

#include <typeinfo>
#include <string>

#include "TypeDefinition.h"

namespace sge {
    template<typename T>
    T const maxVal(T arg1, T arg2) {
        return arg1 > arg2 ? arg1 : arg2;
    };

    template<typename T>
    T const minVal(T arg1, T arg2) {
        return arg1 < arg2 ? arg1 : arg2;
    };

    template<typename T>
    T const avgVal(T arg1, T arg2) {
        return ((double)(arg1 + arg2)) / 2.0;
    }
};

#endif