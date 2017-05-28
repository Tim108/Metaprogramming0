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
struct MatrixData {
    size_t m_size, m_capacity, m_dimension, m_size_internal;
    T *list;
    unsigned long refs;
};

template<class T>
class Matrix {
private:
    MatrixData<T> *data;

    const size_t to_internal_i(size_t i) const {
        if (i == 0)
            return 0;
        size_t i2 = i;
        // first to two dimensional
        size_t x = i2 % data->m_dimension;
        size_t y = floor(i2 / data->m_dimension);

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
        data = new MatrixData<T>;
        data->m_dimension = ceil(sqrt(n));
        data->m_size = n;
        data->m_capacity = data->m_dimension * data->m_dimension;
        data->m_size_internal = to_internal_i(n);
        data->list = new T[((data->m_dimension * (data->m_dimension + 1)) / 2) * sizeof(T)];
        cout << "--" << data->m_dimension << "--" << data->m_size << "--" << data->m_capacity << "--" << endl;
//        for (int i = 0; i < ((m_dimension * (m_dimension + 1)) / 2); ++i) {
//            list[i] = 0;
//        }
        data->refs = 1;
    }

    Matrix(const Matrix &m) { // copy constructor
        data = m.data;
        data->refs++;
//        m_dimension = m.m_dimension;
//        m_size = m.m_size;
//        m_capacity = m.m_capacity;
//        m_size_internal = m.m_size_internal;
//        list = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
//        copy(m.cbegin(), m.cend(), list);
    }

    Matrix(Matrix &&m) { // move constructor
        data = m.data;
        m.data = new MatrixData<T>;
//        m_dimension = m.m_dimension;
//        m_size = m.m_size;
//        m_capacity = m.m_capacity;
//        m_size_internal = m.m_size_internal;
//        list = m.list;
//        m.list = new T[0];
//        m.m_size = 0;
//        m.m_capacity = 0;
//        m.m_size_internal = 0;
//        m.m_dimension = 0;
    }

    ~Matrix() {
        data->refs--;
        if (data->refs == 0) {
            delete data;
        }
        // Not delete m_p;
    }

    Matrix &operator=(const Matrix &m) { // copy
        if (this != &m) {
            data = m.data;
//            delete[] list;
//            m_dimension = m.m_dimension;
//            m_size = m.m_size;
//            m_capacity = m.m_capacity;
//            m_size_internal = m.m_size_internal;
//            list = new T[((m_dimension * (m_dimension + 1)) / 2) * sizeof(T)];
//            copy(m.cbegin(), m.cend(), list);
        }
        return *this;
    }

    Matrix &operator=(Matrix &&m) { // move
        if (this != &m) {
            data = m.data;
            m.data = new MatrixData<T>;
//            delete[] list;
//            m_dimension = m.m_dimension;
//            m_size = m.m_size;
//            m_capacity = m.m_capacity;
//            m_size_internal = m.m_size_internal;
//            list = m.list;
//            m.list = nullptr;
//            m.m_dimension = 0;
//            m.m_capacity = 0;
//            m.m_size = 0;
//            m.m_size_internal = 0;
            // rrV.m_size = 0;    // better not to do this to be able to detect errors like (1)
        }
        return *this;
    }

    void swap(Matrix &other) {
        using std::swap;
        swap(data, other.data);
//        swap(list, other.list);
//        swap(m_dimension, other.m_dimension);
//        swap(m_capacity, other.m_capacity);
//        swap(m_size, other.m_size);
//        swap(m_size_internal, other.m_size_internal);
    }

    void deep_copy(){
        if (data->refs > 1) {
            data->refs--;
            MatrixData<T> *newData = new MatrixData<T>;
            newData->refs = 1;
            newData->m_dimension = data->m_dimension;
            newData->m_size_internal = data->m_size_internal;
            newData->m_size = data->m_size;
            newData->m_capacity = data->m_size;
            newData->list = new T[((newData->m_dimension * (newData->m_dimension + 1)) / 2) * sizeof(T)];
            copy(cbegin(), cend(), newData->list);
            data = newData;
        }
    }

    T &operator[](size_t i) {
        return data->list[to_internal_i(i)];
    }

    const T &operator[](size_t i) const {
        return data->list[to_internal_i(i)];
    }

    void push_front(const T &t) { // insert front
        deep_copy();
        if (data->m_size >= data->m_capacity){}
            increase_capacity();

        for (int i = data->m_size_internal; i >= 0; --i) {
            data->list[i + 1] = data->list[i];
        }
        data->list[0] = t;
        data->m_size_internal++;

        if (data->m_size % data->m_dimension == floor(data->m_size / data->m_dimension)) {
            data->m_size += 1;
        } else {
            data->m_size += 2;
        }
    }

    void push_back(const T &t) { // insert back
        if (data->m_size >= data->m_capacity)
            increase_capacity();

        data->list[data->m_size_internal] = t;
        data->m_size_internal++;

        if (data->m_size % data->m_dimension == floor(data->m_size / data->m_dimension)) {
            data->m_size += 1;
        } else {
            data->m_size += 2;
        }
    }

    void increase_capacity() { // well.. increase capacity
        T *newlist = new T[((data->m_dimension * (data->m_dimension + 1)) / 2) * sizeof(T)];
        for (size_t i = 0; i < ((data->m_dimension * (data->m_dimension + 1)) / 2); ++i) {
            newlist[i] = data->list[i];
        }
        std::swap(newlist, data->list);
        data->m_dimension++;
        data->m_capacity = data->m_dimension * data->m_dimension;

        delete[] newlist;
        cout << "capacity increased to: " << data->m_capacity << endl;
    }

    void pop_front() { // remove
        for (size_t i = 1; i < data->m_size_internal; ++i)
            data->list[i - 1] = data->list[i];
        --data->m_size_internal;
        if (data->m_size % data->m_dimension == floor(data->m_size / data->m_dimension)) {
            data->m_size -= 1;
        } else {
            data->m_size -= 2;
        }
        data->list[data->m_size_internal] = 0;
    }

    size_t size() const {
        return data->m_size;
    }

    size_t capacity() const {
        return data->m_capacity;
    }

    typedef T *iterator;
    typedef const T *const_iterator;

    iterator begin() {
        return data->list;
    }

    iterator end() {
        return data->list + data->m_size_internal;
    }

    const_iterator begin() const {
        return data->list;
    }

    const_iterator end() const {
        return data->list + data->m_size_internal;
    }

    const_iterator cbegin() const {
        return data->list;
    }

    const_iterator cend() const {
        return data->list + data->m_size_internal;
    }

    void output(const char *label) {
        cout << label << ": " << flush;
        cout << data->m_size << ' ' << data->m_capacity << endl;
        for (int i = 0; i < data->m_capacity; ++i) {
            if (i % data->m_dimension == 0 && i != 0)
                cout << endl;
            cout << data->list[to_internal_i(i)] << '\t';
        }
        cout << endl;
    }
};


int main() {
    bool basicTest = true;
    bool COWTest = true;

    if (basicTest) {

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

    if (COWTest) {
        Matrix<int> a(0);
        a.push_front(1);
        a.push_front(2);
        a.push_front(3);
        a.push_front(4);
        a.output("A - Start");

        Matrix<int> b(a);
        a.output("A - After creating B");
        b.output("B - After creating B");
//        // good so far...
//
        a.push_front(99); // should add only to 'a' not 'b'
        a.output("A - After adding 99 to A");
        b.output("B - After adding 99 to A");
    }

}