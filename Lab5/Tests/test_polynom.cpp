#include "Polynomials.h"
#include "gtest.h"
#include <algorithm>

TEST(Polynom, can_create_polynom)
{
	ASSERT_NO_THROW(Polynom a;);
}

TEST(Polynom, can_add_monom)
{
	Polynom a;
	a.ins(1, 101);
	EXPECT_EQ(true, a.find(1, 101));
}

TEST(Polynom, can_not_add_monom_with_0_coefficient)
{
	Polynom a;
	a.ins(0, 1);
	EXPECT_EQ(true, a.isEmpty());
}

TEST(Polynom, polynom_must_be_sorted)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	Polynom a(v);
	sort(v.begin(), v.end());
	Polynom b(v);
	EXPECT_EQ(a, b);
}

TEST(Polynom, addition_of_such_terms_when_adding)
{
	Polynom a;
	a.ins(2.0, 10);
	a.ins(-3.1, 10);
	EXPECT_EQ(true, a.find(-1.1, 10));
}

TEST(Polynom, destruction_of_such_terms_when_adding)
{
	Polynom a;
	a.ins(4.0, 102);
	a.ins(-4.0, 102);
	EXPECT_EQ(true, a.isEmpty());
}

TEST(Polynom, can_not_add_monom_with_incorrect_exponent)
{
	Polynom a;
	ASSERT_ANY_THROW(a.ins(2.0, 1000));
	ASSERT_ANY_THROW(a.ins(1.2, -3));
}

TEST(Polynom, can_clear_polynom)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	Polynom a(v);
	a.clear();
	EXPECT_EQ(true, a.isEmpty());
}

TEST(Polynom, copied_polynom_is_equal_to_source_one)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	Polynom a(v), b;
	b = a;
	EXPECT_EQ(a, b);
}

TEST(Polynom, copied_polynom_has_its_own_memory)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	Polynom a(v);

	Polynom b = a;
	b.ins(-4.0, 12);

	EXPECT_NE(a, b);
}

TEST(Polynom, can_del_monom)
{
	Polynom a;
	a.ins(1, 101);
	a.ins(15, 1);
	a.del(1, 101);
	EXPECT_EQ(false, a.find(1, 101));
	a.del(15, 1);
	EXPECT_EQ(true, a.isEmpty());
}

TEST(Polynom, can_multiply_scalar_by_polynom)
{
	vector<pair<double, int>> v;
	v.push_back(make_pair(1.0, 101));
	v.push_back(make_pair(2.0, 1));
	v.push_back(make_pair(4.0, 12));
	Polynom a(v), b;

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

TEST(Polynom, can_add_polynoms_with_different_exponents_and_equal_sizes)
{
	Polynom a, b, c;

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

TEST(Polynom, can_add_polynoms_with_different_exponents_and_different_sizes_1)
{
	Polynom a, b, c;

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

TEST(Polynom, can_add_polynoms_with_different_exponents_and_different_sizes_2)
{
	Polynom a, b, c;

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

TEST(Polynom, can_add_polynoms_with_some_equal_exponents)
{
	Polynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(-1.0, 89);
	b.ins(4.0, 202);

	c = a + b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(5.4, 202));
	EXPECT_EQ(true, c.find(-1.0, 89));
}

TEST(Polynom, can_add_polynoms_with_equal_exponents_and_opposite_coefficients)
{
	Polynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(-2.0, 101);
	b.ins(-1.4, 202);

	c = a + b;

	EXPECT_EQ(true, c.isEmpty());
}

TEST(Polynom, can_sub_polynoms_with_different_exponents_and_equal_sizes)
{
	Polynom a, b, c;

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

TEST(Polynom, can_sub_polynoms_with_different_exponents_and_different_sizes_1)
{
	Polynom a, b, c;

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

TEST(Polynom, can_sub_polynoms_with_different_exponents_and_different_sizes_2)
{
	Polynom a, b, c;

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

TEST(Polynom, can_sub_polynoms_with_some_equal_exponents)
{
	Polynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(-1.0, 89);
	b.ins(4.0, 202);

	c = a - b;

	EXPECT_EQ(true, c.find(2.0, 101));
	EXPECT_EQ(true, c.find(-2.6, 202));
	EXPECT_EQ(true, c.find(1.0, 89));
}

TEST(Polynom, can_sub_polynoms_with_equal_exponents_and_equal_coefficients)
{
	Polynom a, b, c;

	a.ins(2.0, 101);
	a.ins(1.4, 202);

	b.ins(2.0, 101);
	b.ins(1.4, 202);

	c = a - b;

	EXPECT_EQ(true, c.isEmpty());
}

TEST(Polynom, can_multiply_polynom_by_polynom)
{
	Polynom a, b, c;

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

TEST(Polynom, multiplication_overflow)
{
	Polynom a, b, c;

	a.ins(2.0, 109);
	a.ins(1.4, 204);

	b.ins(-1.0, 75);
	b.ins(4.0, 202);

	ASSERT_ANY_THROW(c = a * b);
}

TEST(Polynom, can_multiply_polynom_by_polynom_with_simplification)
{
	Polynom a, b, c;

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