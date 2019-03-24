#include "Polynomials.h"
#include "gtest.h"

TEST(NamedPolynom, can_create_namedpolynom_with_default_name)
{
	NamedPolynom a;
	EXPECT_EQ("Nameless", a.getname());
}

TEST(NamedPolynom, can_create_namedpolynom_with_name)
{
	NamedPolynom a("A");
	EXPECT_EQ("A", a.getname());
}

TEST(NamedPolynom, can_create_namedpolynom_using_vector)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	NamedPolynom a(v, "B");
	EXPECT_EQ(false, a.isEmpty());
	EXPECT_EQ("B", a.getname());
}

TEST(NamedPolynom, can_rename_namedpolynom)
{
	NamedPolynom a("A");
	a.rename("C");
	EXPECT_EQ("C", a.getname());
}

TEST(NamedPolynom, copied_namedpolynom_is_equal_to_source_one)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	NamedPolynom a(v), b;
	b = a;
	EXPECT_EQ(a, b);
}

TEST(NamedPolynom, copied_namedpolynom_has_its_own_memory)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	NamedPolynom a(v);

	NamedPolynom b = a;
	b.ins(-4.0, 12);

	EXPECT_NE(a, b);
}

