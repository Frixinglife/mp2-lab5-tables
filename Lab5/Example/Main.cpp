#include "Polynomials.h"
#include "UnorderedTable.h"
#include "OrderedTable.h"
#include "HashTable.h"

int main()
{
	HTable <NamedPolynom> a;
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	NamedPolynom b(v, "B");	
	a.ins(b.getname(), b);
	NamedPolynom *t = a.find("A");
	if (t)
	{
		cout << *t;
	}


	/*setlocale(LC_ALL, "Russian");
	cout << "+----------------------------------------------------------------+" << endl;
	cout << "|                     Правила ввода данных                       |" << endl;
	cout << "+----------------------------------------------------------------+" << endl;
	cout << "| 1) Полином составлен из мономов от трех переменных.            |" << endl;
	cout << "| 2) Коэффициенты монома - вещественные числа.                   |" << endl;
	cout << "| 3) Степени (x, y, z) монома  - неотрицательные, не превышают 9.|" << endl;
	cout << "+----------------------------------------------------------------+" << endl;
	cout << endl;
retry1:
	cout << "Введите 2 полинома." << endl << endl;
	Polynom a, b;
	try
	{
		cout << "Первый полином: " << endl;
		cin >> a;
		cout << "Второй полином: " << endl;
		cin >> b;
	}
	catch (string str)
	{
		cout << endl << "Вы ввели некорректную степень полинома. Повторите ввод." << endl << endl;
		goto retry1;
	}
	cout << "Получившиеся полиномы: " << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl << endl;
retry2:
	cout << "Выберите одну из предложенных операций: " << endl;
	cout << "1) a + b " << endl;
	cout << "2) a - b " << endl;
	cout << "3) b - a " << endl;
	cout << "4) a * b " << endl;
	int input;
	cout << endl;
	cin >> input;
	cout << endl;
	if (input < 1 || input > 4)
	{
		cout << endl << "Такой пункт отсутствует. Повторите ввод." << endl << endl;
		goto retry2;
	}
	try
	{
		switch (input)
		{
		case 1:
			cout << "a + b = " << a + b << endl;
			break;
		case 2:
			cout << "a - b = " << a - b << endl;
			break;
		case 3:
			cout << "b - a = " << b - a << endl;
			break;
		case 4:
			cout << "a * b = " << a * b << endl;
			break;
		}
	}
	catch (string str)
	{
		cout << "Произошло переполнение при умножении. " << endl << endl;
	}
	return 0;*/
}