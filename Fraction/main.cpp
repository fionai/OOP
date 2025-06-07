#include <iostream>
using namespace std;

int GCD(const int a = 1, const int b = 1) //	Find a Gratest Common Divisor
{
	if (!a || !b)
		return 0;
	int big, small, buf;
	if (a > b)
	{
		big = a;
		small = b;
	}
	else if (b > a)
	{
		big = b;
		small = a;
	}
	else if (a == b)
		return a;
	while (big % small)
	{
		buf = big % small;
		big = small;
		small = buf;
	}
	return small;
}

class Fraction
{
	//int integer;
	int numerator;
	int denominator;
public:
	int get_numerator() const
	{
		return numerator;
	}
	int get_denominator() const
	{
		return denominator;
	}
	void set_numerator(int x)
	{
		this->numerator = x;
	}	
	void set_denominator(int x)
	{
		this->denominator = x;
	}
	
	//			Constructors
	Fraction (int n = 0, int d = 1) // по умолчанию
	{
		//this->integer = i;
		this->numerator = n;
		this->denominator = d;
	}
	Fraction(const Fraction& other)	//CopyConstruction
	{
		this->numerator = other.numerator;
		this->denominator = other.denominator;
	}
	//			Destructor
	~Fraction()
	{

	}

	//			Operators

	Fraction operator ++ ()		
	{
		this->Normal_Minus();

		this->numerator += this->denominator;
		int dd = GCD(this->numerator, this->denominator);									//	находим НОД
		if (dd)
		{
			this->numerator /= dd;								//	сокращаем дробь
			this->denominator /= dd;
		}
		else this->denominator = 0;
		return *this;
	}
	Fraction operator--()
	{ 
		this->Normal_Minus();
	
		this->numerator -= this->denominator;
		int dd = GCD(this->numerator, this->denominator);									//	находим НОД
		if (dd)
		{
			this->numerator /= dd;								//	сокращаем дробь
			this->denominator /= dd;
		}
		else this->denominator = 0;
		return *this;
	}
/*	
	Fraction operator+=()
	{ }
	Fraction operator-=()
	{ }
	Fraction operator*=()
	{	}
	Fraction operator/=()
	{	}*/

	//			Methods
	void Print() const
	{
		if (!this->denominator)
			cout << "Ошибка: Деление на 0.";
		else
			cout << this->numerator << "/" << this->denominator;
	}
	Fraction Normal_Minus()				// нормализация нулей
	{
		if (this->numerator < 0 and this->denominator < 0) 
		{
			this->numerator = -this->numerator;
			this->denominator = -this->denominator;
		}
		return *this;
	}

	//int GCD() //	Find a Gratest Common Divisor
	//{
	//	if (!this->denominator || !this->numerator)
	//		return 0;
	//	int big, small, buf;
	//	if (this->denominator > this->numerator)
	//	{
	//		big = this->denominator;
	//		small = this->numerator;
	//	}
	//	else if (this->numerator > this->denominator)
	//	{
	//		big = this->numerator;
	//		small = this->denominator;
	//	}
	//	else if (this->numerator == this->denominator)
	//		return this->denominator;
	//	while (big % small)
	//	{
	//		buf = big % small;
	//		big = small;
	//		small = buf;
	//	}
	//	return small;
	//}

};		//class Fraction

//Fraction Normal_Minus(Fraction& x)				// нормализация нулей
//{
//	if (x.get_numerator() < 0 and x.get_denominator() < 0)
//	{
//		x.set_numerator(-x.get_numerator());
//		x.set_denominator(-x.get_denominator());
//	}
//	return x;
//}
Fraction operator+(const Fraction& x, const Fraction& y)
{
	Fraction res;
	int n, d;
	if (!x.get_denominator() or !y.get_denominator())
	{
		res.set_numerator(0);
		res.set_denominator(0);
		return res;
	}
	n = x.get_numerator() * y.get_denominator() + y.get_numerator() * x.get_denominator();
	d = x.get_denominator() * y.get_denominator();
	int dd = GCD(n, d);
	if (dd)
	{
		n /= dd;
		d /= dd;
	}
	res.set_numerator(n);
	res.set_denominator(d);
	return res;
}
/*
Fraction operator-(const Fraction x, const Fraction y)
{ }
Fraction operator/(const Fraction x, const Fraction y)
{ }
Fraction operator*(const Fraction x, const Fraction y)
{ }
bool operator>(const Fraction x, const Fraction y)
{ }
bool operator<(const Fraction x, const Fraction y)
{ }
bool operator==(const Fraction x, const Fraction y)
{ }
bool operator!=(const Fraction x, const Fraction y)
{ }*/

void main()
{
	setlocale(LC_ALL, "");

	Fraction cf1 (-7, -13),  cf2 (2, 5), cf3;			// CommonFraction
	cout << "Начальные значения дробных чисел:\n";
	cf1.Print();
	cout << "\t";
	cf2.Print();
	cout << endl;

	cf1 = cf2;
	cout << "Первой переменной присвоили переменной значение второй переменной. Значения переменных равны: ";
	cf1.Print();
	cout << " ";
	cf2.Print();
	cout << endl;

	cout << "++(";
	cf1.Print();
	cout << ") = ";
	++cf1;
	cf1.Print();
	cout << endl;

	cout << "--(";
	cf1.Print();
	cout << ") = ";
	--cf1;
	cf1.Print();
	cout << endl;

	cf1 = Fraction(2, 7);
	cf2 = Fraction(2, 10);
	cf3 = cf1 + cf2;
	cf1.Print();
	cout << " + ";
	cf2.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	//cout << endl << GCD(51, 221);
	//cout << endl << GCD(221, 51);
	//cout << endl << GCD(13, 13);

}