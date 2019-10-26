#pragma once

#include <iostream>
#include <assert.h>
#include <string.h>

class String {
	friend std::ostream& operator<<(std::ostream& _cout, const String& s);
	friend std::istream& operator>>(std::istream& _cin, String& s);

public:
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin() {
		return _str;
	}

	iterator end() {
		return _str + _size;
	}

	const_iterator begin() const {
		return _str;
	}

	const_iterator end() const {
		return _str + _size;
	}

public:
	String(const char* str = "")
		: _str(nullptr)
		, _capacity(0)
	{
		assert(str != nullptr);

		_size = strlen(str);
		reserve(_size);
		strcpy(_str, str);
	}

	~String() {
		if (_str) {
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}

	String(const String& s)
		: _str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String temp(s.c_str());

		swap(temp);
	}

	String& operator=(String s) {
		swap(s);

		return *this;
	}

public:
	void reserve(size_t capacity);

	void resize(size_t size, char ch = 0);

public:
	String& operator+=(char ch);
	String& operator+=(const char* str);
	String operator+(char ch) const;
	String operator+(const char* str) const;
	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;

public:
	String& insert(size_t pos, char ch);
	String& insert(size_t pos, const char* str);
	String& push_back(char ch);
	String& append(const char* str);
	String& erase(size_t pos, size_t len = -1);
	size_t find(char ch, size_t pos = 0) const;
	size_t find(const char* str, size_t pos = 0) const;

public:
	bool operator>(const String& s) const;
	bool operator==(const String& s) const;
	bool operator>=(const String& s) const;
  bool operator<(const String& s) const;
	bool operator<=(const String& s) const;
	bool operator!=(const String& s) const;

public:
	size_t size() const {
		return _size;
	}

	size_t capacity() const {
		return _capacity;
	}

	char* c_str() const {
		return _str;
	}

	void swap(String& s) {
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

std::ostream& operator<<(std::ostream& _cout, const String& s);

std::istream& operator>>(std::istream& _cin, String& s);
