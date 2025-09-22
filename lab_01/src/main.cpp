#include "function.h"
#include <iostream>

int main()
{

    int a, b;
    std::cin >> a >> b;
    try
    {
        std::cout << calculate_sum_range(a, b) << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
