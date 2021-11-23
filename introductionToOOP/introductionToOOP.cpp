#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Fraction;
Fraction operator*(Fraction left, Fraction right);

class Fraction
{
	int integer;
	int numerator;
	int denominator;

public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
	}


	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:" << this << endl;
	}

	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:" << this << endl;
	}

	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:" << this << endl;
	}

	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}

	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}

	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}



	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}

	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this * other.inverted();
	}

	Fraction operator+=(Fraction right)
	{
		to_improper();
		right.to_improper();
		this->numerator = (get_numerator() * right.get_denominator()) + (right.get_numerator() * get_denominator());
		this->denominator = get_denominator() * right.get_denominator();
		to_proper();
		return *this;
	}

	Fraction operator-=(Fraction right)
	{
		to_improper();
		right.to_improper();
		this->numerator = (get_numerator() * right.get_denominator()) - (right.get_numerator() * get_denominator());
		this->denominator = get_denominator() * right.get_denominator();
		to_proper();
		return *this;
	}



	Fraction& operator++()
	{
		integer++;
		return *this;
	}

	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}

	Fraction& operator--()
	{
		integer--;
		return *this;
	}

	Fraction operator--(int)
	{
		Fraction old = *this;
		integer--;
		return old;
	}



	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}

	Fraction& to_proper()
	{
		integer = numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		int buffer = inverted.numerator;
		inverted.numerator = inverted.denominator;
		inverted.denominator = buffer;
		return inverted;
	}

	Fraction& reduction()
	{
		int nod;
		for (int i = 1; i <= numerator; i++)
		{
			if (numerator % i == 0 && denominator % i == 0)
			{
				nod = i;
			}
		}

		this->numerator = numerator / nod;
		this->denominator = denominator / nod;
		if (denominator == 1)
		{
			integer += numerator;
			numerator = 0;
			denominator = 0;
		}
		return *this;
	}

	void print()const
	{
		if (integer) cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}
};


Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}

Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}

bool operator==(Fraction left, Fraction right)
{
	if (left.get_integer()) left.to_improper();
	if (right.get_integer()) right.to_improper();

	bool comparison_result = false;
	if ((left.get_numerator() == right.get_numerator()) && (left.get_denominator() == right.get_denominator())) comparison_result = true;
	return comparison_result;
}

bool operator!=(Fraction left, Fraction right)
{
	if (left.get_integer()) left.to_improper();
	if (right.get_integer()) right.to_improper();

	bool comparison_result = false;
	if ((left.get_numerator() != right.get_numerator()) || (left.get_denominator() != right.get_denominator())) comparison_result = true;
	return comparison_result;
}

bool operator>(Fraction left, Fraction right)
{
	left.reduction();
	right.reduction();

	left.to_improper();
	right.to_improper();

	left.set_numerator(left.get_numerator() * right.get_denominator());
	right.set_numerator(left.get_denominator() * right.get_numerator());

	bool comparison_result = false;
	if (left.get_numerator() > right.get_numerator()) comparison_result = true;

	return comparison_result;
}

bool operator<(Fraction left, Fraction right)
{
	left.reduction();
	right.reduction();

	left.to_improper();
	right.to_improper();

	left.set_numerator(left.get_numerator() * right.get_denominator());
	right.set_numerator(left.get_denominator() * right.get_numerator());

	bool comparison_result = false;
	if (left.get_numerator() < right.get_numerator()) comparison_result = true;

	return comparison_result;
}

Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		(left.get_numerator() * right.get_denominator()) + (right.get_numerator() * left.get_denominator()),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}

Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		(left.get_numerator() * right.get_denominator()) - (right.get_numerator() * left.get_denominator()),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer()) os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer()) os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer()) os << ")";
	}
	else if (obj.get_integer() == 0) os << 0;
	return os;
}

istream& operator>>(istream& is, Fraction& obj)
{
	

	const int SIZE = 80; 
	char buffer[SIZE] = {};
	is.getline(buffer, SIZE);
	char delimiters[] = "() /"; 
	char* number[5];	
	int n = 0; 
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		number[n++] = pch;
	}
	switch (n)
	{
	case 1: obj.set_integer(atoi(number[0])); break;
	case 2:
		obj.set_numerator(atoi(number[0]));
		obj.set_denominator(atoi(number[1]));
		break;
	case 3:
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
	}
	return is;
}


void main()
{
	setlocale(LC_ALL, "");

	double a = 2;
	double b = 3;
	double c = a * b;
	c++;

	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);

	A = B++;
	A.print();
	A = ++B;
	A.print();

	A = B--;
	A.print();
	A = --B;
	A.print();

	A *= B;
	A.print();

	A /= B;
	A.print();

	A.print();
	B.print();

	cout << A << endl;
	cout << B << endl;


}


	
