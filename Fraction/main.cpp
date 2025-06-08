#include <iostream>
using namespace std;

int GCD(const int a = 1, const int b = 1) //	Find a Gratest Common Divisor
{
	if (!a || !b)
		return 0;
	int big, small, buf;
	if (a > b)
	{
		big = a;
		small = b;
	}
	else if (b > a)
	{
		big = b;
		small = a;
	}
	else if (a == b)
	{
		return a;
	}
	while (big % small)
	{
		buf = big % small;
		big = small;
		small = buf;
	}
	return small;
}

class Fraction
{
	//int integer;
	int numerator;		//числитель
	int denominator;	//знаменатель. Он же - признак ошибки (если 0)
public:
	int get_numerator() const
	{
		return numerator;
	}
	int get_denominator() const
	{
		return denominator;
	}
	void set_numerator(int x)
	{
		this->numerator = x;
	}	
	void set_denominator(int x)
	{
		this->denominator = x;
	}
	
	//			Constructors
	Fraction (int n = 0, int d = 1) // по умолчанию
	{
		this->numerator = n;
		this->denominator = d;
	}
	Fraction(const Fraction& other)	//CopyConstruction
	{
		this->numerator = other.numerator;
		this->denominator = other.denominator;
	}
	//			Destructor
	~Fraction()
	{

	}

	//			Operators

	Fraction operator ++ ()		
	{

		this->numerator += this->denominator;
		int dd = GCD(this->numerator, this->denominator);									//	находим НОД
		if (dd)
		{
			this->numerator /= dd;								//	сокращаем дробь
			this->denominator /= dd;
		}
		else this->denominator = 0;
		this->Normal_Minus();
		return *this;
	}
	Fraction operator-- ()
	{ 
	
		this->numerator -= this->denominator;
		int dd = GCD(this->numerator, this->denominator);									//	находим НОД
		if (dd)
		{
			this->numerator /= dd;								//	сокращаем дробь
			this->denominator /= dd;
		}
		else this->denominator = 0;
		this->Normal_Minus();
		return *this;
	}
	Fraction operator- ()
	{
		Fraction res;
		res.numerator = -this->numerator;
		res.denominator = this->denominator;
		res.Normal_Minus();
		return res;
	}
	Fraction operator+= (Fraction& other) // this = this + other
	{ 
		//так как я не могу обратиться к уже прописанному (в функции) оператору, приходится писать весь код здесь
		int n, d;
		n = this->numerator * other.denominator + this->denominator * other.numerator;
		d = this->denominator * other.denominator;
		if (!d)
		{
			this->numerator = 0;
			this->denominator = 0;
			return *this;
		}
		this->numerator = n;
		this->denominator = d;
		int dd = GCD(this->numerator, this->denominator);									//	находим НОД
		if (dd)
		{
			this->numerator /= dd;								//	сокращаем дробь
			this->denominator /= dd;
		}
		else this->denominator = 0;
		this->Normal_Minus();
		return *this;
	}
	Fraction operator-= (Fraction& other) // this = this - other
	{ 
		//this += (-other);   // ПОЧЕМУ я не могу так вызвать? Есть же уже такой опреатор. Ругается на +=
		// так и не разобралась, поэтому полностью повторяю код ((
	
		int n, d;
		n = this->numerator * other.denominator - this->denominator * other.numerator;
		d = this->denominator * other.denominator;
		if (!d)
		{
			this->numerator = 0;
			this->denominator = 0;
			return *this;
		}
		this->numerator = n;
		this->denominator = d;
		int dd = GCD(this->numerator, this->denominator);									//	находим НОД
		if (dd)
		{
			this->numerator /= dd;								//	сокращаем дробь
			this->denominator /= dd;
		}
		else this->denominator = 0;
		this->Normal_Minus();
		return *this;
	}
	Fraction operator*= (Fraction& other)
	{	
		int n, d;
		n = this->numerator * other.numerator;
		d = this->denominator * other.denominator;
		if (!d)
		{
			this->numerator = 0;
			this->denominator = 0;
			return *this;
		}
		this->numerator = n;
		this->denominator = d;
		int dd = GCD(this->numerator, this->denominator);									//	находим НОД
		if (dd)
		{
			this->numerator /= dd;								//	сокращаем дробь
			this->denominator /= dd;
		}
		else this->denominator = 0;
		this->Normal_Minus();
		return *this;
	}
	Fraction operator/=(Fraction& other)
	{	
		int n, d;
		n = this->numerator * other.denominator;
		d = this->denominator * other.numerator;
		if (!d)
		{
			this->numerator = 0;
			this->denominator = 0;
			return *this;
		}
		this->numerator = n;
		this->denominator = d;
		int dd = GCD(this->numerator, this->denominator);									//	находим НОД
		if (dd)
		{
			this->numerator /= dd;								//	сокращаем дробь
			this->denominator /= dd;
		}
		else this->denominator = 0;
		this->Normal_Minus();
		return *this;
	}

	//			Methods
	void Print() const
	{
		if (!this->denominator)
			cout << "Ошибка: Деление на 0.";
		else
			cout << this->numerator << "/" << this->denominator;
	}
	Fraction Normal_Minus()				// нормализация минусов. Знаменатель всегда должен быть положительным
	{
		if (this->denominator < 0)
		{

			this->numerator = -this->numerator;
			this->denominator = -this->denominator;
		}
		return *this;
	}

	//int GCD() //	Find a Gratest Common Divisor
	//{
	//	if (!this->denominator || !this->numerator)
	//		return 0;
	//	int big, small, buf;
	//	if (this->denominator > this->numerator)
	//	{
	//		big = this->denominator;
	//		small = this->numerator;
	//	}
	//	else if (this->numerator > this->denominator)
	//	{
	//		big = this->numerator;
	//		small = this->denominator;
	//	}
	//	else if (this->numerator == this->denominator)
	//		return this->denominator;
	//	while (big % small)
	//	{
	//		buf = big % small;
	//		big = small;
	//		small = buf;
	//	}
	//	return small;
	//}

};		//class Fraction

void Normal_Minus(Fraction& x)				// нормализация минусов
{
	if (x.get_denominator() < 0)
	{
		x.set_numerator(-x.get_numerator());
		x.set_denominator(-x.get_denominator());
	}
}
Fraction operator+ (const Fraction& x, const Fraction& y)
{
	Fraction res;
	int n, d;
	if (!x.get_denominator() or !y.get_denominator())  //будет ошибка
	{
		res.set_numerator(0);
		res.set_denominator(0);
		return res;
	}
	n = x.get_numerator() * y.get_denominator() + y.get_numerator() * x.get_denominator();
	d = x.get_denominator() * y.get_denominator();
	int dd = GCD(n, d);
	if (dd)
	{
		n /= dd;
		d /= dd;
		res.set_numerator(n);
		res.set_denominator(d);
		Normal_Minus(res);
		return res;
	}
	else  //будет ошибка
	{
		res.set_numerator(0);
		res.set_denominator(0);
		return res;
	}
}
Fraction operator- (const Fraction x, Fraction y)   // с const 'y' нельзя почему-то
{
	Fraction res, minus_y;
	minus_y = -y;									// Хотя 'y' не должен меняться при вызове унарного -. И не меняется...
	res = x + minus_y;		
	return res;
}
Fraction operator* (const Fraction x, const Fraction y)
{
	Fraction res;
	if (!x.get_denominator() or !y.get_denominator())
	{
		res.set_numerator(0);
		res.set_denominator(0);
		return res;
	}
	res.set_numerator(x.get_numerator() * y.get_numerator());
	res.set_denominator(x.get_denominator() * y.get_denominator());
	int dd = GCD(res.get_numerator(), res.get_denominator());
	res.set_numerator(res.get_numerator() / dd);
	res.set_denominator(res.get_denominator() / dd);
	Normal_Minus(res);
	return res;
}
Fraction operator/ (const Fraction x, const Fraction y)
{ 
	Fraction anti_y, res;
	if (!x.get_denominator() or !y.get_numerator())
	{
		res.set_numerator(0);
		res.set_denominator(0);
		return res;
	}
	//  Переворачиваем вторую дробь:
	anti_y.set_numerator(y.get_denominator());   
	anti_y.set_denominator(y.get_numerator());

	//Теперь две дроби можно просто перемножить
	res = x * anti_y;

	int dd = GCD(res.get_numerator(), res.get_denominator());
	res.set_numerator(res.get_numerator() / dd);
	res.set_denominator(res.get_denominator() / dd);
	Normal_Minus(res);
	return res;
}
bool operator> (const Fraction x, const Fraction y)
{
	Fraction res;
	res = x - y;
	if (res.get_numerator() > 0)
		return true;
	else
		return false;
}
bool operator< (const Fraction x, const Fraction y)
{
	Fraction res;
	res = x - y;
	if (res.get_numerator() < 0)
		return true;
	else
		return false;
}
bool operator== (const Fraction x, const Fraction y)
{ 
	Fraction res;
	res = x - y;
	if (!res.get_numerator())
		return true;
	else
		return false;
}
bool operator!= (const Fraction x, const Fraction y)
{ 
	Fraction res;
	res = x - y;
	if (res.get_numerator())
		return true;
	else
		return false;
}

void main()
{
	setlocale(LC_ALL, "");

	Fraction cf1 (-7, -13),  cf2 (2, 5), cf3;			// CommonFraction
	cout << "Начальные значения дробных чисел:\n";
	cf1.Print();
	cout << "\t";
	cf2.Print();
	cout << endl;

	cf1 = cf2; // присвоить
	cout << "Результат присвоения в первую переменную значения второй переменной. Значения переменных теперь равны: ";
	cf1.Print();
	cout << " ";
	cf2.Print();
	cout << endl;

	cf1 = Fraction(2, 7);	// Плюс
	cf2 = Fraction(2, 10);
	cf3 = cf1 + cf2;
	cf1.Print();
	cout << " + ";
	cf2.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	cf3 = cf1 - cf2;		// Минус
	cf1.Print();
	cout << " - ";
	cf2.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	cf3 = cf1 * cf2;		// Умножить
	cf1.Print();
	cout << " * ";
	cf2.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	cf3 = cf1 / cf2;		// Поделить
	cf1.Print();
	cout << " / ";
	cf2.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	cf2 = Fraction(0, 2);  // Проверим ка деление на 0
	cf3 = cf1 / cf2;
	cf1.Print();
	cout << " / ";
	cf2.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	cf2 = Fraction(2, 10);  //вернем нормальное значение

	cout << "++(";			// префиксный инкремент. Постфиксный нельзя?
	cf1.Print();
	cout << ") = ";
	++cf1;
	cf1.Print();
	cout << endl;

	cout << "--(";			// префиксный декремент. Постфиксный нельзя?
	cf1.Print();
	cout << ") = ";
	--cf1;
	cf1.Print();
	cout << endl;

	cf3 = -cf1;				// Унарный минус
	cout << "-(";
	cf1.Print();
	cout << ") = ";
	cf3.Print();
	cout << endl;

	cf3 = cf2;				// +=
	cf3.Print();
	cf3 += cf1;
	cout << " += ";
	cf1.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	cf3 = cf2;				// -=
	cf3.Print();
	cf3 -= cf1;
	cout << " -= ";
	cf1.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	cf3 = cf2;				// *=
	cf3.Print();
	cf3 *= cf1;
	cout << " *= ";
	cf1.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	cf3 = cf2;				// /=
	cf3.Print();
	cf3 /= cf1;
	cout << " /= ";
	cf1.Print();
	cout << " = ";
	cf3.Print();
	cout << endl;

	bool bool_res;
	bool_res = cf1 > cf2;	// Больше 
	cf1.Print();
	cout << " > ";
	cf2.Print();
	cout << "\t Результат сравнения есть: ";
	if (bool_res)
		cout << "true\n";
	else
		cout << "false\n";

	cf3 = cf2;
	bool_res = cf3 > cf2;	// Больше  (при равенстве)
	cf3.Print();
	cout << " > ";
	cf2.Print();
	cout << "\t Результат сравнения есть: ";
	if (bool_res)
		cout << "true\n";
	else
		cout << "false\n";

	bool_res = cf1 < cf2;	// Меньше 
	cf1.Print();
	cout << " < ";
	cf2.Print();
	cout << "\t Результат сравнения есть: ";
	if (bool_res)
		cout << "true\n";
	else
		cout << "false\n";


	bool_res = cf3 < cf2;	// Меньше  (при равенстве)
	cf3.Print();
	cout << " < ";
	cf2.Print();
	cout << "\t Результат сравнения есть: ";
	if (bool_res)
		cout << "true\n";
	else
		cout << "false\n";

	bool_res = cf1 == cf2;	//  Равно
	cf1.Print();
	cout << " == ";
	cf2.Print();
	cout << "\t Результат сравнения есть: ";
	if (bool_res)
		cout << "true\n";
	else
		cout << "false\n";

	bool_res = cf3 == cf2;	//  Равно (при равенстве)
	cf3.Print();
	cout << " == ";
	cf2.Print();
	cout << "\t Результат сравнения есть: ";
	if (bool_res)
		cout << "true\n";
	else
		cout << "false\n";

	bool_res = cf1 != cf2;	// Не равно
	cf1.Print();
	cout << " != ";
	cf2.Print();
	cout << "\t Результат сравнения есть: ";
	if (bool_res)
		cout << "true\n";
	else
		cout << "false\n";

	bool_res = cf3 != cf2;	// Не равно (при равенстве)
	cf3.Print();
	cout << " != ";
	cf2.Print();
	cout << "\t Результат сравнения есть: ";
	if (bool_res)
		cout << "true\n";
	else
		cout << "false\n";
}