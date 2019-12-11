#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, cant_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, cant_create_stack_with_too_big_length) {
	ASSERT_ANY_THROW(TStack<int> st(102));
}

TEST(TStack, can_check_empty) {
	TStack<int> st(2);
	ASSERT_EQ(st.empty(),1);
}
TEST(TStack, can_check_full) {
	TStack<int>st(2);
	for (int i = 0; i < st.GetSize(); i++)
		st.push(0);
	EXPECT_EQ(1, st.full());
}
TEST(TStack, throws_when_get_top_element_in_empty) {
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.gettop());
}
TEST(TStack, can_push) {
	TStack<int> st(2);
	for (int i = 0; i < st.GetSize(); i++) {
		st.push(0);
	}
	ASSERT_EQ(st.gettop(), 0);
}
TEST(TStack, can_pop) {
	TStack<int> st(2);
	for (int i = 0; i < st.GetSize(); i++) {
		st.push(0);
	}
	st.pop();
	ASSERT_EQ(st.GetTop(), 0);

}
TEST(TStack, throws_when_push_in_full) {
	TStack<int> st(2);
	for (int i = 0; i < st.GetSize(); i++) {
		st.push(0);
	}
	ASSERT_ANY_THROW(st.push(0));
}
TEST(TStack, throws_when_pop_in_empty) {
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.pop());
}
