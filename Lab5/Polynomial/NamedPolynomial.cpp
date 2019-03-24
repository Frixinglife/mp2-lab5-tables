#include "Polynomials.h"

NamedPolynom::NamedPolynom(const string &s): Polynom()
{
	name = s;
}

NamedPolynom::NamedPolynom(const NamedPolynom &p) : Polynom(p)
{
	name = p.name;
}

NamedPolynom::NamedPolynom(const vector <pair<double, int>> &p, const string &s) : Polynom(p)
{
	name = s;
}

NamedPolynom& NamedPolynom::operator=(const NamedPolynom &p)
{
	Polynom::operator=(p);
	name = p.name;
	return *this;
}

string NamedPolynom::getname()
{
	return name;
}

void NamedPolynom::rename(const string &s)
{
	name = s;
}

ostream& operator << (std::ostream& os, const NamedPolynom& object)
{
	if (object.isEmpty())
	{
		os << 0;
		return os;
	}
	os << object.name << ": ";
	Monom *temp = object.f_head->next;
	while (temp != NULL)
	{
		int x, y, z;
		x = temp->exp / 100;
		y = temp->exp / 10 % 10;
		z = temp->exp % 10;
		if (temp->coef > 0)
		{
			os << temp->coef << " ";
		}
		else
		{
			os << "(" << temp->coef << ") ";
		}
		if (x != 0)
		{
			os << "* x^" << x << " ";
		}
		if (y != 0)
		{
			os << "* y^" << y << " ";
		}
		if (z != 0)
		{
			os << "* z^" << z << " ";
		}
		if (temp->next != NULL)
		{
			os << "+ ";
		}
		temp = temp->next;
	}
	return os;
}

istream& operator >> (std::istream& is, NamedPolynom& object)
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите название полинома: ";
	cin >> object.name;
	cout << endl;
	cout << "Введите количество мономов: ";
	int k;
	is >> k;
	cout << endl;
	vector<pair<double, int>> v;
	v.reserve(k);
	for (int i = 0; i < k; i++)
	{
		pair<double, int> temp;
		double coef;
		int x, y, z;
		cout << "Моном " << i + 1 << "." << endl;
		cout << "Введите коэффициент: ";
		is >> coef;
		temp.first = coef;
		cout << "Введите степень х: ";
		is >> x;
		if (x < 0 || x > 9)
		{
			throw (string)"Некорректная степень х";
		}
		cout << "Введите степень y: ";
		is >> y;
		if (y < 0 || y > 9)
		{
			throw (string)"Некорректная степень y";
		}
		cout << "Введите степень z: ";
		is >> z;
		if (z < 0 || z > 9)
		{
			throw (string)"Некорректная степень z";
		}
		temp.second = x * 100 + y * 10 + z;
		cout << endl;
		if (!(abs(coef) < EPS))
		{
			v.push_back(temp);
		}
	}
	object.clear();
	for (auto it : v)
	{
		object.ins(it.first, it.second);
	}
	return is;
}

