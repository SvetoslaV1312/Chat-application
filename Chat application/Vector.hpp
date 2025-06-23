#pragma once
#include <iostream>
#include <fstream>
#include <type_traits>
#include <limits>
#include "String.h"

class User;

template <typename T>
class Vector {
public:
    Vector()
        :size(0), capacity(1)
    {
        data = new T[capacity];
    }
    explicit Vector(size_t newSize) : size(newSize), capacity(calcualteCapacity(newSize)) {
        data = new T[capacity]();
    }
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    Vector<User*>& push_back(const User*& data) = delete;
    Vector& push_back(const T& data);
    Vector& pop_back() {
        if (size == 0) return *this;
        size--;
        if (size * 4 <= capacity && capacity > 1) resize(capacity / 2);
        return *this;
    }
    Vector& insert(const T& data, size_t position) {
        if (position > size) return *this;
        if (size >= capacity) resize(calcualteCapacity(size + 1));
        for (size_t i = size; i > position; i--) this->data[i] = std::move(this->data[i - 1]);
        this->data[position] = data;
        size++;
        return *this;
    }
    Vector& remove(size_t position) {
        if (position >= size) return *this;
        size--;
        for (size_t i = position; i < size; i++) this->data[i] = std::move(this->data[i + 1]);
        if (size * 4 <= capacity && capacity > 1) resize(capacity / 2);
        return *this;
    }
    T& operator[](size_t idx) {
        if (idx >= size) throw std::out_of_range("Index out of range");
        return data[idx];
    }
    const T& operator[](size_t idx) const {
        if (idx >= size) throw std::out_of_range("Index out of range");
        return data[idx];
    }
    Vector& operator+=(const Vector& other) {
        size_t newSize = size + other.size;
        if (newSize > capacity) resize(calcualteCapacity(newSize));
        for (size_t i = size, j = 0; i < newSize; i++, j++) data[i] = other.data[j];
        size = newSize;
        return *this;
    }
    friend Vector operator+(const Vector& lhs, const Vector& rhs) {
        Vector result(lhs.size + rhs.size);
        result += lhs;
        result += rhs;
        return result;
    }
    friend bool operator==(const Vector& lhs, const Vector& rhs) {
        if (lhs.size != rhs.size) return false;
        for (size_t i = 0; i < lhs.size; i++) {
            if (lhs.data[i] != rhs.data[i]) return false;
        }
        return true;
    }
    friend bool operator!=(const Vector& lhs, const Vector& rhs) {
        return !(lhs == rhs);
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Vector<U>& vector);
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vector);

    Vector(const Vector& other) {
        copyFrom(other);
    }
    Vector(Vector&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            free();
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }
    Vector& clear() {
        size = 0;
        return *this;
    }
    ~Vector() {
        free();
    }
    void writeBinary(std::ostream& fs) const {
        fs.write((const char*)(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            fs.write((const char*)(&data[i]), sizeof(data[i]));
        }
    }
    void readBinary(std::istream& fs) {
        free();
        size_t newSize = 0;
        fs.read((char*)(&newSize), sizeof(newSize));
        size = newSize;
        capacity = calcualteCapacity(newSize);
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            fs.read((char*)(&data[i]), sizeof(data[i]));
        }
    }
    T* getData() const {
        return data;
    }

private:
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        size_t copySize = size < newCapacity ? size : newCapacity;
        for (size_t i = 0; i < copySize; i++) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        size = copySize;
    }
    size_t calcualteCapacity(size_t n) const {
        return n == 0 ? 1 : n * 2;
    }
    void free() {

        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    void copyFrom(const Vector& other) {
        data = new T[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 1;
};

template <typename T>
Vector<T>& Vector<T>::push_back(const T& data) {
    if (size >= capacity) resize(calcualteCapacity(size + 1));
    this->data[size++] = data;
    return *this;
}

template <typename T>
std::istream& operator>>(std::istream& is, Vector<T>& vector) {
    if constexpr (std::is_pointer_v<T>) {
        return is;
    }
        size_t newSize;
        is >> newSize;
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!is) return is;

        vector.free();
        vector.size = newSize;
        vector.capacity = vector.calcualteCapacity(newSize);
        vector.data = new T[vector.capacity];

        for (size_t i = 0; i < vector.size; i++) {
            is >> vector.data[i];
            if (i < vector.size - 1) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // or '  '
        }

        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
    os << vector.size << '\n';
    for (size_t i = 0; i < vector.size; i++) {
        os << vector.data[i];
        if (i < vector.size - 1) os << "\n"; // or ' '
    }
    os << '\n';

    return os;
}

