#pragma once
#ifndef _TRI_COMMON_TOOLS_H_
#define _TRI_COMMON_TOOLS_H_

#include <typeinfo>
#include <string>

#include "TypeDefinition.h"

namespace sge {
    /// <summary>
    /// compare two numbers and return the maximal one
    /// </summary>
    /// <typeparam name="T">type can be integer, float</typeparam>
    /// <param name="arg1"></param>
    /// <param name="arg2"></param>
    /// <returns></returns>
    template<typename T>
    T const max_val(T arg1, T arg2) {
        return arg1 > arg2 ? arg1 : arg2;
    };

    /// <summary>
    /// compare two numbers and return the minimal one
    /// </summary>
    /// <typeparam name="T">type can be integer, float</typeparam>
    /// <param name="arg1"></param>
    /// <param name="arg2"></param>
    /// <returns></returns>
    template<typename T>
    T const min_val(T arg1, T arg2) {
        return arg1 < arg2 ? arg1 : arg2;
    };

    /// <summary>
    /// calculate the average
    /// </summary>
    /// <typeparam name="T">type can be integer, float</typeparam>
    /// <param name="arg1"></param>
    /// <param name="arg2"></param>
    /// <returns></returns>
    template<typename T>
    T const avg_val(T arg1, T arg2) {
        return ((double)(arg1 + arg2)) / 2.0;
    }
};

#endif