#ifndef _UNORDERED_TABLE_H_
#define _UNORDERED_TABLE_H_

#include "Tables.h"

template <class T1, class T2>
class UTable : public Table<T1, T2>
{
private:
	vector<pair<T1, T2*>> v;
	vector<bool> check;
public:
	UTable();
	~UTable() {}
	void ins(const T1& key, const T2& data) override;
	void del(const T1& key) override;
	T2* find(const T1& key) override;
};

template <class T1, class T2>
UTable<T1, T2>::UTable()
{
	cur_size = 0;
	size = start_size;
	vector<pair<T1, T2*>> temp1(size);
	v = temp1;
	vector<bool> temp2(size, false); 
	check = temp2;
}

template <class T1, class T2>
void UTable<T1, T2>::ins(const T1& key, const T2& data)
{
	T2 *temp = new T2(data);
	cur_size++;
	int i;
	for (i = 0; i < size; i++)
	{
		if (check[i] == false)
		{
			v[i] = make_pair(key, temp);
			check[i] = true;
			return;
		}
	}
	size = size * 2;
	check.resize(size, false);
	v.resize(size);
	v[i] = make_pair(key, temp);
	check[i] = true;
}

template <class T1, class T2>
void UTable<T1, T2>::del(const T1& key)
{
	for (int i = 0; i < size; i++)
	{
		if (v[i].first == key)
		{
			cur_size--;
			check[i] = false;
			delete v[i].second;
			return;
		}
	}
}

template <class T1, class T2>
T2* UTable<T1, T2>::find(const T1& key)
{
	for (int i = 0; i < size; i++)
	{
		if (v[i].first == key && check[i] == true)
		{
			return v[i].second;
		}
	}
	return NULL;
}

#endif
