#include "gtest/gtest.h"
#include "../src/classes.h"

TEST(SevenConstructors, Default) {
    Seven s;
    EXPECT_EQ(s.get_size(), 1);
    EXPECT_STREQ(s.to_string().c_str(), "0");
}

TEST(SevenConstructors, FromString) {
    Seven s("123");
    EXPECT_EQ(s.get_size(), 3);
    EXPECT_STREQ(s.to_string().c_str(), "123");
}

TEST(SevenConstructors, FromStringWithZero) {
    Seven s("0");
    EXPECT_EQ(s.get_size(), 1);
    EXPECT_STREQ(s.to_string().c_str(), "0");
}

TEST(SevenConstructors, FromInitializerList) {
    Seven s({1, 2, 3});
    EXPECT_EQ(s.get_size(), 3);
    EXPECT_STREQ(s.to_string().c_str(), "321");
}

TEST(SevenConstructors, Copy) {
    Seven s1("654");
    Seven s2(s1);
    EXPECT_TRUE(s1.is_equal(s2));
}

TEST(SevenConstructors, Move) {
    Seven s1("12345");
    Seven s2(std::move(s1));
    EXPECT_STREQ(s2.to_string().c_str(), "12345");
    EXPECT_EQ(s1.get_size(), 0);
}

TEST(SevenExceptions, InvalidString) {
    EXPECT_THROW(Seven s("12a3"), std::out_of_range);
    EXPECT_THROW(Seven s("7"), std::out_of_range);
}

TEST(SevenExceptions, EmptyString) {
    EXPECT_THROW(Seven s(""), std::invalid_argument);
}

TEST(SevenExceptions, InvalidInitializerList) {
    EXPECT_THROW(Seven s({1, 8, 3}), std::out_of_range);
}

TEST(SevenExceptions, EmptyInitializerList) {
    EXPECT_THROW(Seven s({}), std::invalid_argument);
}

TEST(SevenArithmetic, AddNoCarry) {
    Seven s1("111");
    Seven s2("222");
    Seven result = s1.add(s2);
    EXPECT_STREQ(result.to_string().c_str(), "333");
}

TEST(SevenArithmetic, AddWithCarry) {
    Seven s1("16");
    Seven s2("1");
    Seven result = s1.add(s2);
    EXPECT_STREQ(result.to_string().c_str(), "20");
}

TEST(SevenArithmetic, AddDifferentSizes) {
    Seven s1("666");
    Seven s2("1");
    Seven result = s1.add(s2);
    EXPECT_STREQ(result.to_string().c_str(), "1000");
}

TEST(SevenArithmetic, SubtractNoBorrow) {
    Seven s1("333");
    Seven s2("121");
    Seven result = s1.subtract(s2);
    EXPECT_STREQ(result.to_string().c_str(), "212");
}

TEST(SevenArithmetic, SubtractWithBorrow) {
    Seven s1("20");
    Seven s2("1");
    Seven result = s1.subtract(s2);
    EXPECT_STREQ(result.to_string().c_str(), "16");
}

TEST(SevenArithmetic, SubtractToZero) {
    Seven s1("123");
    Seven s2("123");
    Seven result = s1.subtract(s2);
    EXPECT_STREQ(result.to_string().c_str(), "0");
}

TEST(SevenArithmetic, SubtractResultingInFewerDigits) {
    Seven s1("100");
    Seven s2("1");
    Seven result = s1.subtract(s2);
    EXPECT_STREQ(result.to_string().c_str(), "66");
}

TEST(SevenArithmetic, SubtractSmallerFromLarger) {
    Seven s1("10");
    Seven s2("20");
    Seven result = s1.subtract(s2);
    EXPECT_STREQ(result.to_string().c_str(), "0");
}

TEST(SevenComparison, IsEqual) {
    Seven s1("123");
    Seven s2("123");
    Seven s3("124");
    EXPECT_TRUE(s1.is_equal(s2));
    EXPECT_FALSE(s1.is_equal(s3));
}

TEST(SevenComparison, IsGreater) {
    Seven s1("124");
    Seven s2("123");
    Seven s3("1000");
    EXPECT_TRUE(s1.is_greater(s2));
    EXPECT_TRUE(s3.is_greater(s1));
    EXPECT_FALSE(s1.is_greater(s1));
    EXPECT_FALSE(s2.is_greater(s1));
}

TEST(SevenComparison, IsLess) {
    Seven s1("123");
    Seven s2("124");
    Seven s3("10");
    EXPECT_TRUE(s1.is_less(s2));
    EXPECT_TRUE(s3.is_less(s1));
    EXPECT_FALSE(s1.is_less(s1));
    EXPECT_FALSE(s2.is_less(s1));
}