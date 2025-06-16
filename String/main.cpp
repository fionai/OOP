#include <iostream>
using namespace std;

class String
{
	int len;			//длина строки (кол-во символов + 1)
	char* value;		//значение самой строки
public:
	int get_len()const
	{
		return len;
	}
	char* get_value()const
	{
		return value;
	}

	//			Constructors
	String (const char value[] = "", int len = 1)  //Default
	{
		int i = 0;
		while (value[i] != 0)
		{
			i++;
		}
		this->len = i + 1;
		this->value = new char[this->len];
		for (int i = 0; i < this->len; i++)
		{
			this->value[i] = value[i];
		}
		cout << "Default. new char[]\t\t" << this << endl;
	}
	~String()
	{
		//delete[] this->value;  //Я не смогла победить это
		cout << "Constructor. delete \t\t" << this << endl;
	}
	//              Operators
	String operator= (const char value[]) //присваивание константной строки
	{
		int i = 0;
		while (value[i] != 0)
		{
			i++;
		}
		this->len = i + 1;
		this->value = new char[this->len];
		for (int i = 0; i < this->len; i++)
		{
			this->value[i] = value[i];
		}
		cout << "AssignConstStr. new char[]\t\t" << this << endl;
		return *this;
	}
	String operator= (String other)		//присваивание переменной типа String
	{
		this->len = other.len;
		this->value = new char[this->len];
		cout << "AssignString. new char[]\t" << this << endl;
		for (int i = 0; i < other.len; i++)
		{
			this->value[i] = other.value[i];
		}
		return *this;
	}
	String operator+ (const String s2)
	{
		String s3;
		s3.len = this->len + s2.len - 1;
		s3.value = new char[s3.len];
		cout << "operator+. new char[]\t\t" << this << endl;
		for (int i = 0; i < s3.len; i++)
		{
			if (i < this->len-1)
				s3.value[i] = this->value[i];
			else
				s3.value[i] = s2.value[i - this->len + 1];
		}
		return s3;
	}
};

std::ostream& operator<< (std::ostream& os, String& str)
{
	os << str.get_value();
	return os;
}

void main()
{
	/*cout << sizeof("Hello") << endl;
	cout << strlen("Hello") << endl;*/
	setlocale(LC_ALL, "");

	String str1 = "Hello";
	String str2 = "World";
	String str3;
	str3 = str1 + ", " + str2 + "!";
	cout << "\t\t\t\t\t\t" << str3 << endl;
}