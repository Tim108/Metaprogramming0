//
// Created by tim on 12-6-17.
//

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include "ass2.h"

using namespace std;

int main() {
    vector<string> v(5);
    v[0] = "a";
    v[1] = "abb";
    v[2] = "ab";
    v[3] = "axx";
    v[4] = "ac";

    vector<int> v2(5);
    v2[0] = 1;
    v2[1] = 2;
    v2[2] = 1;
    v2[3] = 0;
    v2[4] = 1;

    auto r = longest(v);
    for (auto i : r) {
        cout << *i << endl;
    }


}