#pragma once
#include <fstream>
#pragma warning(disable: 4996)

class String
{
public:
	String();
	String(const char* string);
	explicit String(char c);
	String(size_t  size);
	String(const String& other);
	String& operator=(const String& other);
	~String();
	String& operator=(String&& other) noexcept;
	String(String&& other) noexcept;
	const char* c_str()const;
	size_t getSize()const;
	size_t getCapacity() const;
	const char& operator[](size_t idx) const;
	char& operator[](size_t idx);
	String& operator+=(const String& other);
	String& operator+=(size_t other);

	String substr(size_t begin, size_t count) const;
	friend String operator+(const String& lhs, const String& rhs);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend std::istream& operator>>(std::istream& is, String& other);
	friend std::ostream& operator<<(std::ostream& os, const String& other);
	friend void readConsole(String& toReturn);
	void readBinary(std::istream& fs);
	void writeBinary(std::ostream& fs)const;
	void readConsole(String& toReturn);
	friend std::istream& getline(std::istream& is, String& str, char delim);

private:
	void copyFrom(const String& other);
	void free();
	void resize(size_t newCapacity);
	size_t allocateCapacity(size_t size)const;
	char* string = nullptr;
	size_t capacity = 1;
	size_t size = 0;
};

namespace
{
	constexpr size_t MAX_SIZE = 1024;
}

std::istream& operator>>(std::istream& is, String& other);
std::istream& operator>>(std::istream& is, String& other);
