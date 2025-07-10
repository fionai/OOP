#include <myMatrix.h>

void main()
{
	Matrix M1(3, 4);
	M1.FillRand();
	cout << "M1\n";
	M1.PrintM();

	Matrix M2(3, 4);
	M2.FillRand();
	cout << "M2\n";
	M2.PrintM();

	Matrix M3;
	M3 = M1 + M2;
	cout << "M1 + M2 =\n";
	M3.PrintM();

	Matrix M4(3, 4);
	M4.FillRand();
	cout << "M4\n";
	M4.PrintM();

	Matrix M5(4, 5);
	M5.FillRand();
	cout << "M5\n";
	M5.PrintM();

	Matrix M6;
	M6 = M4 * M5;
	cout << "M4 * M5 =\n";
	M6.PrintM();

	Matrix M7 (4,4);
	M7.FillRand();
	cout << "M7\n";
	M7.PrintM();
	Matrix inv = M7;

	inv.Inverse();
	cout << "M7 inverse =\n";
	inv.PrintM();

	Matrix M8;
	M8 = M7 * inv;
	cout << "Check. M7 * M7.inverse =\n";
	M8.PrintM();
}

