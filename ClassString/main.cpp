#include <iostream>
using namespace std;

class String
{
	int size;
	char* str;
public:
	int get_size() const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}
	//		constructors
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstruction\t" << this << endl;
	}
	String(const char str[])
	{
		size = 0;
		while (str[size++]);
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++)
			this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {0};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "DeepCopy:\t\t" << this << endl; //Побитовое копирование
	}
	~String()
	{
		delete[] str;
		this->str = nullptr;
		this->size = 0;
		cout << "Destructor\t\t" << this << endl;
	}
	//		Operators
	String& operator= (const String& other)
	{
		if (this == &other)
			return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {0};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl; //Побитовое копирование
		return *this;
	}
	char operator[] (int i) const
	{
		return str[i];
	}
	char& operator[] (int i) 
	{
		return str[i];
	}
	//		Metods
	void info() const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

String operator+(const String& left, const String right)
{
	String result( left.get_size() + right.get_size() - 1);
	for (int i = 0; left[i]; i++)
		result[i] = left[i];
	for (int i = 0; right[i]; i++)
		result[left.get_size() - 1 + i] = right[i];
	return result;
}

std::ostream& operator<< (std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
//#define CONSTRUCTORS_CHECK
void main()
{
#ifdef CONSTRUCTORS_CHECK
	setlocale(LC_ALL, "");
	String str1(5);		//explicit конструктор нельзя вызвать оператором Присвоить, но всегда можно вызвать при помощи ()
	str1.info();
	cout << str1 << endl;

	String str2 = "Hello";
	cout << str2 << endl;

	String str3 = str2;
	cout << str3 << endl;

	String str4;
	str4 = str3;
	cout << str4 << endl;
#endif // CONSTRUCTORS_CHECK

	String str1 = "Hello";
	String str2 = "World";
	String str3 = str1 + ", " + str2 + "!";
	cout << str3 << endl;

}