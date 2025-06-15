//#pragma once
//#include "Vector.hpp"
//#include <limits>
//
//template <typename T>
//std::istream& operator>>(std::istream& is, Vector<T>& vector) {
//    size_t newSize;
//    is >> newSize;
//    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    if (!is) return is;
//
//    vector.free();
//    vector.size = newSize;
//    vector.capacity = vector.allocateCapacity(newSize);
//    vector.data = new T[vector.capacity];
//
//    for (size_t i = 0; i < vector.size; i++) {
//        is >> vector.data[i];
//        if (i < vector.size - 1)
//            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    }
//
//    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    return is;
//}
//
//template <typename T>
//std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
//    os << vector.size << '\n';
//    for (size_t i = 0; i < vector.size; i++) {
//        os << vector.data[i];
//        if (i < vector.size - 1) os << "\n";
//    }
//    os << '\n';
//    return os;
//}
