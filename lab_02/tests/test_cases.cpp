#include <gtest/gtest.h>
#include "../src/classes.h"

TEST(SevenConstructorTest, DefaultConstructor) {
    Seven s;
    EXPECT_EQ(s.to_string(), "0");
    EXPECT_EQ(s.get_size(), 0);
}

TEST(SevenConstructorTest, InitializerListConstructor) {
    Seven s1{1, 2, 3};
    EXPECT_EQ(s1.to_string(), "321");
    EXPECT_EQ(s1.get_size(), 3);

    Seven s2{};
    EXPECT_EQ(s2.to_string(), "0");
}

TEST(SevenConstructorTest, InitializerListThrowsOutOfRange) {
    EXPECT_THROW(Seven({1, 2, 7}), OutOfRange);
    EXPECT_THROW(Seven({9}), OutOfRange);
}

TEST(SevenConstructorTest, StringConstructor) {
    Seven s1("321");
    EXPECT_EQ(s1.to_string(), "321");
    EXPECT_EQ(s1.get_size(), 3);

    Seven s2("0");
    EXPECT_EQ(s2.to_string(), "0");
    EXPECT_EQ(s2.get_size(), 1);
    
    Seven s3("");
    EXPECT_EQ(s3.to_string(), "0");
}

TEST(SevenConstructorTest, StringConstructorThrowsInvalidInput) {
    EXPECT_THROW(Seven("12a3"), InvalidInput);
    EXPECT_THROW(Seven("-123"), InvalidInput);
    EXPECT_THROW(Seven("1273"), InvalidInput);
}

TEST(SevenConstructorTest, CopyConstructor) {
    Seven s1("12345");
    Seven s2(s1);
    EXPECT_TRUE(s1.is_equal(s2));
}

TEST(SevenConstructorTest, MoveConstructor) {
    Seven s1("12345");
    Seven s2(std::move(s1));
    
    EXPECT_EQ(s2.to_string(), "12345");
    EXPECT_EQ(s1.to_string(), "0");
    EXPECT_EQ(s1.get_size(), 0);
}

TEST(SevenAssignmentTest, CopyAssignment) {
    Seven s1("123");
    Seven s2("456");
    s2 = s1;
    EXPECT_TRUE(s1.is_equal(s2));
    
    s1 = s1;
    EXPECT_EQ(s1.to_string(), "123");
}

TEST(SevenAssignmentTest, MoveAssignment) {
    Seven s1("123");
    Seven s2("456");
    s2 = std::move(s1);

    EXPECT_EQ(s2.to_string(), "123");
    EXPECT_EQ(s1.to_string(), "0");
    EXPECT_EQ(s1.get_size(), 0);
}

TEST(SevenAdditionTest, SimpleAddition) {
    Seven s1("123");
    Seven s2("321");
    Seven result = s1.add(s2);
    EXPECT_EQ(result.to_string(), "444");
}

TEST(SevenAdditionTest, AdditionWithCarry) {
    Seven s1("123");
    Seven s2("456");
    Seven result = s1.add(s2);
    EXPECT_EQ(result.to_string(), "612");
}

TEST(SevenAdditionTest, AdditionDifferentSizes) {
    Seven s1("1234");
    Seven s2("56");
    Seven result = s1.add(s2);
    EXPECT_EQ(result.to_string(), "1323");
}

TEST(SevenAdditionTest, AdditionResultsInExtraDigit) {
    Seven s1("666");
    Seven s2("1");
    Seven result = s1.add(s2);
    EXPECT_EQ(result.to_string(), "1000");
}

TEST(SevenAdditionTest, AddToZero) {
    Seven s1("123");
    Seven s2("0");
    Seven result = s1.add(s2);
    EXPECT_EQ(result.to_string(), "123");
}

TEST(SevenSubtractionTest, SimpleSubtraction) {
    Seven s1("456");
    Seven s2("123");
    Seven result = s1.subtract(s2);
    EXPECT_EQ(result.to_string(), "333");
}

TEST(SevenSubtractionTest, SubtractionWithBorrow) {
    Seven s1("444");
    Seven s2("155");
    Seven result = s1.subtract(s2);
    EXPECT_EQ(result.to_string(), "256");
}

TEST(SevenSubtractionTest, SubtractionDifferentSizes) {
    Seven s1("1234");
    Seven s2("56");
    Seven result = s1.subtract(s2);
    EXPECT_EQ(result.to_string(), "1145");
}

TEST(SevenSubtractionTest, SubtractionResultsInFewerDigits) {
    Seven s1("1000");
    Seven s2("1");
    Seven result = s1.subtract(s2);
    EXPECT_EQ(result.to_string(), "666");

    Seven s3("123");
    Seven s4("120");
    Seven result2 = s3.subtract(s4);
    EXPECT_EQ(result2.to_string(), "3");
}

TEST(SevenSubtractionTest, SubtractToZero) {
    Seven s1("123");
    Seven s2("123");
    Seven result = s1.subtract(s2);
    EXPECT_EQ(result.to_string(), "0");
}

TEST(SevenSubtractionTest, SubtractLargerFromSmaller) {
    Seven s1("123");
    Seven s2("456");
    Seven result = s1.subtract(s2);
    EXPECT_EQ(result.to_string(), "0");
}

TEST(SevenComparisonTest, IsEqual) {
    Seven s1("123");
    Seven s2("123");
    Seven s3("124");
    Seven s4("1234");

    EXPECT_TRUE(s1.is_equal(s2));
    EXPECT_FALSE(s1.is_equal(s3));
    EXPECT_FALSE(s1.is_equal(s4));
}

TEST(SevenComparisonTest, IsGreater) {
    Seven s1("124");
    Seven s2("123");
    Seven s3("1234");

    EXPECT_TRUE(s1.is_greater(s2));
    EXPECT_FALSE(s2.is_greater(s1));
    EXPECT_TRUE(s3.is_greater(s1));
    EXPECT_FALSE(s1.is_greater(s3));
    EXPECT_FALSE(s1.is_greater(s1));
}

TEST(SevenComparisonTest, IsLess) {
    Seven s1("123");
    Seven s2("124");
    Seven s3("12");

    EXPECT_TRUE(s1.is_less(s2));
    EXPECT_FALSE(s2.is_less(s1));
    EXPECT_TRUE(s3.is_less(s1));
    EXPECT_FALSE(s1.is_less(s3));
    EXPECT_FALSE(s1.is_less(s1));
}