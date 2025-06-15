#include "String.h"
#include <iostream>

String::String()
    :size(0), capacity(1)
{
    string = new char[capacity];
}

String::String(const char* string) {
    if (string==nullptr) {
        size = 1;
        capacity = 1;
        this->string = new char[1];
        this->string[0] = '\0';
        return;
    }

    size = strlen(string) + 1;
    capacity = allocateCapacity(size);
    if (capacity == 0) capacity = 1;
    this->string = new char[capacity];
    strcpy(this->string, string);
}


String::String(char c) :
    size(1), capacity(2)
{
    string = new char[capacity];
    string[0] = c;
    string[1] = '\0';
}

String::String(size_t size) :
    size(size)
{
    capacity = allocateCapacity(size);
    this->string = new char[capacity];
}

String::String(const String& other)
{
    copyFrom(other);
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

String::~String()
{
    free();
}

String& String::operator=(String&& other) noexcept
{
    if (this != &other)
    {
        free();
        size = (other.size);
        capacity = (other.capacity);
        string = (other.string);
        other.string = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

String::String(String&& other) noexcept :
    size(other.size),
    capacity(other.capacity),
    string(other.string)
{
    other.string = nullptr;
    other.size = 0;
    other.capacity = 0;
}

const char* String::c_str() const
{
    return string;
}

size_t String::getSize() const
{
    return size;
}

size_t String::getCapacity() const
{
    return capacity;
}

const char& String::operator[](size_t idx) const
{
    if (idx >= size) throw std::out_of_range("Index out of range");
    return string[idx];
}

char& String::operator[](size_t idx)
{
    if (idx >= size) throw std::out_of_range("Index out of range");
    return string[idx];
}

String& String::operator+=(const String& other) {
    if (!other.string || !string) return *this;
    size_t newSize = size + other.size;
    if (newSize + 1 > capacity) {
        resize(allocateCapacity(newSize));
    }
    strcpy(string + size, other.string);
    size = newSize;
    return *this;
}

String& String::operator+=(size_t other)
{
    char buffer[20];
    size_t index = 0;

    do {
        buffer[index++] = '0' + (other % 10);
        other /= 10;
    } while (other > 0);

    for (size_t i = 0; i < index / 2; ++i) {
        std::swap(buffer[i], buffer[index - i - 1]);
    }

    buffer[index] = '\0';
    *this += buffer;
}

String String::substr(size_t begin, size_t count) const
{
    if (begin + count > size) throw std::out_of_range("Substring out of range");
    String toReturn(count);
    for (size_t i = 0; i < count; i++)
    {
        toReturn.string[i] = string[i + begin];
    }
    toReturn.string[count] = '\0';
    return toReturn;
}


void String::readBinary(std::istream& fs)
{
    free();
    if (fs.peek()==EOF) {
        std::cerr << "Error: Could not open the file!\n";
        return;
    }
    fs.read((char*)&size, sizeof(size));
    fs.read((char*)&capacity, sizeof(capacity));
    string = new char[capacity];
    fs.read((char*)string, size);
    string[size] = '\0';
}

void String::writeBinary(std::ostream& fs) const
{
    if (fs.tellp() == EOF) {
        std::cerr << "Error: File not open for writing!\n";
        return;
    }

    if (!string) {
        std::cerr << "Error: Attempted to write a null string!\n";
        return;
    }
    fs.write((const char*)(&size), sizeof(size));
    fs.write((const char*)(&capacity), sizeof(capacity));
    fs.write((const char*)(string), size);
}


void String::copyFrom(const String& other) // ab
{
    this->capacity = other.capacity;
    this->size = other.size;
    this->string = new char[capacity];
    strcpy(this->string, other.string);
}

void String::free()
{
    delete[] string;
}

void String::resize(size_t newCapacity) {
    if (newCapacity == 0) {
        delete[] string;
        string = nullptr;
        capacity = 0;
        size = 0;
        return;
    }

    char* newString = new char[newCapacity];
    if (string != nullptr && size > 0) {
        strcpy(newString, string);
    }
    else {
        newString[0] = '\0';
    }

    delete[] string;
    string = newString;
    capacity = newCapacity;
}

size_t String::allocateCapacity(size_t size) const
{
    return size * 2;
}

String operator+(const String& lhs, const String& rhs)
{
    String toReturn(lhs.getSize() + rhs.getSize());

    toReturn += lhs;
    toReturn += rhs;

    return toReturn;
}

bool operator==(const String& lhs, const String& rhs)
{
    return strcmp(lhs.string, rhs.string) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
    return strcmp(lhs.string, rhs.string) != 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
    return strcmp(lhs.string, rhs.string) <= 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
    return strcmp(lhs.string, rhs.string) >= 0;
}

bool operator<(const String& lhs, const String& rhs)
{
    return strcmp(lhs.string, rhs.string) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
    return strcmp(lhs.string, rhs.string) > 0;
}

std::istream& operator>>(std::istream& is, String& other)
{
    char buff[MAX_SIZE + 1];
    is >> buff;

    size_t buffLength = strlen(buff);

    if (buffLength >= other.getCapacity())
    {
        other.resize(other.allocateCapacity(buffLength));
    }
    strcpy(other.string, buff);

    other.size = buffLength;

    return is;
}

std::ostream& operator<<(std::ostream& os, const String& other)
{
    return os << other.string;
}

void readConsole(String& toReturn) {
    char staticArr[512];
    size_t index = 0;
    char first = std::cin.peek();
    while (first == ' ' || first == '\n' || first == '>')
    {
        first = std::cin.get();
        first = std::cin.peek();
    }
    while (index < 511) {
        char ch = std::cin.peek(); 
        if (ch == ' ' || ch == '\n' || ch == EOF) break;
        ch = std::cin.get();
        staticArr[index++] = ch;
    }


    staticArr[index] = '\0';
    toReturn = String(staticArr);
}

std::istream& getline(std::istream& is, String& str, char delim)
{
    char buffer[1024];
    is.getline(buffer, 1024, delim);
    str = buffer;
    return is;
}

void String::readConsole(String& toReturn) {
    char staticArr[1024];
    size_t index = 0;
    char first = std::cin.peek();
    while (first == ' ' || first == '\n')
    {
        first = std::cin.get();
        first = std::cin.peek();
    }
    while (index < 1024 - 1) {
        char ch = std::cin.get();
        if (ch == ' ' || ch == '\n') break;
        staticArr[index++] = ch;
    }

    staticArr[index] = '\0';
    toReturn = String(staticArr);
}

