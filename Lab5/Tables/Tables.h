#ifndef _TABLES_H_
#define _TABLES_H_

#include <vector>
using namespace std;

#define start_size 1024

template <class T1, class T2>
class Table
{
protected:
	int cur_size, size;
public:
	Table() {}
	virtual ~Table() {}
	int getsize() const { return cur_size; }
	virtual void ins(const T1& key, const T2& data, int *op = NULL) = 0;
	virtual void del(const T1& key, int *op = NULL) = 0;
	virtual T2* find(const T1& key, int *op = NULL) = 0;
};

#endif