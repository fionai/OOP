#include <iostream>
using namespace std;

class Matrix;
void FillRand(double** arr, const int rows, const int cols);
void Print(double** arr, const int rows, const int cols);


class Matrix
{
	int rows; //количество строк
	int cols; //количество столбцов
	double** m;
	//bool err;
public:
	int get_rows() const
	{
		return rows;
	}
	int get_cols() const
	{
		return cols;
	}
	double** get_m() const
	{
		return m;
	}
	//		constructors
	Matrix(int rows = 1, int cols = 1)							// default or measurements
	{
		this->rows = rows;
		this->cols = cols;
		//err = 0;
		this->m = new double*[rows] {};
		for (int i = 0; i < rows; i++)
			this->m[i] = new double[cols] {};
		cout << "DefaultConstruction\t" << this << endl;
	}
	Matrix(double** arr, const   int rows, const   int cols)		//array and measurements
	{
		this->rows = rows;
		this->cols = cols;
		//this->err = 0;
		this->m = new double*[rows] {};
		for (int i = 0; i < rows; i++)
			this->m[i] = new double[cols] {};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->m[i][j] = arr[i][j];
		cout << "array and measurements\t" << this << endl;
	}
	Matrix(const Matrix& other)									//Matrix
	{
		this->rows = other.rows;
		this->cols = other.cols;
		//this->err = 0;
		this->m = new double*[rows] {};
		for (int i = 0; i < rows; i++)
			this->m[i] = new double[cols] {};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->m[i][j] = other.m[i][j];
		cout << "DeepCopy:\t\t" << this << endl; //Побитовое копирование
	}
	/*Matrix(const bool err)
	{
		this->rows = 1;
		this->cols = 1;
		this->err = err;
		this->m = new double*[this->rows]{};
		this->m[0] = new double[this->cols]{};
	}*/
	~Matrix()
	{
		for (int i = 0; i < rows; i++)
			delete[] m[i];
		delete[] m;
		this->rows = 0;
		this->cols = 0;
		cout << "Destructor\t\t" << this << endl;
	}
	//Operators
	Matrix& operator= (const Matrix& other)
	{
		if (this == &other)
			return *this;
		for (int i = 0; i < rows; i++)
			delete[] m[i];
		delete[] m;

		this->rows = other.rows;
		this->cols = other.cols;
		this->m = new double*[rows] {};
		for (int i = 0; i < rows; i++)
			this->m[i] = new double[cols] {};

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->m[i][j] = other.m[i][j];
		cout << "CopyAssignment:\t\t" << this << endl; //Побитовое копирование
	}
	/*Matrix& operator= (double ** arr,  int rows,  int cols)							//Почему так ругается?
	{
		for (int i = 0; i < rows; i++)
			delete[] m[i];
		delete[] m;

		this->rows = other.rows;
		this->cols = other.cols;
		this->m = new double*[rows] {};
		for (int i = 0; i < rows; i++)
			this->m[i] = new double[cols] {};

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->m[i][j] = arr[i][j];
		cout << "CopyAssignment:\t\t" << this << endl; //Побитовое копирование
	}*/
	Matrix& operator+ (const Matrix& other)
	{
		/*if (this->rows != other.rows || this->cols != other.cols)
		{
			bool error = 1;
			return Matrix(error);
		}*/
		Matrix m3(this->rows, this->cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				m3.m[i][j] = this->m[i][j] + other.m[i][j];
			}
		}
		return m3;
	}
	// Methods
	void PrintM() const			//с именем Print почему-то возникла путаница. Хотя количество аргументов разное, но метод пытался вызвать метод, а не функцию. Пришлось поменять имя метода
	{
		Print(this->m, this->rows, this->cols);
	}
};


void FillRand(double** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = double(rand() % 10000) / 100;
		}
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
	//Matrix m1{ {0, 1, 2}, {0, 1, 2}, {4, 5,6 }, {0, 1, 2} };            //так не получается. Буду пробовать через массивы
	int r1 = 3, c1 = 4; //измерения массива
	int r2 = 3, c2 = 4; //измерения массива
	double** arr1 = new double* [r1];											//arr1 create
	for (int i = 0; i < r1; i++)
	{
		arr1[i] = new double[c1];
	}
	double** arr2 = new double*[r2];											//arr2 create
	for (int i = 0; i < r2; i++)
	{
		arr2[i] = new double[c2];
	}
	
	FillRand(arr1, r1, c1);
//	Print(arr1, r1, c1);
	cout << endl;
	FillRand(arr2, r2, c2);
//	Print(arr2, r2, c2);


	Matrix m1 (arr1, r1, c1);
	m1.PrintM();

	Matrix m2 (arr2, r2, c2);
	m2.PrintM();

	Matrix m3;
	m3 = m1 + m2;			//пока без проверок размерностей. Не поняла, как использовать признак ошибки
	m3.PrintM();

	for (int i = 0; i < r1; i++)												//arr1 delete
		delete[] arr1[i];
	delete[] arr1;
	for (int i = 0; i < r2; i++)												//arr2 delete
		delete[] arr2[i];
	delete[] arr2;
}








