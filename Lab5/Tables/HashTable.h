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
	int hash(const string& key);
public:
	HTable();
	~HTable() {}
	void ins(const string& key, const T& data) override;
	void del(const string& key) override;
	T* find(const string& key) override;
};

template <class T>
int HTable<T>::hash(const string& key)
{
	int res = 0;
	for (auto it : key)
	{
		res += (int)it;
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
void HTable<T>::ins(const string& key, const T& data)
{
	cur_size++;
	T *d = new T(data);
	int ind = hash(key);
	if (v[ind] == NULL)
	{
		list<pair<string, T*>> *temp = new list<pair<string, T*>>;
		temp->push_back(make_pair(key, d));
		v[ind] = temp;
	}
	else
	{
		v[ind]->push_back(make_pair(key, d));
	}
}

template <class T>
T* HTable<T>::find(const string& key)
{
	int ind = hash(key);
	if (v[ind] == NULL)
	{
		return NULL;
	}
	for (auto it = v[ind]->begin(); it != v[ind]->end(); it++)
	{
		if (it->first == key)
		{
			return it->second;
		}
	}
	return NULL;
}

template<class T>
void HTable<T>::del(const string& key)
{
	int ind = hash(key);
	if (v[ind] == NULL)
	{
		return;
	}
	else
	{
		for (auto it = v[ind]->begin(); it != v[ind]->end(); it++)
		{
			if (it->first == key)
			{
				v[ind]->erase(it);
				cur_size--;
				if (v[ind]->empty())
				{
					delete v[ind];
					v[ind] = NULL;
				}
				return;
			}
		}
	}
}

#endif
