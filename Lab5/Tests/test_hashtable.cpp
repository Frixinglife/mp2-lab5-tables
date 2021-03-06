﻿#include "HashTable.h"
#include "Polynomials.h"
#include "gtest.h"

TEST(HTable, can_create_table)
{
	HTable<NamedPolynom> a;
	EXPECT_EQ(a.getsize(), 0);
}

TEST(HTable, can_insert_elem)
{
	HTable<NamedPolynom> a;

	NamedPolynom b;
	b.rename("C");
	b.ins(1, 101);

	NamedPolynom c;
	c.rename("P");
	c.ins(5, 528);

	NamedPolynom d;
	d.rename("V");
	d.ins(3, 328);

	a.ins(b.getname(), b);
	a.ins(c.getname(), c);
	a.ins(d.getname(), d);

	EXPECT_EQ(a.getsize(), 3);
}

TEST(HTable, can_find_elem)
{
	HTable<NamedPolynom> a;

	NamedPolynom b;
	b.rename("C");
	b.ins(1, 101);

	NamedPolynom c;
	c.rename("P");
	c.ins(5, 528);

	NamedPolynom d;
	d.rename("V");
	d.ins(3, 328);

	a.ins(b.getname(), b);
	a.ins(c.getname(), c);
	a.ins(d.getname(), d);

	EXPECT_EQ(b, *a.find(b.getname()));
	EXPECT_EQ(c, *a.find(c.getname()));
	EXPECT_EQ(d, *a.find(d.getname()));
}

TEST(HTable, can_not_find_non_existent_elem)
{
	HTable<NamedPolynom> a;

	NamedPolynom b;
	b.rename("C");
	b.ins(1, 101);

	NamedPolynom c;
	c.rename("P");
	c.ins(5, 528);

	a.ins(b.getname(), b);

	EXPECT_EQ(NULL, a.find(c.getname()));
}

TEST(HTable, can_delete_elem)
{
	HTable<NamedPolynom> a;

	NamedPolynom b;
	b.rename("C");
	b.ins(1, 101);

	NamedPolynom c;
	c.rename("P");
	c.ins(5, 528);

	NamedPolynom d;
	d.rename("V");
	d.ins(3, 328);

	a.ins(b.getname(), b);
	a.ins(c.getname(), c);
	a.ins(d.getname(), d);

	EXPECT_EQ(b, *a.find(b.getname()));
	EXPECT_EQ(c, *a.find(c.getname()));
	EXPECT_EQ(d, *a.find(d.getname()));

	a.del(c.getname());
	EXPECT_EQ(NULL, a.find(c.getname()));

	a.del(b.getname());
	EXPECT_EQ(NULL, a.find(b.getname()));

	a.del(d.getname());
	EXPECT_EQ(NULL, a.find(d.getname()));

	EXPECT_EQ(0, a.getsize());
}