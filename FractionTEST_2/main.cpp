#include<ClassFraction.h>

void main()
{
	setlocale(LC_ALL, "");
	Fraction F1(2, 3, 5);
	F1.print();

	Fraction F2 = 2.76;
	F2.print();
}