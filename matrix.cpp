//
// Created by tim on 20-5-17.
//

//#include "Vector.h"

#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>

using namespace std;

template<class T>
class Matrix {
private:
    size_t m_size, m_capacity, m_dimension, m_size_internal;
    T *list;



public:
    explicit Matrix(size_t n = 0) {
        m_dimension = ceil(sqrt(n));
        m_size = n;
        m_capacity = m_dimension * m_dimension;
        m_size_internal = 0;
        list = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
        cout << "--" <<  m_dimension << "--" << m_size << "--" << m_capacity << "--" << endl;

        cout << "!!!" << ((m_dimension * (m_dimension + 1)) / 2) << endl;
    }

    Matrix(const Matrix &m) {
        m_dimension = m.m_dimension;
        m_size = m.m_size;
        m_capacity = m.m_capacity;
        m_size_internal = m.m_size_internal;
        list = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
        copy(m.cbegin(), m.cend(), list);
    }

    Matrix(Matrix &&m) {
        m_dimension = m.m_dimension;
        m_size = m.m_size;
        m_capacity = m.m_capacity;
        m_size_internal = m.m_size_internal;
        list = m.list;
        m.list = nullptr;
        m.m_size = 0;
    }

    ~Matrix() {
        delete[] list;
        // Not delete m_p;
    }

    Matrix &operator=(const Matrix &m) {
        if (this != &m) {
            delete[] list;
            m_dimension = m.m_dimension;
            m_size = m.m_size;
            m_capacity = m.m_capacity;
            m_size_internal = m.m_size_internal;
            list = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
            copy(m.cbegin(), m.cend(), list);
        }
        return *this;
    }

    Matrix &operator=(Matrix &&m) {
        if (this != &m) {
            delete[] list;
            m_dimension = m.m_dimension;
            m_size = m.m_size;
            m_capacity = m.m_capacity;
            m_size_internal = m.m_size_internal;
            list = m.list;
            m.list = nullptr;
            // rrV.m_size = 0;    // better not to do this to be able to detect errors like (1)
        }
        return *this;
    }

    T &operator[](size_t i) {
        return list[to_internal_i(m_dimension, i)];
    }

    const T &operator[](size_t i) const {
        return list[to_internal_i(m_dimension, i)];
    }

    void push_back(const T &t){
        if(m_size >= m_capacity){
            cout << "=========================================" << endl;
            output("before expanding");
            m_dimension++;
            m_capacity = m_dimension * m_dimension;
            T *newlist = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
            for (size_t i = 0; i < m_size; ++i) {
                newlist[to_internal_i(m_dimension, i)] = list[to_internal_i(m_dimension-1, i)];
            }
            swap(newlist, list);

            delete[] newlist;
            cout << "capacity increased to: " << m_capacity << endl;
            output("after expanding");
            cout << "==========================================" << endl;
        }

//        cout << "before: " << m_size_internal << endl;
//        list[m_size_internal] = t;
//        m_size_internal++;
//        cout << "after: " << m_size_internal << endl;

        list[to_internal_i(m_dimension, m_size)] = t;
        if (m_size % m_dimension == floor(m_size / m_dimension)) {
            m_size += 1;
        } else{
            m_size += 2;
        }
    }

//    void push_back(const T &rcT) {// = insert?
//        if (m_size++ == m_capacity) {
//            m_capacity += 10;
//            T *newlist = new T[m_capacity];
//            for (size_t i = 0; i < m_size - 1; ++i)
//                newlist[i] = list[i];
//            swap(newlist, list);
//            delete[] newlist;
//        }
//        list[m_size - 1] = rcT;
//    }

    void pop_front() { // = remove?
        for (size_t i = 1; i < m_size; ++i)
            list[i - 1] = list[i];
        --m_size;
    }

    size_t size() const {
        return m_size;
    }

    size_t capacity() const {
        return m_capacity;
    }

    typedef T *iterator;
    typedef const T *const_iterator;

    iterator begin() {
        return list;
    }

    iterator end() {
        return list + m_size;
    }

    const_iterator begin() const {
        return list;
    }

    const_iterator end() const {
        return list + m_size;
    }

    const_iterator cbegin() const {
        return list;
    }

    const_iterator cend() const {
        return list + m_size;
    }

    void output(const char *label) {
        cout << label << ": " << flush;
        cout << m_size << ' ' << m_capacity << endl;
        for (int i = 0; i < m_capacity; ++i) {
            if(i % m_dimension == 0 && i != 0)
                cout << endl;
            cout << list[to_internal_i(m_dimension, i)] << '\t';
        }
        cout << endl;
    }

    const size_t to_internal_i(size_t dim, size_t i)const {
        size_t i2 = i;
        // first to two dimensional
        size_t x = i2 % dim;
        size_t y = floor(i2 / dim);

        // swap if needed
        if (x > y) {
            size_t z = x;
            x = y;
            y = z;
        }

        // then back to one dimensional
//        i2 = x + (y * dim);

        size_t i3 = 0;
        size_t temp = 0;
        for (int j = 0; j < y; ++j) {
            i3 += ++temp;
        }
        i3 += x;
        return i3;
    }
};



int main() {
    Matrix<int> v(16);
    v.output("base");
    for (int i = 0; i < 16; ++i) {
        v[i] = i;
        v.output(to_string(i).c_str());
    }


//    v.output("before");
//    for (int i = 0; i < 6; ++i) {
//        v.push_back(i);
//        v.output(to_string(i).c_str());
//    }

//    v.pop_front();
//    v.output("v");
//    copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
//    cout << endl;
//    Matrix<int> v2 = v;
//    v.output("v2");
//    v.pop_front();
//    v2 = v;
//    v.output("v2");
//    v = std::move(v2);  // (2)
//    v.output("v after move");
    // output("v2 after move", v2); // (1) - referencing v2 after moving it in (2)
}