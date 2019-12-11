#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_delete_space) {
	string a = { "a + b" };
	TPostfix p;
	p.SetInfix(a);
	p.DeleteSpaceInfix();
	ASSERT_EQ( "a+b" , p.GetInfix());
}
TEST(TPostfix, can_put_space_in_infix) {
	string a = { "a+b" },b;
	TPostfix p;
	p.SetInfix(a);
	b=p.InsertSpace();
	EXPECT_EQ("a + b", b);
}
TEST(TPostfix, can_translate_to_postfix) {
	string a = { "a+b" };
	TPostfix p;
	p.SetInfix(a);
	EXPECT_EQ(" a b +", p.ToPostfix());
}

TEST(TPostfix, cant_translate_infix_with_number_in_alt) {
	string a = { "1a+b" };
	TPostfix p;
	p.SetInfix(a);
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_translate_infix_with_2_operands) {
	string a = { "j*/" };
	TPostfix p;
	p.SetInfix(a);
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_translate_infix_when_first_is_oper) {
	string a = { "+i-o" };
	TPostfix p;
	p.SetInfix(a);
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_translate_incorrect_infix) {
	string a = { "k?t>" };
	TPostfix p;
	p.SetInfix(a);
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_translate_infix_with_alt_with_point) {
	string a = { "5.h+8 "};
	TPostfix p;
	p.SetInfix(a);
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_translate_infix_with_2_points) {
	string a = { "5..8+3 " };
	TPostfix p;
	p.SetInfix(a);
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_translate_infix_with_incorrect_skobkami) {
	string a = { "a+b+(5+1-(y)" };
	TPostfix p;
	p.SetInfix(a);
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, can_translate_to_postfix_functions) {
	string a = { "sin(a)+b" };
	TPostfix p;
	p.SetInfix(a);
	EXPECT_EQ(" a sin b +", p.ToPostfix());
}
TEST(TPostfix, can_translate_to_postfix_alts_many_elenents) {
	string a = { "bread+butter" };
	TPostfix p;
	p.SetInfix(a);
	EXPECT_EQ(" bread butter +", p.ToPostfix());
}
TEST(TPostfix, can_translate_to_postfix_double_number) {
	string a = { "3.19+2.5" };
	TPostfix p;
	p.SetInfix(a);
	EXPECT_EQ(" 3.19 2.5 +", p.ToPostfix());
}
TEST(TPostfix, can_translate_to_postfix_double_number_with_alt) {
	string a = { "a+2.5" };
	TPostfix p;
	p.SetInfix(a);
	EXPECT_EQ(" a 2.5 +", p.ToPostfix());
}
TEST(TPostfix, can_calculate_postfix) {
	string a = { " 1 4 + " };
	TPostfix p;
	p.SetPostfix(a);
	EXPECT_EQ(5, p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_with_skobki) {
	string a = { "1+3*(2+2)" };
	TPostfix p;
	p.SetInfix(a);
	p.ToPostfix();
	EXPECT_EQ(13, p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_with_stepen) {
	string a = { "2^4-16" };
	TPostfix p;
	p.SetInfix(a);
	p.ToPostfix();
	EXPECT_EQ(0, p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_with_functions) {
	string a = { "sin(0)" };
	TPostfix p;
	p.SetInfix(a);
	p.ToPostfix();
	EXPECT_EQ(0, p.Calculate());
}