#pragma warning(disable:4326)
#include <iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

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
		cout << "Constructor:\t\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}
	//Point(const Point& other) = delete;
	~Point()
	{
		cout << "Destructor " << this << endl;
	}

	//			Operators
	void operator=(const Point& other)
	{
		this->x = other.y;
		this->y = other.y;
		cout << "CopyAssignment:\t\t" << this << endl;
	}


	//			Methods

	void print() const
	{
		cout << "X = " << get_x() << "\tY = " << get_y() << endl;
	}
	double distance(const Point& b) const
	{
		return sqrt((this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y));
	}
};

double distance(const Point& A, const Point& B);


//#define STRUCT_POINT
//#define OBJECT_LIFETIME
#define DISTANCE_CHECK
//#define CONSTRUCTOR_CHECK
//#define ASSIGNMENT_CHECK

#define delimiter "\n---------------------------------------------------------------------------------------"

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

#ifdef OBJECT_LIFETIME

#endif // OBJECT_LIFETIME


#ifdef DISTANCE_CHECK

	Point A;
	A.set_x(2);
	A.set_y(3);
	A.print();


	Point B(7, 8);
	B.print();

	cout << delimiter << endl;
	cout << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << distance(B, A) << endl;


#endif // DISTANCE_CHECK
		
#ifdef CONSTRUCTOR_CHECK
	Point A(2, 3);
	A.print();
	Point B(1, 1);
	B.print();
	Point C(7, 8);
	C.print();

	Point D = C;
	D.print();

	Point E;
	E = D;
	E.print();

#endif // CONSTRUCTOR_CHECK

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	Point A, B, C;
	A = B = C = Point(2, 3);
	A.print();
	B.print();
	C.print();

#endif // ASSIGNMENT_CHECK


}


double distance(const Point& A, const Point& B)
{
	return sqrt((A.get_x() - B.get_x()) * (A.get_x() - B.get_x()) + (A.get_y() - B.get_y()) * (A.get_y() - B.get_y()));
}