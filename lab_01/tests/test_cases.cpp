#include <gtest/gtest.h>
#include "../src/function.h"

TEST(CalculateSumRangeTest, HandlesExampleRange) {
    Solution solution;
    EXPECT_EQ(11, solution.calculate_sum_range(2, 7));
}

TEST(CalculateSumRangeTest, HandlesSingleNumberRange) {
    Solution solution;
    EXPECT_EQ(2, solution.calculate_sum_range(3, 3));
    EXPECT_EQ(1, solution.calculate_sum_range(8, 8));
}

TEST(CalculateSumRangeTest, ThrowsExceptionOnInvalidInput) {
    Solution solution;
    EXPECT_THROW(solution.calculate_sum_range(10, 5), InvalidInput);
    EXPECT_THROW(solution.calculate_sum_range(-5, 2), InvalidInput);
}

TEST(CalculateSumRangeTest, RangeIncludingZero) {
    Solution solution;
    EXPECT_EQ(2, solution.calculate_sum_range(0, 2));
}

TEST(CalculateSumRangeTest, RangeIsOnlyZero) {
    Solution solution;
    EXPECT_EQ(0, solution.calculate_sum_range(0, 0));
}

TEST(CalculateSumRangeTest, RangeWithPowersOfTwo) {
    Solution solution;
    EXPECT_EQ(4, solution.calculate_sum_range(7, 8));
}

TEST(CalculateSumRangeTest, RangeWithAllBitsSet) {
    Solution solution;
    EXPECT_EQ(7, solution.calculate_sum_range(14, 15));
}

TEST(CalculateSumRangeTest, LargerRange) {
    Solution solution;
    EXPECT_EQ(32, solution.calculate_sum_range(0, 15));
}