#include <iostream>
#include<conio.h>

using namespace std;
//#define DEBUG

class Matrix;
void FillRand(double** arr, const int rows, const int cols);
void Print(double** arr, const int rows, const int cols);
Matrix operator*(const Matrix left, const Matrix right);
Matrix operator/(const Matrix left, const Matrix right);
void Print(double** arr, const int rows, const int cols);

class Matrix
{
	int rows; //количество строк
	int cols; //количество столбцов 
	double** arr;

public:
	int get_rows() const
	{
		return rows;
	}
	int get_cols() const
	{
		return cols;
	}
	double** get_arr() const
	{
		return arr;
	}
	//		constructors
	Matrix(int rows = 1, int cols = 1);
	Matrix(double** arr, const   int rows, const   int cols) ;
	Matrix(const Matrix& other) ;
	~Matrix();

	//Operators
	Matrix& operator= (const Matrix& other);
	Matrix operator+ (const Matrix other);
	Matrix& operator*(int value);		//умножение на число

	// Methods
	void FillRand(int minRand = 0, int maxRand = 10);
	void PrintM() const;			//с именем Print почему-то возникла путаница. Хотя количество аргументов разное, но метод пытался вызвать метод, а не функцию. Пришлось поменять имя метода
	Matrix& Inverse();
	Matrix& to_e();	//Записывает единичную матрицу
	Matrix& ChangeLines(int first, int second);
	Matrix& MultiplyLine(int line_num, double value);
	Matrix& DivideLine(int line_num, double value);
	Matrix& Subtraction(int minued, int subtrahed, double value = 1);   // minued - subtrahed * value
};  // CLass Matrix

Matrix::Matrix(int rows, int cols) :rows(rows), cols(cols), arr(new double* [this->rows] {})
// default or measurements
{
	for (int i = 0; i < rows; i++)
		this->arr[i] = new double[cols] {};
#ifdef DEBUG
	cout << "DefaultConstruction\t" << this << endl;
#endif // DEBUG

}
Matrix::Matrix(double** arr, const   int rows, const   int cols) :Matrix(rows, cols)
//array and measurements
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			this->arr[i][j] = arr[i][j];
#ifdef DEBUG
	cout << "array and measurements\t" << this << endl;
#endif // DEBUG

}
Matrix::Matrix(const Matrix& other) :Matrix(other.arr, other.rows, other.cols)
//Matrix
{
#ifdef DEBUG
	cout << "DeepCopy:\t\t" << this << endl;
#endif // DEBUG

	//Побитовое копирование
}
Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] arr[i];
	delete[] arr;
	this->rows = 0;
	this->cols = 0;
#ifdef DEBUG
	cout << "Destructor\t\t" << this << endl;
#endif // DEBUG

}
//Operators
Matrix& Matrix::operator= (const Matrix& other)
{
	if (this == &other)
		return *this;
	////////////////////////////////////////////////////////////
	for (int i = 0; i < rows; i++)
		delete[] this->arr[i];
	delete[] this->arr;
	////////////////////////////////////////////////////////////

	this->rows = other.rows;
	this->cols = other.cols;

	this->arr = new double* [this->rows] {};
	for (int i = 0; i < rows; i++)
		this->arr[i] = new double[this->cols] {};

	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->arr[i][j] = other.arr[i][j];
#ifdef DEBUG
	cout << "CopyAssignment:\t\t" << this << endl; //Побитовое копирование  
#endif // DEBUG

}
Matrix Matrix::operator+ (const Matrix other)
{
	if (this->rows != other.rows || this->cols != other.cols) //невозможно вычислить
	{
		Matrix result(1, 1);
		return result;
	}
	Matrix m3;
	m3.rows = this->rows;
	m3.cols = this->cols;
	m3.arr = new double* [rows];
	for (int i = 0; i < rows; i++)
		m3.arr[i] = new double[cols];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m3.arr[i][j] = this->arr[i][j] + other.arr[i][j];
		}
	}
#ifdef DEBUG
	cout << "operator+ \t\t" << &m3 << endl;
#endif // DEBUG

	return m3;
}
Matrix& Matrix::operator*(int value)		//умножение на число
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			this->arr[i][j] *= value;
		}
	}
	return *this;
}
// Methods
void Matrix::FillRand(int minRand, int maxRand)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % (maxRand - minRand) + minRand;
		}
	}
}
void Matrix::PrintM() const			//с именем Print почему-то возникла путаница. Хотя количество аргументов разное, но метод пытался вызвать метод, а не функцию. Пришлось поменять имя метода
{
	Print(this->arr, this->rows, this->cols);
}
Matrix& Matrix::Inverse()
{
	if (rows != cols)
	{
		for (int i = 0; i < this->rows; i++)
			delete[] arr[i];
		delete[] arr;
		rows = 1;
		cols = 1;
		arr = new double* [rows] {};
		arr[0] = new double[cols] {};
		return *this;
	}
	else
	{
		double first_element = 0;
		int ind = 0;
		while (!first_element && ind < rows)
		{
			if (arr[ind][0])
				first_element = arr[ind][0];
			ind++;
		}
		ind--;
		if (!first_element) //если весь первый столбец нулевой, обратной матрицы не существует
		{
			for (int i = 0; i < this->rows; i++)
				delete[] arr[i];
			delete[] arr;
			rows = 1;
			cols = 1;
			arr = new double* [rows] {};
			arr[0] = new double[cols] {};
			return *this;
		}
		else  //вот теперь ищем обратную матрицу
		{
			Matrix res(rows, cols);
			res.to_e();

#ifdef DEBUG
			cout << "res to e\n";
			res.PrintM();
#endif // DEBUG


			for (int i = 0; i < rows; i++)						//ПРЯМОЙ ОБХОД
			{
				if (!arr[i][i])  //если диагональный эл-т = 0, меняем строки местами
				{
					ind = 0;
					for (int k = i + 1; k < rows; k++)
					{
						if (arr[k][i] && !ind)
							ind = k;						//находим строку, где элемент ненулевой
					}
					this->ChangeLines(i, ind);
					res.ChangeLines(i, ind);
#ifdef DEBUG
					cout << "this change lines\n";
					this->PrintM();
					cout << "res change lines\n";
					res.PrintM();
#endif // DEBUG

				}

				double denominator = arr[i][i];			//приводим диагональный элемент к единице, преобразовывая всю строку
				this->DivideLine(i, denominator);
				res.DivideLine(i, denominator);

#ifdef DEBUG
				cout << "DivideLine" << i << " / " << denominator << endl << "this" << endl;
				this->PrintM();
				cout << "res\n";
				res.PrintM();
#endif // DEBUG


				for (int j = i + 1; j < rows; j++)
				{
					if (i != j && arr[j][i] && arr[i][i])
					{
						double multiplier = arr[j][i] / arr[i][i];
						this->Subtraction(j, i, multiplier);
						res.Subtraction(j, i, multiplier);
#ifdef DEBUG
						cout << "Subtruction line " << j << " " << i << " * " << multiplier << endl << "this\n";
						this->PrintM();
						cout << "res\n";
						res.PrintM();
#endif // DEBUG

					}
				}
			}  //получили: по диагонали единицы, под диагональю нули

#ifdef DEBUG
			cout << "\nREVERSE\n";
#endif // DEBUG

			for (int i = rows - 1; i >= 0; i--)				//ОБРАТНЫЙ ОБХОД
			{
				for (int j = i - 1; j >= 0; j--)
				{
					double multiplier = arr[j][i] / arr[i][i];
					this->Subtraction(j, i, multiplier);
					res.Subtraction(j, i, multiplier);
#ifdef DEBUG
					cout << "Subtruction line " << j << " " << i << " * " << multiplier << endl << "this\n";
					this->PrintM();
					cout << "res\n";
					res.PrintM();
#endif // DEBUG


				}
			}

			//вывод результата
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					this->arr[i][j] = res.arr[i][j];
			return *this;
		}
	}
} // end of inverse()
Matrix& Matrix::to_e()	//Записывает единичную матрицу
{
	int buf = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (i == j)
				arr[i][j] = 1;
			else
				arr[i][j] = 0;
		}
	return *this;
}
Matrix& Matrix::ChangeLines(int first, int second)
{
	double buf = 0;
	for (int i = 0; i < cols; i++)
	{
		buf = arr[first][i];
		arr[first][i] = arr[second][i];
		arr[second][i] = buf;
	}
	return *this;
}
Matrix& Matrix::MultiplyLine(int line_num, double value)
{
	for (int i = 0; i < cols; i++)
		arr[line_num][i] *= value;
	return *this;
}
Matrix& Matrix::DivideLine(int line_num, double value)
{
	if (value)
		this->MultiplyLine(line_num, 1 / value);
	return *this;
}
Matrix& Matrix::Subtraction(int minued, int subtrahed, double value)   // minued - subtrahed * value
{
	for (int i = 0; i < cols; i++)
	{
		arr[minued][i] -= arr[subtrahed][i] * value;
	}
	return *this;
}

Matrix operator*(const Matrix left, const Matrix right) //умножение двух матриц
{

	if (left.get_cols() != right.get_rows()) // Если не соблюдаются условия по размерности для перемножения
	{
		Matrix C;
		return C;
	}

	int c_rows = left.get_rows(), c_cols = right.get_cols();
	Matrix C(c_rows, c_cols);


	for (int i = 0; i < c_rows; i++)
		for (int j = 0; j < c_cols; j++)
		{
			C.get_arr()[i][j] = 0;
			for (int r = 0; r < right.get_rows(); r++)
				C.get_arr()[i][j] += left.get_arr()[i][r] * right.get_arr()[r][j];
		}

	return C;
}
Matrix operator/(const Matrix left, const Matrix right) //деление матриц
{
	Matrix dub, result;
	dub = right;
	dub.Inverse();
	result = left * dub;
	return result;
}
void Print(double** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}


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