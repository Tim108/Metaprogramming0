//
// Created by tim on 11-5-17.
//
#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>

#ifndef METAPROGRAMMING0_SYMM_H
#define METAPROGRAMMING0_SYMM_H


template <class T>
class Symm
{
private:
    size_t m_size, m_capacity, dimension;
    T *list;
    int nextIndex = 0;

public:
    explicit Symm(size_t n = 0, size_t dim = 1);

    size_t size() const;

    size_t capacity() const;

    T &operator [] (size_t i);

    void insert(T);

    void remove(T);

    void output(const char *pcszLabel, const Symm <T> &rcV);

};

#endif //METAPROGRAMMING0_SYMM_H
