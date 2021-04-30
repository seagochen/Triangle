#pragma once
#ifndef _TRI_ITERATOR_H_
#define _TRI_ITERATOR_H_

template<typename T>
class Iterator {
public:

    // get the iterator
    Iterator* iterator() {
        reset();
        return this;
    };

    // loop, return true if not reaches list's tail
    virtual bool_n has_next() = 0;

    // loop, return true if not reaches list's head
    virtual bool_n has_prev() = 0;

    // access the element
    virtual T* ptr() = 0;

    // move to next element
    virtual void next() = 0;

    // move to prev element
    virtual void prev() = 0;

    // reset the iterator
    virtual void reset() = 0;
};

#endif