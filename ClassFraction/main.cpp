#include "ClassFraction.h"



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
	//Fraction(2, 3, 4); - явный вызов конструктора, который создает временный безымянный объект

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
	cout << "Введите дробь: ";
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

	Fraction B(2, 3, 5);
	B.print();
}