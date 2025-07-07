#include<ClassFraction.h>

class Matrix;
void Print(Fraction** arr, const int rows, const int cols);


class Matrix 
{
	int rows; //количество строк
	int cols; //количество столбцов
	Fraction** arr;

public:
	int get_rows() const
	{
		return rows;
	}
	int get_cols() const
	{
		return cols;
	}
	Fraction** get_arr() const
	{
		return arr;
	}
	//		constructors
	Matrix(int rows = 1, int cols = 1):rows(rows), cols(cols), arr(new Fraction* [this->rows] {})
		// default or measurements
	{
		for (int i = 0; i < rows; i++)
			this->arr[i] = new Fraction[cols] {};
		cout << "DefaultConstruction\t" << this << endl;
	}
	Matrix(Fraction** arr, const   int rows, const   int cols):Matrix(rows, cols) //:rows(rows), cols(cols), arr(new Fraction* [this->rows] {})
		//array and measurements
	{
		//for (int i = 0; i < rows; i++)
		//	this->arr[i] = new Fraction[cols] {};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->arr[i][j] = arr[i][j];
		cout << "array and measurements\t" << this << endl;
	}
	Matrix(const Matrix& other):Matrix(other.arr, other.rows, other.cols)   //:rows(other.rows), cols(other.cols), arr(new Fraction* [this->rows]{})
		//Matrix
	{
		//for (int i = 0; i < rows; i++)
		//	this->arr[i] = new Fraction[cols] {};
		//
		//for (int i = 0; i < rows; i++)
		//	for (int j = 0; j < cols; j++)
		//		this->arr[i][j] = other.arr[i][j];
		cout << "DeepCopy:\t\t" << this << endl; //Побитовое копирование
	}
	~Matrix()
	{
		for (int i = 0; i < rows; i++)
			delete[] arr[i];
		delete[] arr;
		this->rows = 0;
		this->cols = 0;
		cout << "Destructor\t\t" << this << endl;
	}

	//Operators
	
	Matrix& operator= (const Matrix& other)
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
		this->arr = new Fraction* [this->rows] {};
		for (int i = 0; i < rows; i++)
			this->arr[i] = new Fraction[this->cols] {};
	
		for (int i = 0; i < this->rows; i++)
			for (int j = 0; j < this->cols; j++)
				this->arr[i][j] = other.arr[i][j];
		cout << "CopyAssignment:\t\t" << this << endl; //Побитовое копирование
	}
	Matrix operator+ (const Matrix other)
	{
		if (this->rows != other.rows || this->cols != other.cols) //невозможно вычислить
		{
			Matrix result(1, 1);
			return result;
		}
		Matrix m3;
		m3.rows = this->rows;
		m3.cols = this->cols;
		m3.arr = new Fraction* [rows];
		for (int i = 0; i < rows; i++)
			m3.arr[i] = new Fraction[cols];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				m3.arr[i][j] = this->arr[i][j] + other.arr[i][j];
				m3.arr[i][j].to_proper();
				m3.arr[i][j].Reduce();
			}
		}
		cout << "operator+ \t\t" << &m3 << endl;
		return m3;
	}
	//Matrix& operator*(Fraction value)		//умножение на число
	//{
	//	for (int i = 0; i < rows; i++)
	//	{
	//		for (int j = 0; j < cols; j++)
	//		{
	//			arr[i][j] *= value;
	//			arr[i][j].to_proper();
	//			arr[i][j].Reduce();
	//		}
	//	}
	//	return *this;
	//}

	// Methods
	void FillRand(int minRand = 0, int maxRand = 10)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				arr[i][j].set_integer(rand() % (maxRand - minRand) + minRand);
				arr[i][j].set_numerator(rand() % (maxRand - minRand) + minRand);
				arr[i][j].set_denominator(rand() % (maxRand - minRand - 1) + minRand+1);
				//
				// здесь бы привести дробь в божеский вид
				arr[i][j].to_proper();
				arr[i][j].Reduce();

			}
		}
	}
	void PrintM() const			//с именем Print почему-то возникла путаница. Хотя количество аргументов разное, но метод пытался вызвать метод, а не функцию. Пришлось поменять имя метода
	{
		Print(this->arr, this->rows, this->cols);
	}
	Matrix& Inverse()
	{
		Fraction tmp_zero = 0;
		if (rows != cols)
		{
			for (int i = 0; i < this->rows; i++)
				delete[] arr[i];
			delete[] arr;
			rows = 1;
			cols = 1;
			arr = new Fraction* [rows] {};
			arr[0] = new Fraction[cols] {};
			return *this;
		}
		else
		{
			Fraction first_element = 0;
			int ind = 0;
			while (first_element==tmp_zero && ind < rows)
			{
				if (arr[ind][0]!=tmp_zero)
					first_element = arr[ind][0];
				ind++;
			}
			ind--;
			if (first_element==tmp_zero) //если весь первый столбец нулевой, обратной матрицы не существует
			{
				for (int i = 0; i < this->rows; i++)
					delete[] arr[i];
				delete[] arr;
				rows = 1;
				cols = 1;
				arr = new Fraction* [rows] {};
				arr[0] = new Fraction[cols] {};
				return *this;
			}
			else  //вот теперь ищем обратную матрицу
			{
				Matrix res(rows, cols);
				res.to_e();
	
				cout << "res to e\n";
				res.PrintM();
	
				for (int i = 0; i < rows; i++)						//ПРЯМОЙ ОБХОД
				{
					if (arr[i][i]==tmp_zero)  //если диагональный эл-т = 0, меняем строки местами
					{
						ind = 0;
						for (int k = i + 1; k < rows; k++)
						{
							if (arr[k][i]!=tmp_zero && !ind)
								ind = k;						//находим строку, где элемент ненулевой
						}
						this->ChangeLines(i, ind);
						res.ChangeLines(i, ind);
						cout << "this change lines\n";
						this->PrintM();
						cout << "res change lines\n";
						res.PrintM();
					}
	
					Fraction denominator = arr[i][i];			//приводим диагональный элемент к единице, преобразовывая всю строку
					denominator.to_proper();
					denominator.Reduce();
					this->DivideLine(i, denominator);
					res.DivideLine(i, denominator);
	
					cout << "DivideLine" << i << " / " << denominator << endl << "this" << endl;
					this->PrintM();
					cout << "res\n";
					res.PrintM();
	
					for (int j = i + 1; j < rows; j++)
					{
						if (i != j && arr[j][i]!=tmp_zero && arr[i][i]!=tmp_zero)
						{
							Fraction multiplier = arr[j][i] / arr[i][i];
							multiplier.to_proper();
							multiplier.Reduce();
							this->Subtraction(j, i, multiplier);
							res.Subtraction(j, i, multiplier);
							cout << "Subtruction line " << j << " " << i << " * " << multiplier << endl << "this\n";
							this->PrintM();
							cout << "res\n";
							res.PrintM();
						}
					}
				}  //получили: по диагонали единицы, под диагональю нули
	
				cout << "\nREVERSE\n";
				for (int i = rows - 1; i >= 0; i--)				//ОБРАТНЫЙ ОБХОД
				{
					for (int j = i - 1; j >= 0; j--)
					{
						Fraction multiplier = arr[j][i] / arr[i][i];
						multiplier.to_proper();
						multiplier.Reduce();
						this->Subtraction(j, i, multiplier);
						res.Subtraction(j, i, multiplier);
						cout << "Subtruction line " << j << " " << i << " * " << multiplier << endl << "this\n";
						this->PrintM();
						cout << "res\n";
						res.PrintM();
	
					}
				}
	
				//вывод результата
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						this->arr[i][j] = res.arr[i][j];
				return *this;
			}
		}
	}
	Matrix& to_e()	//Записывает единичную матрицу
	{
		Fraction one(1, 0, 1);
		Fraction zero(0, 0, 1);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				if (i == j)
					arr[i][j] = one;
				else
					arr[i][j] = zero;
			}
		return *this;
	}
	Matrix& ChangeLines(int first, int second)
	{
		Fraction buf = 0;
		for (int i = 0; i < cols; i++)
		{
			buf = arr[first][i];
			arr[first][i] = arr[second][i];
			arr[second][i] = buf;
		}
		return *this;
	}
	Matrix& MultiplyLine(int line_num, Fraction value)
	{
		for (int i = 0; i < cols; i++)
		{
			arr[line_num][i] *= value;
			arr[line_num][i].to_proper();
			arr[line_num][i].Reduce();
		}
		return *this;
	}
	Matrix& DivideLine(int line_num, Fraction value)
	{
		Fraction tmp_zero = 0;
		if (value!=tmp_zero)
		{
			Fraction tmp_one = 1;
			this->MultiplyLine(line_num, (tmp_one / value));
		}
		return *this;
	}
	Matrix& Subtraction(int minued, int subtrahend, Fraction value = 1)   // line minued - line subtrahend * value
	{
		for (int i = 0; i < cols; i++)
		{
			arr[minued][i] -= arr[subtrahend][i] * value;
			arr[minued][i].to_proper();
			arr[minued][i].Reduce();
		}
		return *this;
	}
};  // CLass Matrix



Matrix operator*(const Matrix M, const Fraction value)		//умножение на число
{
	Matrix res(M.get_rows(), M.get_cols());
	for (int i = 0; i < M.get_rows(); i++)
	{
		for (int j = 0; j < M.get_cols(); j++)
		{
			res.get_arr()[i][j] = M.get_arr()[i][j] * value;
			res.get_arr()[i][j].to_proper();
			res.get_arr()[i][j].Reduce();
		}
	}
	return res;
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
	for (int i = 0; i < c_rows; i++)
		for (int j = 0; j < c_cols; j++)
		{
			C.get_arr()[i][j].to_proper();
			C.get_arr()[i][j].Reduce();
		}
	return C;
}
//Matrix operator/(const Matrix left, const Matrix right) //деление матриц
//{
//	Matrix dub, result;
//	dub = right;
//	dub.Inverse();
//	result = left * dub;
//	return result;
//}
void Print(Fraction** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j].print();
			cout  << "\t";
		}
		cout << endl;
	}
}


void main()
{
	setlocale(LC_ALL, "");

	//1. Просто скопировать два класса			- ОК
	//Заменить в Matrix double  на Fraction		- OK
	// Создать матрицу							- OK
	// Заполнить матрицу						- OK
	// вывести на экран матрицу					- OK
	// Присвоить								- ОК
	// Сложить									- ОК
	// Умножить на число						- OK
	// перемножить 2 матрицы					- OK
	// найти обратную							- OK
	// пройти ТЕСТ с обратной					- OK!!!!!!!!!!!!!!!!!!
	// достаточно

	//Fraction F1(0, 0, 1);
	//F1.to_proper();
	//F1.Reduce();
	//F1.print();

	Matrix M1(4, 4);
	M1.FillRand();
	cout << "  M1\n";
	M1.PrintM();

	Matrix M2 = M1;
	cout << "  M2\n";
	M2.PrintM();

	Matrix M3;
	M3 = M1;
	cout << "  M3\n";
	M3.PrintM();

	M2.FillRand();
	M3 = M1 + M2;
	cout << "\n\nСЛОЖЕНИЕ\n  M1\n";
	M1.PrintM();
	cout << "  M2\n";
	M2.PrintM();
	cout << "  M1 + M2 =\n";
	M3.PrintM();

	Fraction value (1, 2);
	M3 = M1 * value;
	cout << "\n\nУМНОЖЕНИЕ НА ЧИСЛО\n  M1\n";
	M1.PrintM();
	cout << "  M1 * 1/2 =\n";
	M3.PrintM();

	Matrix N1(3, 4), N2(4, 5);
	Matrix N3;
	N1.FillRand();
	N2.FillRand();
	N3 = N1 * N2;
	cout << "\n\nУМНОЖЕНИЕ\n  M1\n";
	N1.PrintM();
	cout << "  M2\n";
	N2.PrintM();
	cout << "  M1 * M2 =\n";
	N3.PrintM();

	Matrix dub = M1;
	cout << "\n\nНАЙТИ ОБРАТНУЮ МАТРИЦУ\n  M1\n";
	dub.PrintM();
	dub.Inverse();
	cout << "--------обратная матрица---------\n";
	dub.PrintM();
	cout << "-------------------------\n";

	Matrix test;
	test = M1 * dub;
	cout << "---------ПРОВЕРКА--------\nM * обратнаяM = \n";
	test.PrintM();
	cout << "-------------------------\n";
}