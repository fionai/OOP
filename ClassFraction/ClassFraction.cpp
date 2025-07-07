#include "ClassFraction.h"

// -----------------------------------------------------------------------------------

// ================================= CLASS DEFINITION. Определение класса =====================

long long int Fraction::get_integer() const
{
	return integer;
}
int Fraction::get_numerator() const
{
	return numerator;
}
int Fraction::get_denominator() const
{
	return denominator;
}

void Fraction::set_integer(int integer)
{
	this->integer = integer;
}
void Fraction::set_numerator(int numerator)
{
	this->numerator = numerator;
}
void Fraction::set_denominator(int denominator)
{
	if (denominator == 0) denominator = 1;
	this->denominator = denominator;
}

//				contructions
Fraction::Fraction()
{
	this->integer = 0;
	this->numerator = 0;
	this->denominator = 1;
	//cout << "Default construction:\t" << this << endl;
}
Fraction::Fraction(int integer, int numerator, int denominator)
{
	this->integer = integer;
	this->numerator = numerator;
	this->denominator = denominator;
	//cout << "Constructor: \t\t" << this << endl;
}
Fraction::Fraction(int numerator, int denominator)
{
	this->integer = 0;
	this->numerator = numerator;
	this->denominator = denominator;
	//cout << "Construction:\t\t" << this << endl;
}
Fraction::Fraction(int integer)
{
	this->integer = integer;
	this->numerator = 0;
	this->denominator = 1;
	//cout << "Constructor:\t\t" << this << endl;
}
Fraction::Fraction(double decimal)
{
	decimal += 1e-10;
	integer = decimal;
	decimal -= integer;
	denominator = 1e+9;
	numerator = decimal * denominator;
	Reduce();
}
Fraction::Fraction(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	//cout << "CopyConstruction:\t" << this << endl;
}
Fraction::~Fraction()
{
	//cout << "Destructor:\t\t" << this << endl;
}
//				Operators
Fraction& Fraction::operator= (const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	//cout << "CopyAssignment:\t\t" << this << endl;
	return *this;
}
Fraction& Fraction::operator*= (const Fraction other)
{
	return *this = *this * other;
}
Fraction& Fraction::operator/= (const Fraction other)
{
	return *this = *this / other;
}
Fraction& Fraction::operator+= (const Fraction other)
{
	return *this = *this + other;
}
Fraction& Fraction::operator-= (const Fraction other)
{
	return *this = *this - other;
}
//			Icrement/Decrement
Fraction& Fraction::operator++()
{
	integer++;
	return *this;
}
Fraction Fraction::operator++ (int)
{
	Fraction old = *this;
	integer++;
	return old;
}
Fraction& Fraction::operator--()
{
	return *this = *this - Fraction(1);
}
Fraction Fraction::operator-- (int)
{
	Fraction old = *this;
	*this = *this - Fraction(1);
	return old;
}
//Type-cast operastors
Fraction::operator int() const
{
	if (!denominator)
		return Fraction(0, 0, 1);
	return integer + numerator / denominator;
}
Fraction::operator double() const
{
	if (!denominator)
		return Fraction(0, 0, 1);
	return integer + (double)numerator / denominator;
}
//				Methods
Fraction& Fraction::to_improper() //переводит дробь в неправильную
{
	numerator += integer * denominator;
	integer = 0;
	return *this;
}
Fraction& Fraction::Reduce()
{
	int more, less, rest;
	if (!numerator || !denominator)
		return *this;
	if (numerator < denominator)
	{
		less = numerator;
		more = denominator;
	}
	else
	{
		more = numerator;
		less = denominator;
	}
	do
	{
		rest = more % less;
		more = less;
		less = rest;
	} while (rest);
	numerator /= more;
	denominator /= more;
	return *this;
}
Fraction& Fraction::to_proper()
{
	Fraction tmp (0, 0, 1);
	if (!denominator)
		return tmp;
	integer += numerator / denominator;
	numerator %= denominator;
	return *this;
}
Fraction Fraction::invert()const
{
	Fraction inverted = *this;
	inverted.to_improper();
	swap(inverted.numerator, inverted.denominator);
	return inverted;
}
void Fraction::print()const
{
	if (integer) cout << integer;
	if (numerator)
	{
		if (integer) cout << "(";
		cout << numerator << "/" << denominator;
		if (integer) cout << ")";
	}
	else if (!integer) cout << 0;
}

//============= up IN CLASS up ===============

Fraction operator* (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator/ (const Fraction left, const Fraction right)
{
	return left * right.invert();
}
Fraction operator+ (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator- (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator() - right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
bool operator== (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();
}
bool operator!= (const Fraction left, const Fraction right)
{
	return !(left == right);
}
bool operator> (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return (left.get_numerator() * right.get_denominator() > right.get_numerator() * left.get_denominator() ? 1 : 0);
}
bool operator< (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return (left.get_numerator() * right.get_denominator() < right.get_numerator() * left.get_denominator() ? 1 : 0);
}

std::ostream& operator<< (std::ostream& os, Fraction& obj)
{
	if (obj.get_integer())
	{
		os << obj.get_integer();
		if (obj.get_numerator())
		{
			if (obj.get_numerator()) os << "(";
			os << obj.get_numerator() << "/" << obj.get_denominator();
			if (obj.get_integer()) os << ")";
		}
	}
	else if (!obj.get_integer())
	{
		if (obj.get_numerator())
			os << obj.get_numerator() << "/" << obj.get_denominator();
	}
	else
	{
		os << 0;
	}
	return os;
}
std::istream& operator>> (std::istream& is, Fraction& obj)
{

	const int SIZE = 32;
	char sz_input[SIZE] = {};
	//is >> sz_input;
	is.getline(sz_input, SIZE);
	const char delimiters[] = { '/', '(', ')', ' ', '.', ',', 0 };
	int numbers[3] = {};
	int n = 0;
	for (char* pch = strtok(sz_input, delimiters); pch && n < 3; pch = strtok(NULL, delimiters))
		numbers[n++] = atoi(pch);

	switch (n)
	{
	case 1:obj = numbers[0]; break;
	case 2:obj = Fraction(numbers[0], numbers[1]); break;
	case 3:obj = Fraction(numbers[0], numbers[1], numbers[2]); break;
	}

	return is;
}

// ================================= CLASS DEFINITION END. КОНЕЦ. Определение класса =====================
