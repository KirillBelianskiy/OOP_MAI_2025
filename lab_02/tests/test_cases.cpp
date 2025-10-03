#include "../src/classes.h"
#include <gtest/gtest.h>

TEST(ConstructorTest, FromStringValid)
{
    Seven a("423");
    EXPECT_EQ(a.to_string(), "423");
}

TEST(ConstructorTest, FromStringInvalidChar)
{
    EXPECT_THROW(Seven("48"), std::out_of_range);
}

TEST(ConstructorTest, FromStringEmpty)
{
    EXPECT_THROW(Seven(""), std::invalid_argument);
}

TEST(ConstructorTest, FromInitializerList)
{
    Seven a({1, 2, 3});
    EXPECT_EQ(a.to_string(), "321");
}

TEST(ConstructorTest, FromArray)
{
    unsigned char arr[] = {3, 2, 1};
    Seven a(3, arr);
    EXPECT_EQ(a.to_string(), "123");
}

TEST(ConstructorTest, FromArrayInvalidDigit)
{
    unsigned char arr[] = {7, 1};
    EXPECT_THROW(Seven(2, arr), std::out_of_range);
}

TEST(ArithmeticTest, AddSimple)
{
    Seven a("1");
    Seven b("1");
    Seven c = a.add(b);
    EXPECT_EQ(c.to_string(), "2");
}

TEST(ArithmeticTest, AddWithCarry)
{
    Seven a("6");
    Seven b("1");
    Seven c = a.add(b);
    EXPECT_EQ(c.to_string(), "10");
}

TEST(ArithmeticTest, SubtractSimple)
{
    Seven a("423");
    Seven b({1, 2, 4});
    Seven c = a.subtract(b);
    EXPECT_EQ(c.to_string(), "2");
}

TEST(ArithmeticTest, SubtractSelf)
{
    Seven a("123");
    Seven b("123");
    Seven c = a.subtract(b);
    EXPECT_EQ(c.to_string(), "0");
}

TEST(ArithmeticTest, SubtractSmallerMinusBigger)
{
    Seven a("12");
    Seven b("123");
    Seven c = a.subtract(b);
    EXPECT_EQ(c.to_string(), "0");
}

TEST(ComparisonTest, Equality)
{
    Seven a("123");
    Seven b("123");
    EXPECT_TRUE(a.is_equal(b));
    EXPECT_FALSE(a.is_greater(b));
    EXPECT_FALSE(a.is_less(b));
}

TEST(ComparisonTest, GreaterAndLess)
{
    Seven a("124");
    Seven b("123");
    EXPECT_TRUE(a.is_greater(b));
    EXPECT_FALSE(a.is_less(b));
    EXPECT_FALSE(a.is_equal(b));
}

TEST(CopyMoveTest, CopyConstructor)
{
    Seven a("456");
    Seven b(a);
    EXPECT_EQ(b.to_string(), "456");
}

TEST(CopyMoveTest, AssignmentOperator)
{
    Seven a("123");
    Seven b("6");
    b = a;
    EXPECT_EQ(b.to_string(), "123");
}

TEST(CopyMoveTest, MoveConstructor)
{
    Seven a("123");
    Seven b(std::move(a));
    EXPECT_EQ(b.to_string(), "123");
}

TEST(CopyMoveTest, MoveAssignment)
{
    Seven a("555");
    Seven b("1");
    b = std::move(a);
    EXPECT_EQ(b.to_string(), "555");
}
