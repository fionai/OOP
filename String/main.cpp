#include <iostream>
using namespace std;

class String
{
	int len;			//длина строки, количество символов
	char* value;// = new char[];
public:
	int get_len()
	{
		return len;
	}
	char* get_value()
	{
		return value;
	}
	void set_len(int a)
	{
		this->len = a;
	}
	void set_value(char* a)
	{
		for (int i = 0; i < this->len; i++)
		{
			this->value[i] = a[i];
		}
	}
	//			Constructions
	String(char* value) //Default
	{
		//this->len = !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		this->value = new char[this->len];
	}
	String(const String& other) //Copy Constructor
	{
		this->len = other.len;
		for (int i = 0; i < this->len; i++)
		{
			this->value[i] = other.value[i];
		}
	}

};

void main()
{
	setlocale(LC_ALL, "");
	//String str1("Hello");
	int n = 15;
	char* arr = new char[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = 70+i;
	}
	for (int i = 0; i < n; i++)
	{
		cout << arr[i];
	}
	cout << endl << n << "\t" << sizeof(&arr);
	delete[] arr;
}