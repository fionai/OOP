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
		/*double x1 = B.x;
		double y1 = B.y;
		double x2 = this->x;*/
		return sqrt ((this->x - B.x) * (this->x - B.x) + (this->y - B.y) * (this->y - B.y));
	}
};

//#define STRUCT_POINT

void main()
{
	setlocale(LC_ALL, "");
#ifdef STRUCT_POINT


	Point A;	
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x;
#endif // STRUCT_POINT

	Point A(1, 1);
//	A.print();
	cout << "Координаты точки А:\tx = " << A.get_x() << ", y = " << A.get_y() << endl;

	Point B(4, 5);
	cout << "Координаты точки B:\tx = " << B.get_x() << ", y = " << B.get_y() << endl;
//	C.print();

	double dist;
	dist = A.distance(B);	//Как-то так.
							//за какой пункт это считать? За второй или 3, я не поняла. Это расстояние ДО точки или МЕЖДУ точками... 
	cout << "Расстояние между точками равно: " << dist << endl;
}