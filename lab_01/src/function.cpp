#include "function.h"

int counting_units(int n)
{
    int count = 0;

    while (n > 0)
    {
        if (n & 0b1)
        {
            ++count;
        }

        n >>= 1;
    }
    return count;
}

int calculate_sum_range(int start, int end)
{
    if (start < 0 || end < 0 || start > end) return -1;

    int res = 0;
    for (int i = start; i <= end; i++) res += counting_units(i);
    return res;
}
