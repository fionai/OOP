#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
using std::cout;

#define delimiter "\n------------------------------------------------\n"

class Fraction;
Fraction operator* (Fraction left, Fraction right);
Fraction operator/ (const Fraction left, const Fraction right);
Fraction operator+ (Fraction left, Fraction right);
Fraction operator- (const Fraction left, const Fraction right);

class Fraction
{
	int integer;
	int numerator;
	int denominator;

public:
	int get_integer() const
	{
		return integer;
	}
	int get_numerator() const
	{
		return numerator;
	}
	int get_denominator() const
	{
		return denominator;
	}

	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
	}

	//				contructions
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		//cout << "Default conatruction:\t" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		//cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->denominator = denominator;
		//cout << "Construction:\t\t" << this << endl;
	}
	Fraction(double decimal)
	{
		decimal += 1e-10;
		integer = decimal;
		decimal -= integer;
		denominator = 1e+9;
		numerator = decimal * denominator;
		Reduce();
	}
	Fraction(int integer , int numerator , int denominator )
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		//cout << "Constructor: \t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		//cout << "CopyConstruction:\t" << this << endl;
	}
	~Fraction()
	{
		//cout << "Destructor:\t\t" << this << endl;
	}
	//				Operators
	Fraction& operator= (const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		//cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator*= (const Fraction other)
	{
		return *this = *this * other;
	}
	Fraction& operator/= (const Fraction other)
	{
		return *this = *this / other;
	}
	Fraction& operator+= (const Fraction other)
	{
		return *this = *this + other;
	}
	Fraction& operator-= (const Fraction other)
	{
		return *this = *this - other;
	}
	//			Icrement/Decrement
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++ (int)
{
	Fraction old = *this;
	integer++;
	return old;
}
	Fraction& operator--()
	{
		return *this = *this - Fraction(1);
	}
	Fraction operator-- (int)
	{
		Fraction old = *this;
		*this = *this - Fraction(1);
		return old;
	}
	//Type-cast operastors
	 operator int() const
	{
		return integer + numerator / denominator;
	}
	 operator double() const
	{
		return integer + (double)numerator / denominator;
	}
	//				Methods
	Fraction& to_improper() //��������� ����� � ������������
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& Reduce()
	{
		int more, less, rest;
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
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction invert()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	void print()const
	{
		if (integer) cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (!integer) cout << 0;
		cout << endl;
	}
};
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
	return (left.get_numerator() * right.get_denominator() > right.get_numerator() * left.get_denominator()? 1:0);
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
	/*int integer, numerator, denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);*/
	
	const int SIZE = 32;
	char sz_input[SIZE] = {};
	//is >> sz_input;
	is.getline(sz_input, SIZE);
	const char delimiters[] = { '/', '(', ')', ' ', '.', ',', 0};
	int numbers[3] = {};
	int n = 0;
	for (char* pch = strtok(sz_input, delimiters); pch && n<3; pch = strtok(NULL, delimiters))
		numbers[n++] = atoi(pch);

	switch (n)
	{
	case 1:obj = numbers[0]; break;
	case 2:obj = Fraction(numbers[0], numbers[1]); break; 
	case 3:obj = Fraction(numbers[0], numbers[1], numbers[2]); break;
	}

	return is;
}

//#define CONSRTUCTIONS_CHECK
//#define ASSIGNMENT_CHECK
//#define ARITHMETICAL_OPERATORS
//#define INC_DEC
//#define COMPARISON
//#define ISTREAM_OPERATOR
//#define CONVERTION_FROM_CLASS_TO_OTHER


void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTIONS_CHECK
	Fraction A;			//Default C
	A.print();

	Fraction B = 5;		//Single-argument C
	B.print();

	Fraction C(1, 2);	//Constructor
	C.print();

	Fraction D(2, 3, 4);//cONSTRUCTOR
	D.print();

	Fraction E = D;		//cOPY C
	E.print();

	Fraction F;
	F = E;				//CopyAssignment
	F.print();
#endif // CONSTRUCTIONS_CHECK

#ifdef ASSIGNMENT_CHECK


	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	Fraction A, B, C;
	cout << delimiter;
	A = B = C = Fraction(2, 3, 4);
	//Fraction(2, 3, 4); - ����� ����� ������������, ������� ������� ��������� ���������� ������

	cout << delimiter;
#endif // ASSIGNMENT_CHECK

#ifdef ARITHMETICAL_OPERATORS


	Fraction A(1, 2);
	Fraction B(3, 4);

	Fraction C = A * B;
	cout << A << "*" << B << "=" << C << endl;

	C = A / B;
	cout << "(" << A << ")" << "/" << "(" << B << ")" << "=" << C << endl;
	
	C = A + B;
	cout << A << "+" << B << "=" << C << endl;

	C = A - B;
	cout << A << "-" << B << "=" << C << endl;

	C = A;
	cout << "C=" << C;
	C *= B;
	cout << ", B=" << B << ". C *= B.\t C=" << C << endl;

	C = A;
	cout << "C=" << C;
	C /= B;
	cout << ", B=" << B << ". C /= B.\t C=" << C << endl;

	C = A;
	cout << "C=" << C;
	C += B;
	cout << ", B=" << B << ". C += B.\t C=" << C << endl;

	C = A;
	cout << "C=" << C;
	C -= B;
	cout << ", B=" << B << ". C -= B.\t C=" << C << endl;

#endif // ARITHMETICAL_OPERATORS

#ifdef INC_DEC


	Fraction A(1, 3);
	cout << "A=" << A;
	Fraction B = ++A;
	cout << ", B=" << "++A\t A=" << A << ", B=" << B << endl;

	A = Fraction(1, 3);
	cout << "A=" << A;
	B = A++;
	cout << ", B=" << "A++\t A=" << A << ", B=" << B << endl;

	A = Fraction(1, 3);
	cout << "A=" << A;
	B = --A;
	cout << ", B=" << "--A\t A=" << A << ", B=" << B << endl;

	A = Fraction(1, 3);
	cout << "A=" << A;
	B = A--;
	cout << ", B=" << "A--\t A=" << A << ", B=" << B << endl;

#endif // INC_DEC

#ifdef COMPARISON
	Fraction A(1, 2);
	Fraction B(5, 10);
	cout << "A=" << A << ", B=" << B << "\t\tA==B is " << (A == B) << endl;
	A = Fraction(1, 2);
	B = Fraction(3, 4);
	cout << "A=" << A << ", B=" << B << "\t\tA==B is " << (A == B) << endl;

	A = Fraction(1, 2);
	B = Fraction(3, 6);
	cout << "A=" << A << ", B=" << B << "\t\tA!=B is " << (A != B) << endl;
	A = Fraction(1, 2);
	B = Fraction(3, 7);
	cout << "A=" << A << ", B=" << B << "\t\tA!=B is " << (A != B) << endl;

	A = Fraction(1, 2);
	B = Fraction(3, 6);
	cout << "A=" << A << ", B=" << B << "\t\tA>B is " << (A > B) << endl;
	A = Fraction(1, 1, 2);
	B = Fraction(3, 6);
	cout << "A=" << A << ", B=" << B << "\t\tA>B is " << (A > B) << endl;
	A = Fraction(1, 2);
	B = Fraction(5, 6);
	cout << "A=" << A << ", B=" << B << "\t\tA>B is " << (A > B) << endl;

	A = Fraction(1, 2);
	B = Fraction(3, 6);
	cout << "A=" << A << ", B=" << B << "\t\tA<B is " << (A < B) << endl;
	A = Fraction(1, 1, 2);
	B = Fraction(3, 6);
	cout << "A=" << A << ", B=" << B << "\t\tA<B is " << (A < B) << endl;
	A = Fraction(1, 2);
	B = Fraction(5, 6);
	cout << "A=" << A << ", B=" << B << "\t\tA<B is " << (A < B) << endl;

#endif // COMPARISON

#ifdef ISTREAM_OPERATOR
	Fraction A;
	cout << "������� �����: ";
	cin >> A;
	cout << A << endl;
#endif // ISTREAM_OPERATOR

#ifdef CONVERTION_FROM_CLASS_TO_OTHER


	Fraction A(2, 5, 4);
	cout << A << endl;

	int a = A;
	cout << a << endl;

	double b = A;
	cout << b << endl;
#endif // CONVERTION_FROM_CLASS_TO_OTHER

	Fraction A = 2.76;
	cout << A << endl;
}