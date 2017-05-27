//
// Created by tim on 20-5-17.
//

//#include "Vector.h"

#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <memory>

using namespace std;

template<class T>
struct MatrixData{
    size_t m_size, m_capacity, m_dimension, m_size_internal;
    T* list;
};

template<class T>
class Matrix {
private:
    size_t m_size, m_capacity, m_dimension, m_size_internal;
    T* list;

    const size_t to_internal_i(size_t i)const {
        size_t i2 = i;
        // first to two dimensional
        size_t x = i2 % m_dimension;
        size_t y = floor(i2 / m_dimension);

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

public:
    explicit Matrix(size_t n = 0) {
        m_dimension = ceil(sqrt(n));
        m_size = n;
        m_capacity = m_dimension * m_dimension;
        m_size_internal = to_internal_i(n);
        list = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
        cout << "--" <<  m_dimension << "--" << m_size << "--" << m_capacity << "--" << endl;
//        for (int i = 0; i < ((m_dimension * (m_dimension + 1)) / 2); ++i) {
//            list[i] = 0;
//        }
    }

    Matrix(const Matrix &m) { // copy constructor
        m_dimension = m.m_dimension;
        m_size = m.m_size;
        m_capacity = m.m_capacity;
        m_size_internal = m.m_size_internal;
        list = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
        copy(m.cbegin(), m.cend(), list);
    }

    Matrix(Matrix &&m) { // move constructor
        m_dimension = m.m_dimension;
        m_size = m.m_size;
        m_capacity = m.m_capacity;
        m_size_internal = m.m_size_internal;
        list = m.list;
        m.list = new T[0];
        m.m_size = 0;
        m.m_capacity = 0;
        m.m_size_internal = 0;
        m.m_dimension = 0;
    }

    ~Matrix() {
        delete[] list;
        // Not delete m_p;
    }

    Matrix &operator=(const Matrix &m) { // copy
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

    Matrix &operator=(Matrix &&m) { // move
        if (this != &m) {
            delete[] list;
            m_dimension = m.m_dimension;
            m_size = m.m_size;
            m_capacity = m.m_capacity;
            m_size_internal = m.m_size_internal;
            list = m.list;
            m.list = nullptr;
            m.m_dimension = 0;
            m.m_capacity = 0;
            m.m_size = 0;
            m.m_size_internal = 0;
            // rrV.m_size = 0;    // better not to do this to be able to detect errors like (1)
        }
        return *this;
    }

    void swap(Matrix &other){
        using std::swap;
        swap(list, other.list);
        swap(m_dimension, other.m_dimension);
        swap(m_capacity, other.m_capacity);
        swap(m_size, other.m_size);
        swap(m_size_internal, other.m_size_internal);
    }

    T &operator[](size_t i) { // element access via non constant iterator
        return list[to_internal_i(i)];
    }

    const T &operator[](size_t i) const { // element access via constant iterator
        return list[to_internal_i(i)];
    }

    void push_front(const T &t){ // insert front
        if (m_size >= m_capacity)
            increase_capacity();

        for (int i = m_size_internal; i >= 0; --i) {
            list[i+1] = list[i];
        }
        list[0] = t;
        m_size_internal++;

        if (m_size % m_dimension == floor(m_size / m_dimension)) {
            m_size += 1;
        } else{
            m_size += 2;
        }
    }

    void push_back(const T &t){ // insert back
        if(m_size >= m_capacity)
            increase_capacity();

        list[m_size_internal] = t;
        m_size_internal++;

        if (m_size % m_dimension == floor(m_size / m_dimension)) {
            m_size += 1;
        } else{
            m_size += 2;
        }
    }

    void increase_capacity(){ // well.. increase capacity
        T *newlist = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
        for (size_t i = 0; i < ((m_dimension * (m_dimension + 1)) / 2); ++i) {
            newlist[i] = list[i];
        }
        std::swap(newlist, list);
        m_dimension++;
        m_capacity = m_dimension * m_dimension;

        delete[] newlist;
        cout << "capacity increased to: " << m_capacity << endl;
    }

    void pop_front() { // remove
        for (size_t i = 1; i < m_size_internal; ++i)
            list[i - 1] = list[i];
        --m_size_internal;
        if (m_size % m_dimension == floor(m_size / m_dimension)) {
            m_size -= 1;
        } else{
            m_size -= 2;
        }
        list[m_size_internal] = 0;
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
        return list + m_size_internal;
    }

    const_iterator begin() const {
        return list;
    }

    const_iterator end() const {
        return list + m_size_internal;
    }

    const_iterator cbegin() const {
        return list;
    }

    const_iterator cend() const {
        return list + m_size_internal;
    }

    void output(const char *label) {
        cout << label << ": " << flush;
        cout << m_size << ' ' << m_capacity << endl;
        for (int i = 0; i < m_capacity; ++i) {
            if(i % m_dimension == 0 && i != 0)
                cout << endl;
            cout << list[to_internal_i(i)] << '\t';
        }
        cout << endl;
    }
};



int main() {
    Matrix<int> v(9);

    v.output("one");
    for (int i = 0; i < 9; ++i) {
        v[i] = i;
    }

    v.output("two");

    for (int i = 9; i < 18; ++i) {
        v.push_back(i);
    }

    v.output("three");

    v.pop_front();
    v.pop_front();
    v.pop_front();

    v.output("four");

    copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    Matrix<int> v2 = v;
    v.output("original");
    v.pop_front();
    v2 = v;
    v.output("popped");


    v = std::move(v2);  // (2)
    v.output("v after move");
    v2.output("v2 after move"); // (1) - referencing v2 after moving it in (2)

    swap(v, v2);
    v.output("v after swap");
    v2.output("v2 after swap");

    v2.push_front(99);
    v2.output("v2 after pushing 99 up front");
}