//
// Created by tim on 12-6-17.
//

#ifndef METAPROGRAMMING0_ASS2_H
#define METAPROGRAMMING0_ASS2_H

#include <array>
#include <set>
#include <iostream>

using namespace std;

template<typename container>
set<typename container::const_iterator> longest(container const& vec)
{
    typename container::value_type T; // if needed

    size_t length = 0;
    set<typename container::const_iterator> r;

    for (typename container::const_iterator it = vec.begin(); it != vec.end(); ++it) {

        if ((*it).length() > length) {
            r.clear();
            length = (*it).length();
        }

        if ((*it).length() == length) {
            r.insert(it);
        }
    }

    return r;
}


//template<class container>
//set<iterator> longest(container const &c) {
//    cout << "herman" << endl;
//
//    set<iterator> r;
//
////    size_t length = 0;
////    for (typename container::const_iterator it = c.begin(); it != c.end(); ++it) {
////        if (*it.length() > length) {
////            length = *it.length();
////            r.clear();
////        }
////        if (*it.length() >= length) {
////            r.insert(it);
////        }
////    }
//
//    return r;
//}


#endif //METAPROGRAMMING0_ASS2_H
