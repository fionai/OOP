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
	String operator+ (const String& other) 
	{
		String str3;
		str3.size = this->size + other.size - 1;
		str3.str = new char[str3.size];
		cout << "operator+\t\t" << &str3 << endl;
		for (int i = 0; i < this->size - 1; i++)
		{
			str3.str[i] = this->str[i];
		}
		for (int i = 0; i < other.size; i++)
		{
			str3.str[i + this->size - 1] = other.str[i];
		}
		return str3;
	}
	String operator+= (const String& other)
	{
		return *this = *this + other;
	}
	//		Metods
	void info() const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

std::ostream& operator<< (std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
std::istream& operator>> (std::istream& is, String& obj)
{
	const int SIZE = 500;
	char buf[SIZE] = {};
	is.getline(buf, SIZE);
	//cout << (int)buf[0] << "--" << (int)'п'<< endl;
	String str3(buf);
	obj = str3;
	return is;
}
void main()
{
	setlocale(LC_ALL, "");
	String str1 = "Good";		//explicit конструктор нельзя вызвать оператором Присвоить, но всегда можно вызвать при помощи ()
	str1.info();
	cout << str1 << endl;

	String str2;
	str2 = "day";
	cout << str2 << endl;

	String str3;
	str3 = str1 + " " +str2;
	cout << "\t\t\t\t+\t" << str3 << endl;

	String str4 = "teacher";
	str3 += (String)", " + str4 + "!";
	cout << "\t\t\t\t+=\t" << str3 << endl;

	String str5;
	cout << "Введите строку: ";
	cin >> str5;
	cout << "\t\t\t\tВы ввели " << str5 << endl;
	cout << "Объявились проблемы с русской кодировкой.\nОлег Анатольевич, введите строку на кириллице: ";
	cin >> str5;
	cout << "\t\t\t\tВы ввели " << str5 << endl;
}