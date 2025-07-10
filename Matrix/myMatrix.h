#pragma once
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
	int rows; //���������� �����
	int cols; //���������� �������� 
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
	Matrix(double** arr, const   int rows, const   int cols);
	Matrix(const Matrix& other);
	~Matrix();

	//Operators
	Matrix& operator= (const Matrix& other);
	Matrix operator+ (const Matrix other);
	Matrix& operator*(int value);		//��������� �� �����

	// Methods
	void FillRand(int minRand = 0, int maxRand = 10);
	void PrintM() const;			//� ������ Print ������-�� �������� ��������. ���� ���������� ���������� ������, �� ����� ������� ������� �����, � �� �������. �������� �������� ��� ������
	Matrix& Inverse();
	Matrix& to_e();	//���������� ��������� �������
	Matrix& ChangeLines(int first, int second);
	Matrix& MultiplyLine(int line_num, double value);
	Matrix& DivideLine(int line_num, double value);
	Matrix& Subtraction(int minued, int subtrahed, double value = 1);   // minued - subtrahed * value
};  // CLass Matrix