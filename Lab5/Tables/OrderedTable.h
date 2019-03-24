#ifndef _ORDERED_TABLE_H_
#define _ORDERED_TABLE_H_

#include "Tables.h"
#include <algorithm>

template <class T1, class T2>
class OTable : public Table<T1, T2>
{
private:
	vector<pair<T1, T2*>> v;
	bool comp(const T1& a, const T1& b);
	int bin_find(const T1& key, int *op = NULL);
public:
	OTable();
	~OTable() {}
	void ins(const T1& key, const T2& data, int *op = NULL) override;
	void del(const T1& key, int *op = NULL) override;
	T2* find(const T1& key, int *op = NULL) override;
};

template <class T1, class T2>
bool OTable<T1, T2>::comp(const T1& a, const T1& b)
{
	return a < b;
}

template <class T1, class T2>
OTable<T1, T2>::OTable()
{
	cur_size = 0;
	size = 0;
	vector<pair<T1, T2*>> temp;
	temp.reserve(start_size);
	v = temp;
}

template <class T1, class T2>
int OTable<T1, T2>::bin_find(const T1& key, int *op)
{
	int c = 0;
	if (v.empty())
	{
		c++;
		if (op)
		{
			*op = c;
		}
		return -1;
	}
	int mid = 0, left = 0, right = size - 1;
	c += 3;
	while (true)
	{
		mid = (left + right) / 2;
		c += 2;
		if (comp(key, v[mid].first))
		{
			right = mid - 1;
			c += 2;
		}
		else if (comp(v[mid].first, key))
		{
			left = mid + 1;
			c += 2;
		}
		else
		{
			if (op)
			{
				*op = c;
			}
			return mid;
		}
		if (left > right)
		{
			c++;
			if (op)
			{
				*op = c;
			}
			return -1;
		}
	}
}

template <class T1, class T2>
void OTable<T1, T2>::ins(const T1& key, const T2& data, int *op)
{
	T2 *temp = new T2(data);
	cur_size++;
	int c = 2;
	if (size == 0)
	{
		v.push_back(make_pair(key, temp));
		size++;
		c += 2;
		if (op)
		{
			*op = c;
		}
		return;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			c++;
			if (comp(key, v[i].first))
			{
				v.insert(v.begin() + i, make_pair(key, temp));
				size++;
				c += 2 + (size - i);
				if (op)
				{
					*op = c;
				}
				return;
			}
		}
		v.push_back(make_pair(key, temp));
		size++;
		c += 2;
		if (op)
		{
			*op = c;
		}
	}
}

template <class T1, class T2>
void OTable<T1, T2>::del(const T1& key, int *op)
{
	int c = 0;
	int *o = &c;
	int ind = bin_find(key, o);
	if (ind != -1)
	{
		delete v[ind].second;
		v.erase(v.begin() + ind);
		cur_size--;
		size--;
		c += 4 + (size - ind);
	}
	if (op)
	{
		*op = c;
	}
}

template <class T1, class T2>
T2* OTable<T1, T2>::find(const T1& key, int *op)
{
	int c = 0;
	int *o = &c;
	int ind = bin_find(key, o);
	if (op)
	{
		*op = c;
	}
	if (ind == -1)
	{
		return NULL;
	}
	else
	{
		return v[ind].second;
	}
}

template <class T>
class OTable<string, T> : public Table<string, T>
{
private:
	vector<pair<string, T*>> v;
	bool comp(const string& a, const string& b);
	int bin_find(const string& key, int *op = NULL);
public:
	OTable();
	~OTable() {}
	void ins(const string& key, const T& data, int *op = NULL) override;
	void del(const string& key, int *op = NULL) override;
	T* find(const string& key, int *op = NULL) override;
};

template <class T>
bool OTable<string, T>::comp(const string& a, const string& b)
{
	int m = min(a.size(), b.size());
	for (int i = 0; i < m; i++)
	{
		if (a[i] == b[i])
		{
			continue;
		}
		else
		{
			return a[i] < b[i];
		}
	}
	return a.size() < b.size();
}

template <class T>
OTable<string, T>::OTable()
{
	cur_size = 0;
	size = 0;
	vector<pair<string, T*>> temp;
	temp.reserve(start_size);
	v = temp;
}

template <class T>
int OTable<string, T>::bin_find(const string& key, int *op)
{
	int c = 0;
	if (v.empty())
	{
		c++;
		if (op)
		{
			*op = c;
		}
		return -1;
	}
	int mid = 0, left = 0, right = size - 1;
	c += 3;
	while (true)
	{
		mid = (left + right) / 2;
		c += 2;
		if (comp(key, v[mid].first))
		{
			right = mid - 1;
			c += 2;
		}
		else if (comp(v[mid].first, key))
		{
			left = mid + 1;
			c += 2;
		}
		else
		{
			if (op)
			{
				*op = c;
			}
			return mid;
		}
		if (left > right)
		{
			c++;
			if (op)
			{
				*op = c;
			}
			return -1;
		}
	}
}

template <class T>
void OTable<string, T>::ins(const string& key, const T& data, int *op)
{
	T *temp = new T(data);
	cur_size++;
	int c = 2;
	if (size == 0)
	{
		v.push_back(make_pair(key, temp));
		size++;
		c += 2;
		if (op)
		{
			*op = c;
		}
		return;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			c++;
			if (comp(key, v[i].first))
			{
				v.insert(v.begin() + i, make_pair(key, temp));
				size++;
				c += 2 + (size - i);
				if (op)
				{
					*op = c;
				}
				return;
			}
		}
		v.push_back(make_pair(key, temp));
		size++;
		c += 2;
		if (op)
		{
			*op = c;
		}
	}
}

template <class T>
void OTable<string, T>::del(const string& key, int *op)
{
	int c = 0;
	int *o = &c;
	int ind = bin_find(key, o);
	if (ind != -1)
	{
		delete v[ind].second;
		v.erase(v.begin() + ind);
		cur_size--;
		size--;
		c += 4 + (size - ind);
	}
	if (op)
	{
		*op = c;
	}
}

template <class T>
T* OTable<string, T>::find(const string& key, int *op)
{
	int c = 0;
	int *o = &c;
	int ind = bin_find(key, o);
	if (op)
	{
		*op = c;
	}
	if (ind == -1)
	{
		return NULL;
	}
	else
	{
		return v[ind].second;
	}
}

#endif
