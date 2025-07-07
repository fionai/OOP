#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
using std::cout;

#define delimiter "\n------------------------------------------------\n"

// ================================= CLASS DECLARATION. ќбъ€вление класса =====================

class Fraction;
Fraction operator* (Fraction left, Fraction right);
Fraction operator/ (const Fraction left, const Fraction right);
Fraction operator+ (Fraction left, Fraction right);
Fraction operator- (const Fraction left, const Fraction right);
bool operator== (Fraction left, Fraction right);
bool operator!= (const Fraction left, const Fraction right);
bool operator> (Fraction left, Fraction right);
bool operator< (Fraction left, Fraction right);
std::ostream& operator<< (std::ostream& os, Fraction& obj);
std::istream& operator>> (std::istream& is, Fraction& obj);


class Fraction
{
	long long int integer;
	long long int numerator;
	long long int denominator;

public:
	long long int get_integer() const;
	long long int get_numerator() const;
	long long int get_denominator() const;

	void set_integer(long long int integer);
	void set_numerator(long long int numerator);
	void set_denominator(long long int denominator);

	//				contructions
	Fraction();
	Fraction(long long int integer, long long int numerator, long long int denominator);
	Fraction(long long int numerator, long long int denominator);
	Fraction(long long int integer);
	Fraction(double decimal);
	Fraction(const Fraction& other);
	~Fraction();

	//				Operators
	Fraction& operator= (const Fraction& other);
	Fraction& operator*= (const Fraction other);
	Fraction& operator/= (const Fraction other);
	Fraction& operator+= (const Fraction other);
	Fraction& operator-= (const Fraction other);

	//			Icrement/Decrement
	Fraction& operator++();
	Fraction operator++ (int);
	Fraction& operator--();
	Fraction operator-- (int);

	//Type-cast operastors
	operator int() const;
	operator double() const;

	//				Methods
	Fraction& to_improper(); //переводит дробь в неправильную
	Fraction& Reduce(); //сокращает дробь
	Fraction& to_proper(); //переводит дробь в правильную
	Fraction invert()const;
	void print()const;
};

// ================================= CLASS DECLARATION. END.  ќЌ≈÷. ќбъ€вление класса =====================