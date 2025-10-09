#include "gtest/gtest.h"
#include "../src/classes.h"
#include <stdexcept>

TEST(SevenConstructors, Default)
{
    Seven s;
    EXPECT_EQ(s.get_size(), 1);
    EXPECT_EQ(s.to_string(), "0");
}

TEST(SevenConstructors, Array)
{
    unsigned char arr[] = {1, 2, 3};
    Seven s(3, arr);
    EXPECT_EQ(s.get_size(), 3);
    EXPECT_EQ(s.to_string(), "321");
}

TEST(SevenConstructors, ArrayThrowsOnNull)
{
    EXPECT_THROW(Seven(5, nullptr), std::invalid_argument);
}

TEST(SevenConstructors, ArrayThrowsOnZeroSize)
{
    unsigned char arr[] = {1};
    EXPECT_THROW(Seven(0, arr), std::invalid_argument);
}

TEST(SevenConstructors, ArrayThrowsOnBadDigit)
{
    unsigned char arr[] = {1, 2, 7};
    EXPECT_THROW(Seven(3, arr), std::out_of_range);
}

TEST(SevenConstructors, InitializerList)
{
    Seven s({1, 2, 3});
    EXPECT_EQ(s.get_size(), 3);
    EXPECT_EQ(s.to_string(), "321");
}

TEST(SevenConstructors, InitializerListThrowsOnEmpty)
{
    EXPECT_THROW(Seven({}), std::invalid_argument);
}

TEST(SevenConstructors, InitializerListThrowsOnBadDigit)
{
    EXPECT_THROW(Seven({1, 2, 8}), std::out_of_range);
}

TEST(SevenConstructors, String)
{
    Seven s("321");
    EXPECT_EQ(s.get_size(), 3);
    EXPECT_EQ(s.to_string(), "321");
}

TEST(SevenConstructors, StringThrowsOnEmpty)
{
    EXPECT_THROW(Seven(""), std::invalid_argument);
}

TEST(SevenConstructors, StringThrowsOnBadDigit)
{
    EXPECT_THROW(Seven("127"), std::out_of_range);
    EXPECT_THROW(Seven("12a"), std::out_of_range);
}

TEST(SevenConstructors, Copy)
{
    Seven s1("12345");
    Seven s2(s1);
    EXPECT_TRUE(s1.is_equal(s2));
    EXPECT_EQ(s1.to_string(), "12345");
    EXPECT_EQ(s2.to_string(), "12345");
}

TEST(SevenConstructors, Move)
{
    Seven s1("12345");
    Seven s2(std::move(s1));
    EXPECT_EQ(s2.to_string(), "12345");
    EXPECT_EQ(s1.get_size(), 0);
}

TEST(SevenArithmetic, AddSimple)
{
    Seven s1("12");
    Seven s2("34");
    Seven s3 = s1.add(s2);
    EXPECT_EQ(s3.to_string(), "46");
}

TEST(SevenArithmetic, AddWithCarry)
{
    Seven s1("16");
    Seven s2("1");
    Seven s3 = s1.add(s2);
    EXPECT_EQ(s3.to_string(), "20");
}

TEST(SevenArithmetic, AddMultipleCarries)
{
    Seven s1("666");
    Seven s2("1");
    Seven s3 = s1.add(s2);
    EXPECT_EQ(s3.to_string(), "1000");
}

TEST(SevenArithmetic, AddDifferentSizes)
{
    Seven s1("123");
    Seven s2("4");
    Seven s3 = s1.add(s2);
    EXPECT_EQ(s3.to_string(), "130");
}

TEST(SevenArithmetic, AddDifferentSizesReversed)
{
    Seven s1("4");
    Seven s2("123");
    Seven s3 = s1.add(s2);
    EXPECT_EQ(s3.to_string(), "130");
}

TEST(SevenArithmetic, AddToZero)
{
    Seven s1("123");
    Seven s_zero;
    Seven s3 = s1.add(s_zero);
    EXPECT_EQ(s3.to_string(), "123");
}

TEST(SevenArithmetic, SubtractSimple)
{
    Seven s1("45");
    Seven s2("12");
    Seven s3 = s1.subtract(s2);
    EXPECT_EQ(s3.to_string(), "33");
}

TEST(SevenArithmetic, SubtractWithBorrow)
{
    Seven s1("20");
    Seven s2("1");
    Seven s3 = s1.subtract(s2);
    EXPECT_EQ(s3.to_string(), "16");
}

TEST(SevenArithmetic, SubtractMultipleBorrows)
{
    Seven s1("1000");
    Seven s2("1");
    Seven s3 = s1.subtract(s2);
    EXPECT_EQ(s3.to_string(), "666");
}

TEST(SevenArithmetic, SubtractToZero)
{
    Seven s1("123");
    Seven s2("123");
    Seven s3 = s1.subtract(s2);
    EXPECT_EQ(s3.to_string(), "0");
}

TEST(SevenArithmetic, SubtractRemovesLeadingZeros)
{
    Seven s1("101");
    Seven s2("100");
    Seven s3 = s1.subtract(s2);
    EXPECT_EQ(s3.to_string(), "1");
    EXPECT_EQ(s3.get_size(), 1);
}

TEST(SevenArithmetic, SubtractNegativeResult)
{
    Seven s1("10");
    Seven s2("11");
    Seven s3 = s1.subtract(s2);
    EXPECT_EQ(s3.to_string(), "0");
    EXPECT_EQ(s3.get_size(), 1);
}

TEST(SevenComparison, IsEqual)
{
    Seven s1("123");
    Seven s2("123");
    Seven s3("124");
    Seven s4("12");
    Seven s_zero1;
    Seven s_zero2("0");

    EXPECT_TRUE(s1.is_equal(s2));
    EXPECT_FALSE(s1.is_equal(s3));
    EXPECT_FALSE(s1.is_equal(s4));
    EXPECT_TRUE(s_zero1.is_equal(s_zero2));
}

TEST(SevenComparison, IsGreater)
{
    Seven s1("123");
    Seven s2("122");
    Seven s3("12");
    Seven s4("1000");
    Seven s5("123");

    EXPECT_TRUE(s1.is_greater(s2));
    EXPECT_TRUE(s1.is_greater(s3));
    EXPECT_FALSE(s1.is_greater(s4));
    EXPECT_FALSE(s1.is_greater(s5));
}

TEST(SevenComparison, IsLess)
{
    Seven s1("123");
    Seven s2("124");
    Seven s3("1000");
    Seven s4("12");
    Seven s5("123");

    EXPECT_TRUE(s1.is_less(s2));
    EXPECT_TRUE(s1.is_less(s3));
    EXPECT_FALSE(s1.is_less(s4));
    EXPECT_FALSE(s1.is_less(s5));
}

TEST(SevenUtility, ToString)
{
    Seven s1;
    EXPECT_EQ(s1.to_string(), "0");

    Seven s2("6543210");
    EXPECT_EQ(s2.to_string(), "6543210");

    Seven s3({0, 1, 2});
    EXPECT_EQ(s3.to_string(), "210");
}

TEST(SevenUtility, GetSize)
{
    Seven s1;
    EXPECT_EQ(s1.get_size(), 1);

    Seven s2("123");
    EXPECT_EQ(s2.get_size(), 3);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
