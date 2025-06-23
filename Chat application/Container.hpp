
#pragma once
#include <iostream>
//#include <cstddef>
#include "User.h"
#include "Chat.h"
#include "String.h"

template <typename T>
class Container {
protected:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void resize(size_t newCap) {
        T* newData = new T[newCap];
        for (size_t i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:

    void remove(size_t index) {
        if (index >= size) return; 
        delete data[index]; 

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        size--;
        data[size] = nullptr;
    }

    Container() : size(0), capacity(2) {
        data = new T[capacity]();
    }

    virtual ~Container() {
        for (size_t i = 0; i < size; ++i)
            delete data[i];
        delete[] data;
    }

    size_t getSize() const { return size; }

    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    void clear() {
        delete[] data;
        data = new T[capacity = 2]();
        size = 0;
    }
};

template <>
class Container<User*> {
    User** data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void resize(size_t newCap) {
        User** newData = new User * [newCap];
        for (size_t i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:
    void remove(size_t index) {
        if (index >= size) return; 
        delete data[index];

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1]; 
        }

        size--;
        data[size] = nullptr; 
    }
    Container() : size(0), capacity(2) {
        data = new User * [capacity]();
    }

    ~Container() {
        for (size_t i = 0; i < size; ++i)
            delete data[i];
        delete[] data;
    }

    void push_back(User* user) {
        if (size >= capacity) resize(capacity * 2);
        data[size++] = user->clone();
    }

    User*& operator[](size_t i) { return data[i]; }
    const User* operator[](size_t i) const { return data[i]; }
    size_t getSize() const { return size; }

    void clear() {
        for (size_t i = 0; i < size; ++i)
            delete data[i];
        delete[] data;
        data = new User * [capacity = 2]();
        size = 0;
    }

    void readFromStream(std::istream& is) {
        size_t count;
        is >> count;
        is.ignore();

        clear();
        for (size_t i = 0; i < count; ++i) {
            String type;
            is >> type;
            is.ignore();

            User* user = nullptr;
            if (type == "User") user = new User();
            else if (type == "Admin") user = new Admin();
            else continue;

            user->readTxt(is);
            push_back(user);
        }
    }

    void readFromStreamBin(std::istream& is) {
        size_t count;
        is.read(reinterpret_cast<char*>( &count), sizeof(count));

        clear();
        for (size_t i = 0; i < count; ++i) {
            String type;
            type.readBinary(is);

            User* user = nullptr;
            if (type == "User") user = new User();
            else if (type == "Admin") user = new Admin();
            else continue;

            user->readBin(is);
            push_back(user);
        }
    }

    void writeToStream(std::ostream& os) const {
        os << size << '\n';
        for (size_t i = 0; i < size; ++i) {
            data[i]->printTxt(os);
        }
    }
    void writeToStreamBin(std::ostream& os) const {
        os.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            data[i]->printBin(os);
        }
    }
};

template <>
class Container<Chat*> {
    Chat** data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void resize(size_t newCap) {
        Chat** newData = new Chat * [newCap];
        for (size_t i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:
    void remove(size_t index) {
        if (index >= size) return;
        delete data[index];

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        size--;
        data[size] = nullptr; 
    }

    Container() : size(0), capacity(2) {
        data = new Chat * [capacity]();
    }

    ~Container() {
        for (size_t i = 0; i < size; ++i)
            delete data[i];
        delete[] data;
    }

    void push_back(Chat* chat) {
        if (size >= capacity) resize(capacity * 2);
        data[size++] = chat->clone(); 
    }

    Chat*& operator[](size_t i) { return data[i]; }
    const Chat* operator[](size_t i) const { return data[i]; }
    size_t getSize() const { return size; }

    void clear() {
        for (size_t i = 0; i < size; ++i)
            delete data[i];
        delete[] data;
        data = new Chat * [capacity = 2]();
        size = 0;
    }

    void readFromStream(std::ifstream& is) {
        size_t count;
        is >> count;
        is.ignore();

        clear();
        for (size_t i = 0; i < count; ++i) {
            String type;
            is >> type;
            is.ignore();

            Chat* chat = nullptr;
            if (type == "Individual") chat = new Individual(is);
            else if (type == "Group") chat = new Group(is);
            else continue;
            push_back(chat);
        }
    }

    void readFromStreamBin(std::ifstream& is) {
        size_t count;
        is.read(reinterpret_cast<char*>(&count), sizeof(count));
        clear();
        for (size_t i = 0; i < count; ++i) {
            String type;
            type.readBinary(is);

            Chat* chat = nullptr;
            if (type == "Individual") chat = new Individual();
            else if (type == "Group") chat = new Group();
            else continue;
            chat->readBin(is);
            push_back(chat);
        }
    }

    void writeToStream(std::ostream& os) const {
        os << size << '\n';
        for (size_t i = 0; i < size; ++i) {
            if (dynamic_cast<Individual*>(data[i])) os << "Individual\n";
            else if (dynamic_cast<Group*>(data[i])) os << "Group\n";
            data[i]->printTxt(os);
        }
    }

    void writeToStreamBin(std::ostream& os) const {
        os.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            data[i]->printBin(os);
        }
    }
};

