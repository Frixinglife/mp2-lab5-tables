#include "Polynomials.h"
#include "gtest.h"
#include <algorithm>

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

TEST(NamedPolynom, can_add_monom)
{
	NamedPolynom a;
	a.ins(1, 101);
	EXPECT_EQ(true, a.find(1, 101));
}

TEST(NamedPolynom, can_not_add_monom_with_0_coefficient)
{
	NamedPolynom a;
	a.ins(0, 1);
	EXPECT_EQ(true, a.isEmpty());
}

TEST(NamedPolynom, polynom_must_be_sorted)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	NamedPolynom a(v);
	sort(v.begin(), v.end());
	NamedPolynom b(v);
	EXPECT_EQ(a, b);
}

TEST(NamedPolynom, addition_of_such_terms_when_adding)
{
	NamedPolynom a;
	a.ins(2.0, 10);
	a.ins(-3.1, 10);
	EXPECT_EQ(true, a.find(-1.1, 10));
}

TEST(NamedPolynom, destruction_of_such_terms_when_adding)
{
	NamedPolynom a;
	a.ins(4.0, 102);
	a.ins(-4.0, 102);
	EXPECT_EQ(true, a.isEmpty());
}

TEST(NamedPolynom, can_not_add_monom_with_incorrect_exponent)
{
	NamedPolynom a;
	ASSERT_ANY_THROW(a.ins(2.0, 1000));
	ASSERT_ANY_THROW(a.ins(1.2, -3));
}

TEST(NamedPolynom, can_clear_polynom)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	NamedPolynom a(v);
	a.clear();
	EXPECT_EQ(true, a.isEmpty());
}

TEST(NamedPolynom, copied_polynom_is_equal_to_source_one)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	NamedPolynom a(v), b;
	b = a;
	EXPECT_EQ(a, b);
}

TEST(NamedPolynom, copied_polynom_has_its_own_memory)
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

TEST(NamedPolynom, can_del_monom)
{
	NamedPolynom a;
	a.ins(1, 101);
	a.ins(15, 1);
	a.del(1, 101);
	EXPECT_EQ(false, a.find(1, 101));
	a.del(15, 1);
	EXPECT_EQ(true, a.isEmpty());
}

TEST(NamedPolynom, can_multiply_scalar_by_polynom)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	NamedPolynom a(v), b;

	b = a * 5;
	EXPECT_EQ(true, b.find(5.0, 101));
	EXPECT_EQ(true, b.find(10.0, 1));
	EXPECT_EQ(true, b.find(20.0, 12));
	b = b * 0;
	EXPECT_EQ(true, b.isEmpty());

	EXPECT_EQ(true, a.find(1.0, 101));
	EXPECT_EQ(true, a.find(2.0, 1));
	EXPECT_EQ(true, a.find(4.0, 12));
}

TEST(NamedPolynom, can_add_polynoms_with_different_exponents_and_equal_sizes)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(-1.0, 89);

	b.ins(4.0, 202);
	b.ins(14.2, 8);

	c = a + b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(-1.0, 89));
	EXPECT_EQ(true, c.find(4.0, 202));
	EXPECT_EQ(true, c.find(14.2, 8));
}

TEST(NamedPolynom, can_add_polynoms_with_different_exponents_and_different_sizes_1)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(-1.0, 89);
	a.ins(4.0, 202);

	b.ins(14.2, 8);

	c = a + b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(-1.0, 89));
	EXPECT_EQ(true, c.find(4.0, 202));
	EXPECT_EQ(true, c.find(14.2, 8));
}

TEST(NamedPolynom, can_add_polynoms_with_different_exponents_and_different_sizes_2)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);

	b.ins(-1.0, 89);
	b.ins(4.0, 202);
	b.ins(14.2, 8);

	c = a + b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(-1.0, 89));
	EXPECT_EQ(true, c.find(4.0, 202));
	EXPECT_EQ(true, c.find(14.2, 8));
}

TEST(NamedPolynom, can_add_polynoms_with_some_equal_exponents)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(-1.0, 89);
	b.ins(4.0, 202);

	c = a + b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(5.4, 202));
	EXPECT_EQ(true, c.find(-1.0, 89));
}

TEST(NamedPolynom, can_add_polynoms_with_equal_exponents_and_opposite_coefficients)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(-2.0, 101);
	b.ins(-1.4, 202);

	c = a + b;

	EXPECT_EQ(true, c.isEmpty());
}

TEST(NamedPolynom, can_sub_polynoms_with_different_exponents_and_equal_sizes)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(-1.0, 89);

	b.ins(4.0, 202);
	b.ins(14.2, 8);

	c = a - b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(-1.0, 89));
	EXPECT_EQ(true, c.find(-4.0, 202));
	EXPECT_EQ(true, c.find(-14.2, 8));
}

TEST(NamedPolynom, can_sub_polynoms_with_different_exponents_and_different_sizes_1)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(-1.0, 89);
	a.ins(4.0, 202);

	b.ins(14.2, 8);

	c = a - b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(-1.0, 89));
	EXPECT_EQ(true, c.find(4.0, 202));
	EXPECT_EQ(true, c.find(-14.2, 8));
}

TEST(NamedPolynom, can_sub_polynoms_with_different_exponents_and_different_sizes_2)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);

	b.ins(-1.0, 89);
	b.ins(4.0, 202);
	b.ins(14.2, 8);

	c = a - b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(1.0, 89));
	EXPECT_EQ(true, c.find(-4.0, 202));
	EXPECT_EQ(true, c.find(-14.2, 8));
}

TEST(NamedPolynom, can_sub_polynoms_with_some_equal_exponents)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(-1.0, 89);
	b.ins(4.0, 202);

	c = a - b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(-2.6, 202));
	EXPECT_EQ(true, c.find(1.0, 89));
}

TEST(NamedPolynom, can_sub_polynoms_with_equal_exponents_and_equal_coefficients)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(2.0, 101);
	b.ins(1.4, 202);

	c = a - b;

	EXPECT_EQ(true, c.isEmpty());
}

TEST(NamedPolynom, can_multiply_polynom_by_polynom)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(-1.0, 75);
	b.ins(4.0, 202);

	c = a * b;

	EXPECT_EQ(true, c.find(-2.0, 176));
	EXPECT_EQ(true, c.find(8.0, 303));
	EXPECT_EQ(true, c.find(-1.4, 277));
	EXPECT_EQ(true, c.find(5.6, 404));
}

TEST(NamedPolynom, multiplication_overflow)
{
	NamedPolynom a, b, c;

	a.ins(2.0, 109);
	a.ins(1.4, 204);

	b.ins(-1.0, 75);
	b.ins(4.0, 202);

	ASSERT_ANY_THROW(c = a * b);
}

TEST(NamedPolynom, can_multiply_polynom_by_polynom_with_simplification)
{
	NamedPolynom a, b, c;

	// (x - y) * (x + y) = x^2 - y^2

	a.ins(1.0, 100);
	a.ins(-1.0, 10);

	b.ins(1.0, 100);
	b.ins(1.0, 10);

	c = a * b;

	EXPECT_EQ(true, c.find(1.0, 200));
	EXPECT_EQ(true, c.find(-1.0, 20));
	EXPECT_EQ(false, c.find(1.0, 110));
	EXPECT_EQ(false, c.find(-1.0, 110));
}

