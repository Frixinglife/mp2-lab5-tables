#ifndef _LOG_TABLES_H_
#define _LOG_TABLES_H_

#include "HashTable.h"
#include "OrderedTable.h"
#include "UnorderedTable.h"
#include <clocale>

template<class T>
class LogTables
{
private:
	UTable<string, T> ut;
	OTable<string, T> ot;
	HTable<T> ht;
public:
	LogTables();
	~LogTables() {}
	int getsize() const { return ut.getsize(); } // т.к. текущие размеры таблиц совпадают (проводим операции сразу с 3 таблицами)
	void ins(const string &key, const T& data);
	void del(const string &key);
	T* find(const string &key);
};

template <class T>
LogTables<T>::LogTables()
{
	UTable<string, T> u;
	OTable<string, T> o;
	HTable<T> h;
	ut = u;
	ot = o;
	ht = h;
}

template <class T>
void LogTables<T>::ins(const string &key, const T& data)
{
	int u_ins = 0, o_ins = 0, h_ins = 0;
	int *pu = &u_ins, *po = &o_ins, *ph = &h_ins;
	ut.ins(key, data, pu);
	ot.ins(key, data, po);
	ht.ins(key, data, ph);
	setlocale(LC_ALL, "Russian");
	cout << endl;
	cout << "+-------------------------------+" << endl;
	cout << "| Произведена операция вставки. |" << endl;
	cout << "+-------------------------------+" << endl;
	cout << "| Количество операций:" << endl;
	cout << "| Неупорядоченная таблица: " << u_ins << endl;
	cout << "| Упорядоченная таблица: " << o_ins << endl;
	cout << "| Хэш-таблица: " << h_ins << endl;
	cout << "+-------------------------------+" << endl << endl;
}

template <class T>
void LogTables<T>::del(const string &key)
{
	int u_del = 0, o_del = 0, h_del = 0;
	int *pu = &u_del, *po = &o_del, *ph = &h_del;
	ut.del(key, pu);
	ot.del(key, po);
	ht.del(key, ph);
	setlocale(LC_ALL, "Russian");
	cout << endl;
	cout << "+--------------------------------+" << endl;
	cout << "| Произведена операция удаления. |" << endl;
	cout << "+--------------------------------+" << endl;
	cout << "| Количество операций:" << endl;
	cout << "| Неупорядоченная таблица: " << u_del << endl;
	cout << "| Упорядоченная таблица: " << o_del << endl;
	cout << "| Хэш-таблица: " << h_del << endl;
	cout << "+--------------------------------+" << endl << endl;
}

template <class T>
T* LogTables<T>::find(const string &key)
{
	int u_find = 0, o_find = 0, h_find = 0;
	int *pu = &u_find, *po = &o_find, *ph = &h_find;
	ut.find(key, pu);
	T *res = ot.find(key, po);
	ht.find(key, ph);
	setlocale(LC_ALL, "Russian");
	cout << endl;
	cout << "+------------------------------+" << endl;
	cout << "| Произведена операция поиска. |" << endl;
	cout << "+------------------------------+" << endl;
	cout << "| Количество операций:" << endl;
	cout << "| Неупорядоченная таблица: " << u_find << endl;
	cout << "| Упорядоченная таблица: " << o_find << endl;
	cout << "| Хэш-таблица: " << h_find << endl;
	cout << "+------------------------------+" << endl << endl;
	return res;
}

#endif
