#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "Tables.h"
#include <list>

// Не получится написать шаблонный класс в общем виде, т.к. хэш функция подбирается для определенного типа ключей

template <class T>
class HTable: public Table<string, T>
{
private:
	vector<list<pair<string, T*>>*> v;
	int hash(const string& key, int *op = NULL);
public:
	HTable();
	~HTable() {}
	void ins(const string& key, const T& data, int *op = NULL) override;
	void del(const string& key, int *op = NULL) override;
	T* find(const string& key, int *op = NULL) override;
};

template <class T>
int HTable<T>::hash(const string& key, int *op)
{
	int c = 0;
	int res = 0;
	for (auto it : key)
	{
		c++;
		res += (int)it;
	}
	if (op)
	{
		*op = c;
	}
	return (res % size);
}

template <class T>
HTable<T>::HTable()
{
	cur_size = 0;
	size = start_size;
	vector<list<pair<string, T*>>*> temp(size, NULL);
	v = temp;
}

template <class T>
void HTable<T>::ins(const string& key, const T& data, int *op)
{
	cur_size++;
	T *d = new T(data);
	int c = 2;
	int *o = &c;
	int ind = hash(key, o);
	if (v[ind] == NULL)
	{
		list<pair<string, T*>> *temp = new list<pair<string, T*>>;
		temp->push_back(make_pair(key, d));
		v[ind] = temp;
		c += 4;
	}
	else
	{
		v[ind]->push_back(make_pair(key, d));
		c++;
	}
	if (op)
	{
		*op = c;
	}
}

template <class T>
T* HTable<T>::find(const string& key, int *op)
{
	int c = 0;
	int *o = &c;
	int ind = hash(key, o);
	if (v[ind] == NULL)
	{
		c++;
		if (op)
		{
			*op = c;
		}
		return NULL;
	}
	for (auto it = v[ind]->begin(); it != v[ind]->end(); it++)
	{
		c++;
		if (it->first == key)
		{
			if (op)
			{
				*op = c;
			}
			return it->second;
		}
	}
	if (op)
	{
		*op = c;
	}
	return NULL;
}

template<class T>
void HTable<T>::del(const string& key, int *op)
{
	int c = 0;
	int *o = &c;
	int ind = hash(key, o);
	if (v[ind] == NULL)
	{
		c++;
		if (op)
		{
			*op = c;
		}
		return;
	}
	else
	{
		for (auto it = v[ind]->begin(); it != v[ind]->end(); it++)
		{
			c++;
			if (it->first == key)
			{
				v[ind]->erase(it);
				cur_size--;
				c += 2;
				if (v[ind]->empty())
				{
					delete v[ind];
					v[ind] = NULL;
					c += 2;
				}
				if (op)
				{
					*op = c;
				}
				return;
			}
		}
	}
	if (op)
	{
		*op = c;
	}
}

#endif
