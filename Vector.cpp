////
//// Created by tim on 20-5-17.
////
//
////#include "Vector.h"
//
//#include <iostream>
//#include <utility>
//#include <iterator>
//#include <algorithm>
//
//using namespace std;
//
//template <class T>
//class Vector
//{
//private:
//    size_t m_size, m_capacity;
//    T *m_p;
//public:
//    explicit Vector(size_t n = 0)
//            : m_size(n),
//              m_capacity(10 * (n / 10 + 1)),
//              m_p(new T[m_capacity])
//    {
//        //
//    }
//    Vector(const Vector &rcV)
//            : m_size(rcV.m_size),
//              m_capacity(rcV.m_capacity),
//              m_p(new T[m_capacity])
//    {
//        copy(rcV.cbegin(), rcV.cend(), m_p);
//    }
//    Vector &operator = (const Vector &rcV)
//    {
//        if (this != &rcV)
//        {
//            delete [] m_p;
//            m_size = rcV.m_size;
//            m_capacity = rcV.m_capacity;
//            m_p = new T[m_capacity];
//            copy(rcV.cbegin(), rcV.cend(), m_p);
//        }
//        return *this;
//    }
//    Vector(Vector &&rrV)
//            : m_size(rrV.m_size),
//              m_capacity(rrV.m_capacity),
//              m_p(rrV.m_p)
//    {
//        rrV.m_p = nullptr;
//        rrV.m_size = 0;
//    }
//    Vector &operator = (Vector &&rrV)
//    {
//        if (this != &rrV)
//        {
//            delete [] m_p;
//            m_size = rrV.m_size;
//            m_capacity = rrV.m_capacity;
//            m_p = rrV.m_p;
//            rrV.m_p = nullptr;
//            // rrV.m_size = 0;    // better not to do this to be able to detect errors like (1)
//        }
//        return *this;
//    }
//    ~Vector()
//    {
//        delete [] m_p;
//        // Not delete m_p;
//    }
//    T &operator [] (size_t i)
//    {
//        return m_p[i];
//    }
//    const T &operator [] (size_t i) const
//    {
//        return m_p[i];
//    }
//    void push_back(const T &rcT)
//    {
//        if (m_size ++ == m_capacity)
//        {
//            m_capacity += 10;
//            T *p = new T[m_capacity];
//            for (size_t i = 0; i < m_size - 1; ++ i)
//                p[i] = m_p[i];
//            swap(p, m_p);
//            delete [] p;
//        }
//        m_p[m_size - 1] = rcT;
//    }
//    void pop_front()
//    {
//        for (size_t i = 1; i < m_size; ++ i)
//            m_p[i - 1] = m_p[i];
//        -- m_size;
//    }
//    size_t size() const
//    {
//        return m_size;
//    }
//    size_t capacity() const
//    {
//        return m_capacity;
//    }
//    typedef T *iterator;
//    typedef const T *const_iterator;
//    iterator begin()
//    {
//        return m_p;
//    }
//    iterator end()
//    {
//        return m_p + m_size;
//    }
//    const_iterator begin() const
//    {
//        return m_p;
//    }
//    const_iterator end() const
//    {
//        return m_p + m_size;
//    }
//    const_iterator cbegin() const
//    {
//        return m_p;
//    }
//    const_iterator cend() const
//    {
//        return m_p + m_size;
//    }
//};
//
//template <class T>
//void output(const char *pcszLabel, const Vector <T> &rcV)
//{
//    cout << pcszLabel << ": " << flush;
//    cout << rcV.size() << ' ' << rcV.capacity() << endl;
//    for (int i = 0; i < rcV.size(); ++ i)
//        cout << rcV[i] << ' ';
//    cout << endl;
//}
//
//int main()
//{
//    Vector <int> v(10);
//    for (int i = 0; i < 10; ++ i)
//        v[i] = i;
//    for (int i = 10; i < 25; ++ i)
//        v.push_back(i);
//    v.pop_front();
//    output("v", v);
//    copy(v.cbegin(), v.cend(), ostream_iterator <int> (cout, " "));
//    cout << endl;
//    Vector <int> v2 = v;
//    output("v2", v2);
//    v.pop_front();
//    v2 = v;
//    output("v2", v2);
//    v = std::move(v2);  // (2)
//    output("v after move", v);
//    // output("v2 after move", v2); // (1) - referencing v2 after moving it in (2)
//}