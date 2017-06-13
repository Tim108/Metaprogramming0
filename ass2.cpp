//
// Created by tim on 12-6-17.
//

#include <array>
#include <vector>
#include "ass2.h"
#include "Vector.h"

using namespace std;

int main() {
    vector<string> v(5);
    v[0] = "a";
    v[1] = "abb";
    v[2] = "ab";
    v[3] = "axx";
    v[4] = "ac";

//    set<string> s;
//    s.insert("a");
//    s.insert("abb");
//    s.insert("ab");
//    s.insert("axx");
//    s.insert("ac");

    auto r = longest(v);
    for (auto i : r) {
        cout << *i << endl;
    }
}