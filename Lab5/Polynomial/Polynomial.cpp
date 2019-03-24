#include "Polynomials.h"

Polynom::Polynom()
{
	Monom *temp = new Monom;
	temp->prev = NULL;
	temp->next = NULL;
	temp->exp = -1;
	temp->coef = 0.0;
	f_head = temp;
}

Polynom::Polynom(const Polynom &p): Polynom()
{
	Monom *temp = p.f_head->next;
	while (temp != NULL)
	{
		ins_last(temp->coef, temp->exp);
		temp = temp->next;
	}
}

Polynom::Polynom(const vector<pair<double, int>> &p): Polynom()
{
	for (auto it : p)
	{
		ins(it.first, it.second);
	}
}

Polynom& Polynom::operator=(const Polynom &p)
{
	if (f_head != p.f_head)
	{
		clear();
		Monom *temp = p.f_head->next;
		while (temp != NULL)
		{
			ins_last(temp->coef, temp->exp);
			temp = temp->next;
		}
	}
	return *this;
}

bool Polynom::operator==(const Polynom &p) const
{
	Monom *a = f_head->next, *b = p.f_head->next;
	while (a != NULL && b != NULL)
	{
		if ((a == NULL && b != NULL) && (b == NULL && a != NULL))
		{
			return false;
		}
		else if ((a->exp != b->exp) || (!(abs(a->coef - b->coef) < EPS)))
		{
			return false;
		}
		a = a->next;
		b = b->next;
	}
	return true;
}

bool Polynom::operator!=(const Polynom &p) const
{
	return !(*this == p);
}

bool Polynom::isEmpty() const
{
	return f_head->next == NULL;
}

Polynom::~Polynom()
{
	clear();
	delete f_head;
}

void Polynom::ins_last(double coef, int exp)
{
	if (abs(coef) < EPS)
	{
		return;
	}
	if (exp < 0 || exp > 999)
	{
		throw (string)"Incorrect exponent";
	}
	Monom *temp = f_head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	Monom *a = new Monom;
	a->coef = coef;
	a->exp = exp;
	a->next = NULL;
	a->prev = temp;
	temp->next = a;
}

Monom* Polynom::find_mon(double coef, int exp) const
{
	if (abs(coef) < EPS || exp < 0 || exp > 999)
	{
		return NULL;
	}
	Monom *temp = f_head->next;
	while (temp != NULL)
	{
		if ((temp->exp == exp) && (abs(coef - temp->coef) < EPS))
		{
			return temp;
		}
		else
		{
			temp = temp->next;
		}
	}
	return NULL;
}

bool Polynom::find(double coef, int exp) const
{
	return !(find_mon(coef, exp) == NULL);
}

void Polynom::ins(double coef, int exp)
{
	if (abs(coef) < EPS)
	{
		return;
	}
	if (exp < 0 || exp > 999)
	{
		throw (string)"Incorrect exponent";
	}
	if (f_head->next == NULL)
	{
		Monom *temp = new Monom;
		temp->prev = f_head;
		temp->next = NULL;
		temp->coef = coef;
		temp->exp = exp;
		f_head->next = temp;
	}
	else
	{
		Monom *temp = f_head;
		while ((temp->next != NULL) && (temp->next->exp > exp))
		{
			temp = temp->next;
		}
		if (temp->next == NULL)
		{
			Monom *a = new Monom;
			a->next = NULL;
			a->coef = coef;
			a->exp = exp;
			a->prev = temp;
			temp->next = a;
		}
		else if (temp->next->exp == exp)
		{
			double c = temp->next->coef + coef;
			if (abs(c) < EPS)
			{
				del(temp->next->coef, temp->next->exp);
			}
			else
			{
				temp->next->coef = c;
			}
		}
		else
		{
			Monom *a = new Monom;
			a->prev = temp;
			a->next = temp->next;
			a->coef = coef;
			a->exp = exp;
			temp->next->prev = a;
			temp->next = a;
		}
	}
}

void Polynom::del(double coef, int exp)
{
	Monom* temp = find_mon(coef, exp);
	if (temp != NULL)
	{
		if (temp->next != NULL)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
		else
		{
			Monom* a = temp;
			temp->prev->next = NULL;
		}
		delete temp;
	}
}

void Polynom::clear()
{
	if (f_head->next == NULL)
	{
		return;
	}
	Monom *temp = f_head->next;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	while (temp != f_head)
	{
		Monom *a = temp;
		temp = temp->prev;
		delete a;
	}
	f_head->next = NULL;
}

Polynom Polynom::operator*(double val) const
{
	Polynom a;
	if (!(abs(val) < EPS))
	{
		a = *this;
		Monom *temp = a.f_head->next;
		while (temp != NULL)
		{
			temp->coef = temp->coef * val;
			temp = temp->next;
		}
	}
	return a;
}

void Polynom::simplification(Polynom &p) const
{
	Monom *f = p.f_head->next;
	while (f != NULL && f->next != NULL)
	{
		if (f->exp == f->next->exp)
		{
			double c = f->coef + f->next->coef;
			if (abs(c) < EPS)
			{
				Monom *t = f->next->next;
				p.del(f->next->coef, f->next->exp);
				p.del(f->coef, f->exp);
				f = t;
			}
			else
			{
				f->coef = c;
				p.del(f->next->coef, f->next->exp);
				f = f->next;
			}
		}
		else
		{
			f = f->next;
		}
	}
}

Polynom Polynom::operator+(const Polynom &p) const
{
	Polynom a;
	Monom *f = f_head->next, *s = p.f_head->next;
	while (true)
	{
		if (f == NULL && s != NULL)
		{
			while (s != NULL)
			{
				a.ins_last(s->coef, s->exp);
				s = s->next;
			}
			break;
		}
		else if (f != NULL && s == NULL)
		{
			while (f != NULL)
			{
				a.ins_last(f->coef, f->exp);
				f = f->next;
			}
			break;
		}
		else
		{
			if (f->exp >= s->exp)
			{
				a.ins_last(f->coef, f->exp);
				f = f->next;
			}
			else
			{
				a.ins_last(s->coef, s->exp);
				s = s->next;
			}
		}
	}
	simplification(a);
	return a;
}

Polynom Polynom::operator-(const Polynom &p) const
{
	return *this + p * (-1.0);
}

Polynom Polynom::operator*(const Polynom &p) const
{
	Polynom a;
	Monom *f = f_head->next, *s = p.f_head->next;
	while (f != NULL)
	{
		s = p.f_head->next;
		while (s != NULL)
		{
			int x, y, z;

			x = s->exp / 100 + f->exp / 100;
			y = s->exp / 10 % 10 + f->exp / 10 % 10;
			z = s->exp % 10 + f->exp % 10;

			if ((x > 9) || (y > 9) || (z > 9))
			{
				throw (string)"Overflow";
			}

			double coef = s->coef * f->coef;
			int exp = x * 100 + y * 10 + z;
			a.ins(coef, exp);

			s = s->next;
		}
		f = f->next;
	}
	simplification(a);
	return a;
}

ostream& operator << (ostream& os, const Polynom& object)
{
	if (object.isEmpty())
	{
		os << 0;
		return os;
	}
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

istream& operator >> (istream& is, Polynom& object)
{
	setlocale(LC_ALL, "Russian");
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