#include "String.h"



int String::get_size() const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
//		constructors
String::String(int size) :size(size), str(new char[this->size] {})
{
#ifdef DEBUG
	cout << "DefaultConstruction\t" << this << endl;
#endif // DEBUG
}
String::String(const char str[]) :String(strlen(str) + 1)
{
	for (int i = 0; str[i]; i++)
		this->str[i] = str[i];
#ifdef DEBUG
	cout << "Constructor:\t\t" << this << endl;
#endif // DEBUG
}
String::String(const String& other) :String(other.str)
{
#ifdef DEBUG
	cout << "DeepCopy:\t\t" << this << endl; //Побитовое копирование
#endif // DEBUG
}
String::String(String&& other) :size(other.size), str(other.str)
{
	other.size = 0;
	other.str = nullptr;//защищаем памят от удаления деструктором
#ifdef DEBUG
	cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG
}
String::~String()
{
	delete[] str;
	this->str = nullptr;
	this->size = 0;

#ifdef DEBUG
	cout << "Destructor\t\t" << this << endl;
#endif // DEBUG
}
//		Operators
String& String::operator= (const String& other)
{
	if (this == &other)
		return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = new char[size] {0};
	for (int i = 0; i < size; i++)
		this->str[i] = other.str[i];
#ifdef DEBUG
	cout << "CopyAssignment:\t\t" << this << endl; //Побитовое копирование
#endif // DEBUG
	return *this;
}
String& String::operator=(String&& other)
{
	if (this == &other) return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.size = 0;
	other.str = nullptr;


#ifdef DEBUG
	cout << "MoveAssignment:\t\t" << this << endl;
#endif // DEBUG
	return *this;
}
String& String::operator+=(const String other)
{
	return *this = *this + other;
}
char String::operator[] (int i) const
{
	return str[i];
}
char& String::operator[] (int i)
{
	return str[i];
}
//		Metods
void String::info() const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	for (int i = 0; left[i]; i++)
		result[i] = left[i];
	for (int i = 0; right[i]; i++)
		result[left.get_size() - 1 + i] = right[i];


#ifdef DEBUG
	cout << "Operator+\n";
#endif // DEBUG
	return result;
}

std::ostream& operator<< (std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
std::istream& operator>>(std::istream& cin, String& obj)
{
	const int SIZE = 1024;
	char buffer[SIZE] = {};
	cin >> buffer;
	obj = buffer;
	return cin;

}
std::istream& getline(std::istream& cin, String& obj)
{
	cin.getline(obj.get_str(), obj.get_size());
	return cin;
}

/// -----------------------------------------------------------------///
///			КОНЕЦ.	Определение класса. Class Definition END
