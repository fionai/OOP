#include "myMatrix.h"

void main()
{
	setlocale(LC_ALL, "");

	cout << "\t\tСЛОЖЕНИЕ\n\n";

	Matrix A(4, 3);
	A.FillRand();
	cout << "  A\n";
	A.PrintM();

	Matrix B(4, 3);
	B.FillRand();
	cout << "  B\n";
	B.PrintM();

	Matrix C;
	C = A + B;
	cout << "  A + B =\n";
	C.PrintM();

	getch();
	system("cls");

	cout << "\t\tУМНОЖЕНИЕ НА ЧИСЛО\n\n  A\n";
	A.PrintM();
	Matrix D;
	cout << "  A * 3 =\n";
	D = A * 3;
	D.PrintM();

	getch();
	system("cls");
	cout << "\t\tУМНОЖЕНИЕ ДВУХ МАТРИЦ\n\n  A\n";
	Matrix A1(3, 5);
	A1.FillRand();
	A1.PrintM();
	cout << "  B\n";
	Matrix B1(5, 4);
	B1.FillRand();
	B1.PrintM();
	Matrix E = A1 * B1;
	cout << "  A * B =\n";
	E.PrintM();

	getch();
	system("cls");
	cout << "\t\tОБРАТНАЯ МАТРИЦА\n\n  A\n";
	Matrix A2(4, 4), DUB(4,4), TEST(4,4);
	A2.FillRand();
	A2.get_arr()[0][0] = 0;
	A2.get_arr()[1][0] = 0;
	A2.get_arr()[1][1] = 0;

	DUB = A2;

	A2.PrintM();
	A2.Inverse();
	cout << "\n----------------\nInverse matrix:\n----------------\n";
	A2.PrintM();
	cout << "\n----------------\n";

	TEST = DUB * A2;			//контрольная проверка
	cout << "\n----------------\ntest\n----------------\n";
	TEST.PrintM();
	cout << "\n----------------\n";

	getch();
	system("cls");
	cout << "\t\tДЕЛЕНИЕ\n\n";
	Matrix A3(4, 4), B3(4, 4), C3 (4, 4);
	A3.FillRand();
	B3.FillRand();
	C3 = A3 / B3;

	cout << "  A\n";
	A3.PrintM();
	cout << "  B\n";
	B3.PrintM();
	cout << "A / B =\n";
	C3.PrintM();
 }