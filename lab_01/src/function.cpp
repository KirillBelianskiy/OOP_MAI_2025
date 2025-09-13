#include "function.h"
#include <vector>

int Solution::couting_units(int n)
{
    std::string bin_str = "";
    while (n > 0)
    {
        bin_str = std::to_string(n % 2) + bin_str;
        n /= 2;
    }
    int count = 0;
    for (int i = 0; i < bin_str.size(); i++)
    {
        count += (bin_str[i] == '1') ? 1 : 0;
    }
    return count;
}

int Solution::calculate_sum_range(int start, int end)
{
    if (start < 0 || end < 0 || start > end) throw InvalidInput("Invalid input");

    std::vector<int> v;
    for (int i = 0; i <= end - start; i++) v.push_back(couting_units(start + i));

    int res = 0;
    for (int i = 0; i <= end - start; i++) res += v[i];
    return res;
}
