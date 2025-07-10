#include "myMatrix.h"


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

	//��������� �����������
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
	cout << "CopyAssignment:\t\t" << this << endl; //��������� �����������  
#endif // DEBUG

}
Matrix Matrix::operator+ (const Matrix other)
{
	if (this->rows != other.rows || this->cols != other.cols) //���������� ���������
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
Matrix& Matrix::operator*(int value)		//��������� �� �����
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
void Matrix::PrintM() const			//� ������ Print ������-�� �������� ��������. ���� ���������� ���������� ������, �� ����� ������� ������� �����, � �� �������. �������� �������� ��� ������
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
		if (!first_element) //���� ���� ������ ������� �������, �������� ������� �� ����������
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
		else  //��� ������ ���� �������� �������
		{
			Matrix res(rows, cols);
			res.to_e();

#ifdef DEBUG
			cout << "res to e\n";
			res.PrintM();
#endif // DEBUG


			for (int i = 0; i < rows; i++)						//������ �����
			{
				if (!arr[i][i])  //���� ������������ ��-� = 0, ������ ������ �������
				{
					ind = 0;
					for (int k = i + 1; k < rows; k++)
					{
						if (arr[k][i] && !ind)
							ind = k;						//������� ������, ��� ������� ���������
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

				double denominator = arr[i][i];			//�������� ������������ ������� � �������, �������������� ��� ������
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
			}  //��������: �� ��������� �������, ��� ���������� ����

#ifdef DEBUG
			cout << "\nREVERSE\n";
#endif // DEBUG

			for (int i = rows - 1; i >= 0; i--)				//�������� �����
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

			//����� ����������
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					this->arr[i][j] = res.arr[i][j];
			return *this;
		}
	}
} // end of inverse()
Matrix& Matrix::to_e()	//���������� ��������� �������
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

Matrix operator*(const Matrix left, const Matrix right) //��������� ���� ������
{

	if (left.get_cols() != right.get_rows()) // ���� �� ����������� ������� �� ����������� ��� ������������
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
Matrix operator/(const Matrix left, const Matrix right) //������� ������
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

