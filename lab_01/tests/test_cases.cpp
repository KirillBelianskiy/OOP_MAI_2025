#include <gtest/gtest.h>
#include "../src/function.h"

TEST(CalculateSumRangeTest, HandlesExampleRange) {
    EXPECT_EQ(11, calculate_sum_range(2, 7));
}

TEST(CalculateSumRangeTest, HandlesSingleNumberRange) {
    EXPECT_EQ(2, calculate_sum_range(3, 3));
    EXPECT_EQ(1, calculate_sum_range(8, 8));
}

TEST(CalculateSumRangeTest, ThrowsExceptionOnInvalidInput) {
    EXPECT_THROW(calculate_sum_range(10, 5), std::invalid_argument);
    EXPECT_THROW(calculate_sum_range(-5, 2), std::invalid_argument);
}

TEST(CalculateSumRangeTest, RangeIncludingZero) {
    EXPECT_EQ(2, calculate_sum_range(0, 2));
}

TEST(CalculateSumRangeTest, RangeIsOnlyZero) {
    EXPECT_EQ(0, calculate_sum_range(0, 0));
}

TEST(CalculateSumRangeTest, RangeWithPowersOfTwo) {
    EXPECT_EQ(4, calculate_sum_range(7, 8));
}

TEST(CalculateSumRangeTest, RangeWithAllBitsSet) {
    EXPECT_EQ(7, calculate_sum_range(14, 15));
}

TEST(CalculateSumRangeTest, LargerRange) {
    EXPECT_EQ(32, calculate_sum_range(0, 15));
}