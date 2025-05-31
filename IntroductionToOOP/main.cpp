#pragma warning(disable:4326)
#include <iostream>

using namespace std;


class Point
{
	double x; 
	double y;
public:
	double get_x() const
	{
		return x;
	}
	double get_y() const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//Constructors

	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	//	cout << "Constructor:\t\t" << this << endl;
	}
	~Point()
	{
	//	cout << "Destructor " << this << endl;
	}


	//Methods

	double distance(Point B)
	{
		return sqrt ((this->x - B.x) * (this->x - B.x) + (this->y - B.y) * (this->y - B.y));
	}
};


double distance(Point A, Point B);

void main()
{
	setlocale(LC_ALL, "");

	Point A(1, 1);
	cout << "Координаты точки А:\tx = " << A.get_x() << ", y = " << A.get_y() << endl;

	Point B(4, 5);
	cout << "Координаты точки B:\tx = " << B.get_x() << ", y = " << B.get_y() << endl;

	double dist;
	dist = A.distance(B);	//Пункт 2. МЕТОД - расстояние до точки В 
	cout << "Расстояние между точками равно:\n";
	cout << "Результат вызова метода: " << dist << endl;
	dist = distance(A, B);	//Пункт 3. ФУНКЦИЯ - расстояние между точками
	cout << "Результат вызова функции: " << dist << endl;
}

double distance(Point A, Point B)
{
	return sqrt((A.get_x() - B.get_x()) * (A.get_x() - B.get_x()) + (A.get_y() - B.get_y()) * (A.get_y() - B.get_y()));
}