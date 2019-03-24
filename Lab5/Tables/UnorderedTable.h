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
	void ins(const T1& key, const T2& data, int *op = NULL) override;
	void del(const T1& key, int *op = NULL) override;
	T2* find(const T1& key, int *op = NULL) override;
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
void UTable<T1, T2>::ins(const T1& key, const T2& data, int *op)
{
	T2 *temp = new T2(data);
	cur_size++;
	int i;
	int c = 2;
	for (i = 0; i < size; i++)
	{
		c++;
		if (check[i] == false)
		{
			v[i] = make_pair(key, temp);
			check[i] = true;
			c += 3;
			if (op)
			{
				*op = c;
			}
			return;
		}
	}
	size = size * 2;
	check.resize(size, false);
	v.resize(size);
	v[i] = make_pair(key, temp);
	check[i] = true;
	c += 2 * size + 3;
	if (op)
	{
		*op = c;
	}
}

template <class T1, class T2>
void UTable<T1, T2>::del(const T1& key, int *op)
{
	int c = 0;
	for (int i = 0; i < size; i++)
	{
		c++;
		if (v[i].first == key)
		{
			cur_size--;
			check[i] = false;
			delete v[i].second;
			c += 4;
			if (op)
			{
				*op = c;
			}
			return;
		}
	}
	if (op)
	{
		*op = c;
	}
}

template <class T1, class T2>
T2* UTable<T1, T2>::find(const T1& key, int *op)
{
	int c = 0;
	for (int i = 0; i < size; i++)
	{
		c++;
		if (v[i].first == key && check[i] == true)
		{
			c += 2;
			if (op)
			{
				*op = c;
			}
			return v[i].second;
		}
	}
	if (op)
	{
		*op = c;
	}
	return NULL;
}

#endif
