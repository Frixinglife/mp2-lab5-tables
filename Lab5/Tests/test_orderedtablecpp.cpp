﻿#include "OrderedTable.h"
#include "Polynomials.h"
#include "gtest.h"

TEST(OTable, can_create_table)
{
	OTable<string, NamedPolynom> a;
	EXPECT_EQ(a.getsize(), 0);
}

TEST(OTable, can_insert_elem)
{
	OTable<string, NamedPolynom> a;

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

TEST(OTable, can_find_elem)
{
	OTable<string, NamedPolynom> a;

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

TEST(OTable, can_not_find_non_existent_elem)
{
	OTable<string, NamedPolynom> a;

	NamedPolynom b;
	b.rename("C");
	b.ins(1, 101);

	NamedPolynom c;
	c.rename("P");
	c.ins(5, 528);

	a.ins(b.getname(), b);

	EXPECT_EQ(NULL, a.find(c.getname()));
}

TEST(OTable, can_delete_elem)
{
	OTable<string, NamedPolynom> a;

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