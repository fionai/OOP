#include "String.h"



//#define OPRATOR_PLUS
//#define CONSTRUCTORS_CHECK
#define ISTREAM_OPERATOR
//#define PERFORMANCE_TEST
//#define CALLING_CONSTRUCTORS

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
	String str4 = str3;
	cout << str4 << endl;
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

#ifdef CALLING_CONSTRUCTORS
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
#endif // CALLING_CONSTRUCTORS


}