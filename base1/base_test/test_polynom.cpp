#include <gtest.h>
#include "../base1/polynom.h"
TEST(polynom, TEST1)
{
	ASSERT_NO_THROW(true);
}

TEST(polynom, can_create_polynom) {
	ASSERT_NO_THROW(polynom p);
}

TEST(polynom, can_delete_space) {
	string a = "x2y2z2+ x2y3z3";
	polynom p;
	p.InputPolynom(a);
	p.DeleteSpace();
	ASSERT_EQ("x2y2z2+x2y3z3", p.GetString());
}

TEST(polynom, can_insert_space) {
	string a = "x2y2z2+x2y3z3";
	polynom p;
	p.InputPolynom(a);
	p.InsertSpace();
	ASSERT_EQ("x2y2z2 +x2y3z3", p.GetString());
}

TEST(polynom, can_create_with_string) {
	string a = "x2y2z2";
	polynom p(a);
	ASSERT_EQ("+1.000000x2y2z2",p.GetString() );
}

TEST(polynom, can_create_copy) {
	string a = "x2y2z2";
	polynom p(a);
	polynom p1(p);
	ASSERT_EQ("+1.000000x2y2z2", p1.GetString());
}

TEST(polynom, cant_create_with_incorrect_elems) {
	string a = "?/&^$#@}[>~";
	ASSERT_ANY_THROW(polynom b(a));
}

TEST(polynom, cant_create_with_incorrect_var) {
	string a = "a2g5i10";
	ASSERT_ANY_THROW(polynom b(a));
}

TEST(polynom, cant_create_with_several_points) {
	string a = "7.5..x2.5y2z2";
	ASSERT_ANY_THROW(polynom b(a));
}

TEST(polynom, cant_create_with_too_large_pow) {
	string a = "3x2y1001z2";
	ASSERT_ANY_THROW(polynom b(a));
}

TEST(polynom, delete_var_with_0_pow) {
	string a = "x2y2z2+x2y0z0";
	polynom p(a);
	ASSERT_EQ("+1.000000x2y2z2+1.000000x2", p.GetString());
}

TEST(polynom, transform_var_with_1_pow) {
	string a = "x2y2z2+x2y1z1";
	polynom p(a);
	ASSERT_EQ("+1.000000x2y2z2+1.000000x2yz", p.GetString());
}

TEST(polynom, can_assign_polynom) {
	string a = "x2y2z2";
	polynom p(a);
	polynom p1;
	p1 = p;
	ASSERT_EQ("+1.000000x2y2z2", p1.GetString());
}

TEST(polynom, can_calculate_in_point) {
	string a = "2x2y2z2-3x2yz";
	polynom p(a);
	double v[3] = {1,2,3};
	ASSERT_EQ(54, p.Calculate(v));
}

TEST(polynom, can_add) {
	string a = "2x2y2z2-3x2yz";
	string b = "3xyz";
	polynom p(a);
	polynom p1(b);
	polynom tmp = p + p1;
	double v[3] = { 1,2,3 };
	ASSERT_EQ(72, tmp.Calculate(v));
}

TEST(polynom, can_sub) {
	string a = "2x2y2z2-3x2yz";
	string b = "3xyz";
	polynom p(a);
	polynom p1(b);
	polynom tmp = p - p1;
	double v[3] = { 1,2,3 };
	ASSERT_EQ(36, tmp.Calculate(v));
}

TEST(polynom, can_cast) {
	string a = "x2y2z2+2x2y2z2";
	polynom p(a);
	ASSERT_EQ("+3.000000x2y2z2", p.GetString());
}

TEST(polynom, can_mult_scal) {
	string a = "2x2y2z2-3x2yz";
	polynom p(a);
	polynom tmp = p * 2;
	double v[3] = { 1,2,3 };
	ASSERT_EQ(108, tmp.Calculate(v));
}

TEST(polynom, can_mult_poly) {
	string a = "2xy2z-3x2yz";
	string b = "3xyz+5y2";
	polynom p(a);
	polynom p1(b);
	polynom tmp = p * p1;
	double v[3] = { 1,2,3 };
	ASSERT_EQ(228, tmp.Calculate(v));
}

TEST(polynom, can_derative_x) {
	string a = "2x2y2z2-3x2yz";
	polynom p(a); char x = 'x';
	polynom tmp = p.derative(x);
	double v[3] = { 1,2,3 };
	ASSERT_EQ(108, tmp.Calculate(v));
}

TEST(polynom, can_derative_y) {
	string a = "2x2y2z2-3x2yz";
	polynom p(a); char x = 'y';
	polynom tmp = p.derative(x);
	double v[3] = { 1,2,3 };
	ASSERT_EQ(63, tmp.Calculate(v));
}

TEST(polynom, can_derative_z) {
	string a = "2x2y2z2-3x2yz";
	polynom p(a); char x = 'z';
	polynom tmp = p.derative(x);
	double v[3] = { 1,2,3 };
	ASSERT_EQ(42, tmp.Calculate(v));
}

TEST(polynom, can_integration_x) {
	string a = "6x2yz-12xy3z2";
	polynom p(a); char x = 'x';
	polynom tmp = p.integration(x);
	double v[3] = { 1,2,3 };
	ASSERT_EQ(-420, tmp.Calculate(v));
}

TEST(polynom, can_integration_y) {
	string a = "6x2yz-12xy3z2";
	polynom p(a); char x = 'y';
	polynom tmp = p.integration(x);
	double v[3] = { 1,2,3 };
	ASSERT_EQ(-396, tmp.Calculate(v));
}

TEST(polynom, can_integration_z) {
	string a = "6x2yz-12xy3z2";
	polynom p(a); char x = 'z';
	polynom tmp = p.integration(x);
	double v[3] = { 1,2,3 };
	ASSERT_EQ(-810, tmp.Calculate(v));
}

TEST(polynom, can_derative_const) {
	string a = "x2+y2";
	polynom p(a); char x = 'x';
	polynom tmp = p.derative(x);
	double v[3] = { 1,2,3 };
	ASSERT_EQ("+2.000000x", tmp.GetString());
}