#include"string.h"

void String::reserve(size_t capacity)
{
	if (capacity > _capacity)//如果新容量大于旧容量，则开辟空间
	{
		char *str = new char[capacity + 1];
		if (_str) {
			strcpy(str, _str);
		}
		delete[]_str;
		_str = str;
		_capacity = capacity;
	}
}
void String::resize(size_t size, char ch)
{
	if (size > _size)
	{
		if (size > _capacity) {
			reserve(size);
		}
		for (size_t i = _size; i < size; i++)
		{
			_str[i] = ch;
		}
		_size = size;
		_str[_size] = '\0';
	}
	else{
		_size = size;
	}
}

String& String::insert(size_t pos, char ch)
{
	assert(pos <= _size);

	_size++;
	if (_size > _capacity) {
		reserve(_capacity * 2);
	}//空间不足则扩容
	
	for (size_t i = _size; i > pos; i--)
	{
		_str[i] = _str[i - 1];
	}
	_str[pos] = ch;
	return *this;
}
String& String::insert(size_t pos, const char* str)
{
	assert(pos <= _size);

	int len = strlen(str);
	_size += len;
	if (_size > _capacity) {
		reserve(_capacity * 2);
	}//空间不足则扩容

	for (size_t i = _size; i > pos; i--)
	{
		_str[i] = _str[i - len];
	}
	strncpy(_str + pos, str, len);;
	return *this;
}
String& String::push_back(char ch) {
	insert(_size, ch);
	return *this;
}
String& String::append(const char* str) {
	insert(_size, str);
	return *this;
}
String& String::append(size_t n, char c)
{
	for (size_t i = 0; i < n; ++i)
		push_back(c);
	return *this;
}
String& String::erase(size_t pos, size_t len)
{
	assert(pos <= _size);

	if (pos >= _size - len) {
		_size = pos;
		_str[_size] = '\0';
	}
	else {
		for (int i = pos; i < (int)_size; i++) {
			_str[i] = _str[i + len];
		}
	}
	return *this;
}
size_t String::find(char ch, size_t pos) const {
	for (int i = pos; i < (int)_size; ++i) {
		if (ch == _str[i]) {
			return i;
		}
	}
	return -1;
}
size_t String::find(const char* str, size_t pos) const
{
	char *temp = strstr(_str + pos, str);
	if (temp) {
		return temp - _str;
	}
	return -1;
}

String& String::operator+=(char ch) {
	insert(_size, ch);
	return *this;
}
String& String::operator+=(const char* str) {
	insert(_size, str);
	return *this;
}
String String::operator+(char ch) const {
	String temp(*this);
	temp += ch;
	return temp;
}
String String::operator+(const char* str) const {
	String temp(*this);
	temp += str;
	return temp;
}
char& String::operator[](size_t pos) {
	return *(_str + pos);
}
const char& String::operator[](size_t pos) const {
	return *(_str + pos);
}

bool String::operator>(const String& s) const
{
	int res = strcmp(_str, s._str);
	if (res>0) {
		return true;
	}
	return false;
}
bool String::operator==(const String& s) const {
	int ret = strcmp(_str, s._str);
	if (!ret) {
		return true;
	}
	return false;
}
bool String::operator>=(const String& s) const {
	return *this > s || *this == s;
}
bool String::operator<(const String& s) const {
	return !(*this >= s);
}
bool String::operator<=(const String& s) const {
	return !(*this > s);
}
bool String::operator!=(const String& s) const {
	return !(*this == s);
}

std::ostream& operator<<(std::ostream& _cout, const String& s)
{
	_cout << s._str;
	return _cout;
}
std::istream& operator>>(std::istream& _cin, String& s)
{
	if (s._str) {
		delete[] s._str;
		s._str = nullptr;
		s._capacity = 0;
		s._size = 0;
	}
	
	char *temp = new char[2048];
	_cin >> temp;

	int len = strlen(temp);
	s.reserve(len);
	
	strcpy(s._str, temp);
	
	delete[] temp;
	temp = nullptr;//释放temp并置空

	s._size = len;

	return _cin;
}

void Test1()
{
	String s1;
	String s2("hello bit");
	String s3(s2);
	s1 = s3;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
}
void Test2()
{
	String s1("hello");
	s1.push_back(' ');
	s1.push_back('b');
	s1.append(1, 'i');
	s1 += 't';
	cout << s1 << endl;
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;
	// 利用迭代器打印string中的元素
	auto it = s1.begin();
	while (it != s1.end())
	{
		cout << *it++;
	}
	cout << endl;
	String s2("hello world!!!");
	s1.swap(s2);
	cout << s1 << endl;
	cout << s2 << endl;
}
void Test3()
{
	String s("hello");
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	s.resize(10, 'a');
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	s.resize(20);
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	s.resize(5);
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	s.reserve(50);
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;
}
int main()
{
	Test1();
	system("pause");
	return 0;
}
