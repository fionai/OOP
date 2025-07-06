#include<ClassFraction.h>

void main()
{
	setlocale(LC_ALL, "");
	Fraction F1(2, 3, 5);
	F1.print();

	Fraction F2(3);
	F2.print();

	Fraction F3(3, 7);
	F3.print();

	Fraction F4 = F1 * F3;
	F4.print();
}