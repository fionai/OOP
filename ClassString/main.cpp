#include<Windows.h>
#include <iostream>
using namespace std;
#define delimiter "\n----------------------------------\n"
#define DEBUG

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
#ifdef DEBUG
		cout << "DefaultConstruction\t" << this << endl;
#endif // DEBUG
	}
	String(const char str[])
	{
		size = 0;
		while (str[size++]);
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++)
			this->str[i] = str[i];
#ifdef DEBUG


		cout << "Constructor:\t\t" << this << endl;
#endif // DEBUG
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {0};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
#ifdef DEBUG


		cout << "DeepCopy:\t\t" << this << endl; //Побитовое копирование
#endif // DEBUG
	}
	String(String&& other)
	{
		this->size = other.size;
		this->str = other.str;
		other.size = 0;
		other.str = nullptr;//защищаем памят от удаления деструктором


#ifdef DEBUG
		cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~String()
	{
		delete[] str;
		this->str = nullptr;
		this->size = 0;


#ifdef DEBUG
		cout << "Destructor\t\t" << this << endl;
#endif // DEBUG
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


#ifdef DEBUG
		cout << "CopyAssignment:\t\t" << this << endl; //Побитовое копирование
#endif // DEBUG
		return *this;
	}
	String& operator=(String&& other)
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

String operator+(const String& left, const String& right)
{
	String result( left.get_size() + right.get_size() - 1);
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

//#define OPRATOR_PLUS
//#define CONSTRUCTORS_CHECK
//#define ISTREAM_OPERATOR

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

#ifdef OPRATOR_PLUS
	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3;
	str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
#endif // OPRATOR_PLUS

#ifdef ISTREAM_OPERATOR
	String str;
	cout << "Enter a string: ";
	SetConsoleCP(1251);
	//cin >> str;
	SetConsoleCP(866);
	//cin.getline(str.get_str(), str.get_size());
	getline(cin, str);
	cout << str << endl;
#endif // ISTREAM_OPERATOR

	String str1; //default Constructor
	str1.info();

	String str2(8); //single-argument constructor
	str2.info();

	String str3 = "Hello"; // single-argument constyructor (const char*)
	str3.info();

	cout << typeid("Hello").name() << endl;

	String str4(); // не вызывается никакой конструктор и не создается никакой объект,
					//здесь происходит объявление функции str4, которая ничего не принимает
					//и возвращает объект типа String
	//ВЫВОД - пустые куглые скобки не вызывают конструктор. Не делают явный вызов конструктора
	//ЕСЛИ нужно явно вызвать Default constructor, это можно сделать с {}

	String str5(8);		//инициализация в стиле с++
	String str6{ 8 };	//тоже создается строка длиной 8 байт, т.е. {} вызывают конструктор
	String str7{};		//явный вызов конструтора по умолчанию
	// !!!!!!!!!!!     {}    СЛЕДУЕТ ИСПОЛЬЗОВАТЬ С ОСТОРОЖНОСТЬЮ           !!!!!!!!!!

	String str9 = str3;	//конструктор копирования

}