//
// Created by tim on 12-6-17.
//

#ifndef METAPROGRAMMING0_ASS2_H
#define METAPROGRAMMING0_ASS2_H

#include <array>
#include <set>
#include <iostream>

using namespace std;

template<template<typedef string, class> class TContainer>
set<size_t> longest(const TContainer &c) {
    cout << "herman" << endl;
}


#endif //METAPROGRAMMING0_ASS2_H
