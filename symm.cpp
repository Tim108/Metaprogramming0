////
//// Created by tim on 11-5-17.
////
//#include "symm.h"
//
//using namespace std;
//
//    Symm::Symm(size_t n = 0, size_t dim = 1) {
//        m_size = n;
//        dimension = dim;
//        m_capacity = (dimension * dimension + 1) / 2;
//        list = new T[m_capacity];
//    }
//
//    size_t Symm::size() const {
//        return m_size;
//    }
//
//    size_t Symm::capacity() const {
//        return m_capacity;
//    }
//
//    template <class T>
//    T &Symm::operator[](size_t i) {
//        return list[i];
//    }
//
//    template <class T>
//    void Symm::insert(T t) {
//        if (m_size >= m_capacity) {
//            T *newList = new T[capacity() + dimension++];
//            for (int i = 0; i < size(); i++) {
//                if (list[i]) {
//                    list[i] >> newList[i];
//                }
//            }
//            list = newList;
//            delete[] list;
//        }
//        t >> list[nextIndex++];
//        m_size++;
//    }
//
//    void Symm::output(const char *pcszLabel, const Symm<T> &rcV) {
//        cout << pcszLabel << ": " << flush;
//        cout << rcV.size() << ' ' << rcV.capacity() << endl;
//        for (int i = 0; i < rcV.size(); ++i)
//            cout << rcV[i] << ' ';
//        cout << endl;
//    }
//
//    template <class T>
//    void Symm::remove(T t) {
//        //if(dim1 < dimension && dim2 < dimension){
//        //  nullptr >> list[dim1 + dimension * dim2];
//        //nullptr >> list[dim2 + dimension * dim1];
//        //}
//    }
//
//    int main()
//    {
//        Symm<int> s(2);
//        s.insert(1);
//        s.output("s", s);
//
//    }
