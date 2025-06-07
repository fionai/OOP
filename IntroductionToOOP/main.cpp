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
	/*Point()
	{
		x = y = 0;
		cout << "Default constructor " << this << endl;
	}
	Point(int x)
	{
		this->x = x;
		this->y = 0;
		cout << "Constructor:\t\t" << this << endl;
	}*/
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

	void print() const
	{
		cout << "X = " << get_x() << "\tY = " << get_y() << endl;
	}
	double distance(Point b)
	{
		return sqrt((this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y));
	}
};

double distance(Point A, Point B);

//#define STRUCT_POINT

void main()
{
#ifdef STRUCT_POINT


	setlocale(LC_ALL, "");
	Point A;	
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x;
#endif // STRUCT_POINT

	Point A;
	A.set_x(2);
	A.set_y(3);
	A.print();


	Point B (7, 8);
	B.print();
	
	//Point C(7, 8)	
	// //C.print()

	cout << A.distance(B) << endl;
	cout << distance(A, B);

}


double distance(Point A, Point B)
{
	return sqrt((A.get_x() - B.get_x()) * (A.get_x() - B.get_x()) + (A.get_y() - B.get_y()) * (A.get_y() - B.get_y()));
}