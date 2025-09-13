#include "function.h"
#include <iostream>

int main()
{

    Solution solution;
    int a, b;
    std::cin >> a >> b;
    try
    {
        std::cout << solution.calculate_sum_range(a, b) << std::endl;
    }
    catch (InvalidInput& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (Exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
