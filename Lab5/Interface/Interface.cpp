#include "Interface.h"
#include <vector>

vector<string> names;

void Start(LogTables<NamedPolynom> &t)
{
	EntryRules();
	OperationСhoice(t);
}

void EntryRules()
{
	setlocale(LC_ALL, "Russian");
	cout << "+----------------------------------------------------------------+" << endl;
	cout << "|                     Правила ввода данных                       |" << endl;
	cout << "+----------------------------------------------------------------+" << endl;
	cout << "| 1) Полином составлен из мономов от трех переменных.            |" << endl;
	cout << "| 2) Коэффициенты монома - вещественные числа.                   |" << endl;
	cout << "| 3) Степени (x, y, z) монома  - неотрицательные, не превышают 9.|" << endl;
	cout << "| 4) Полином имеет название.                                     |" << endl;
	cout << "+----------------------------------------------------------------+" << endl;
	cout << endl;
}

void OperationsWithTableOrPolynoms(LogTables<NamedPolynom> &t)
{
	setlocale(LC_ALL, "Russian");
	cout << endl;
	cout << "Выберите один из пунктов меню: " << endl;
	cout << "1) Произвести операцию с таблицей " << endl;
	cout << "  (Положить в таблицу свой полином, " << endl;
	cout << "   найти полином с заданным названием, " << endl;
	cout << "   удалить полином с заданным названием) " << endl;
	cout << "2) Произвести операцию с полиномами: " << endl;
	cout << "  (Выбрать из таблицы 2 полинома с заданными " << endl;
	cout << "   названиями и операцию для них) " << endl;
	cout << "3) Выход " << endl;

	int input;
	cin >> input;

	switch (input)
	{
	case 1:
		OperationСhoice(t);
		return;
	case 2:
		if (t.getsize() < 2)
		{
			cout << endl << "В таблице не хватает полиномов. Выберите другой пункт меню. " << endl;
			OperationsWithTableOrPolynoms(t);
			return;
		}
		SelectPolynoms(t);
		return;
	case 3:
		return;
	default:
		cout << endl << "Такой пункт отсутствует. Повторите ввод." << endl;
		OperationsWithTableOrPolynoms(t);
		return;
	}
}

void OperationСhoice(LogTables<NamedPolynom> &t)
{
	setlocale(LC_ALL, "Russian");
	cout << endl;
	cout << "Выберите один из пунктов меню: " << endl;
	cout << "1) Положить в таблицу свой полином " << endl;
	cout << "2) Найти полином с заданным названием " << endl;
	cout << "3) Удалить полином с заданным названием " << endl;
	cout << "4) Выход " << endl;

	int input;
	cin >> input;

	switch (input)
	{
	case 1:
		AddPolynomToTable(t);
		OperationsWithTableOrPolynoms(t);
		return;
	case 2:
		FindPolynomInTable(t);
		OperationsWithTableOrPolynoms(t);
		return;
	case 3:
		DeletePolynomFromTable(t);
		OperationsWithTableOrPolynoms(t);
		return;
	case 4:
		return;
	default:
		cout << endl << "Такой пункт отсутствует. Повторите ввод." << endl;
		OperationСhoice(t);
		return;
	}
}

void SelectPolynoms(LogTables<NamedPolynom> &t)
{
	cout << endl << "Введите названия двух полиномов из таблицы. " << endl;
	cout << "В таблице имеются полиномы с названиями: ";
	for (int i = 0; i < names.size(); i++)
	{
		cout << names[i] << ((i == names.size() - 1) ? "\n" : ", ");
	}
	string sa, sb;
	NamedPolynom *a, *b;

	cout << "Название первого полинома: ";
	cin >> sa;
	a = t.find(sa);
	if (a == NULL)
	{
		cout << endl << "Полином с таким названием не найден. Повторите ввод. " << endl;
		SelectPolynoms(t);
	}

	cout << "Название второго полинома: ";
	cin >> sb;
	b = t.find(sb);
	if (b == NULL)
	{
		cout << endl << "Полином с таким названием не найден. Повторите ввод. " << endl;
		SelectPolynoms(t);
	}

	cout << endl << "Найденные полиномы: " << endl;
	cout << *a << endl;
	cout << *b << endl;
	cout << endl;

	OperationsWithPolynoms(t, *a, *b);
}

void OperationsWithPolynoms(LogTables<NamedPolynom> &t, NamedPolynom a, NamedPolynom b)
{
	cout << "Выберите один из пунктов меню: " << endl;
	cout << "1) Сложить полиномы " << endl;
	cout << "2) Перемножить полиномы " << endl;
	cout << "3) Вычесть из первого полинома второй " << endl;
	cout << "4) Вычесть из второго полинома первый " << endl;
	cout << "5) Выход " << endl;

	int input;
	cin >> input;

	NamedPolynom c;

	try
	{
		switch (input)
		{
		case 1:
			c = a + b;
			break;
		case 2:
			c = a * b;
			break;
		case 3:
			c = a - b;
			break;
		case 4:
			c = b - a;
			break;
		case 5:
			return;
		default:
			cout << endl << "Такой пункт отсутствует. Повторите ввод." << endl;
			OperationsWithPolynoms(t, a, b);
			return;
		}
	}
	catch (string str)
	{
		cout << endl << "Произошло переполнение при умножении. Выберите другую операцию. " << endl << endl;
		OperationsWithPolynoms(t, a, b);
		return;
	}
	
	SetNameResult(t, c);
}

void SetNameResult(LogTables<NamedPolynom> &t, NamedPolynom res)
{
	cout << "Введите название для полученного полинома: ";
	string str;
	cin >> str;

	for (int i = 0; i < names.size(); i++)
	{
		if (names[i] == str)
		{
			cout << endl << "Полином с таким названием уже есть в таблице. Повторите ввод. " << endl << endl;
			SetNameResult(t, res);
			return;
		}
	}

	res.rename(str);
	cout << endl << "Полученный полином: " << endl << res << endl;

	OperationWithResult(t, res);
}


void OperationWithResult(LogTables<NamedPolynom> &t, NamedPolynom res)
{
	cout << endl;
	cout << "Выберите один из пунктов меню: " << endl;
	cout << "1) Добавить результат операции в таблицу " << endl;
	cout << "2) Не добавлять результата операции в таблицу " << endl;
	cout << "3) Выход " << endl;

	int input;
	cin >> input;

	switch (input)
	{
	case 1:
		t.ins(res.getname(), res);
		names.push_back(res.getname());
		cout << endl << "Результат операции успешно добавлен в таблицу" << endl;
		OperationsWithTableOrPolynoms(t);
		return;
	case 2:
		OperationsWithTableOrPolynoms(t);
		return;
	case 3:
		return;
	default:
		cout << endl << "Такой пункт отсутствует. Повторите ввод." << endl;
		OperationWithResult(t, res);
		return;
	}
}

void AddPolynomToTable(LogTables<NamedPolynom> &t)
{
	setlocale(LC_ALL, "Russian");
	NamedPolynom a;
	try
	{
		cout << endl;
		cin >> a;
	}
	catch (string str)
	{
		cout << endl << "Вы ввели некорректную степень полинома. Повторите ввод." << endl;
		AddPolynomToTable(t);
		return;
	}
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i] == a.getname())
		{
			cout << endl << "Полином с таким названием уже есть в таблице. Повторите ввод. " << endl;
			AddPolynomToTable(t);
			return;
		}
	}
	cout << "Получившийся полином: " << a << endl;
	t.ins(a.getname(), a);
	names.push_back(a.getname());
}

void FindPolynomInTable(LogTables<NamedPolynom> &t)
{
	setlocale(LC_ALL, "Russian");
	cout << "В таблице имеются полиномы с названиями: ";
	for (int i = 0; i < names.size(); i++)
	{
		cout << names[i] << ((i == names.size() - 1) ? "\n" : ", ");
	}
	cout << endl << "Введите название полинома, который необходимо найти: " << endl;
	string str;
	cin >> str;
	NamedPolynom *a = t.find(str);
	if (a == NULL)
	{
		cout << endl << "Полином с таким названием не найден. " << endl;
	}
	else
	{
		cout << "Полином найден: " << endl << *a << endl;
	}
}

void DeletePolynomFromTable(LogTables<NamedPolynom> &t)
{
	setlocale(LC_ALL, "Russian");
	cout << "В таблице имеются полиномы с названиями: ";
	for (int i = 0; i < names.size(); i++)
	{
		cout << names[i] << ((i == names.size() - 1) ? "\n" : ", ");
	}
	cout << endl << "Введите название полинома, который необходимо удалить: " << endl;
	string str;
	cin >> str;
	t.del(str);
	for (int i = 0; i < names.size(); i++)
	{
		if (names[i] == str)
		{
			names.erase(names.begin() + i);
		}
	}
	cout << "Если полином с таким названием был в таблице, то он успешно удален." << endl;
}