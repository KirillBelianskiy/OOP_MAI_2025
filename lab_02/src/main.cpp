#include "classes.h"
#include <iostream>
#include <string>
#include <stdexcept>

int main()
{
    try
    {
        std::string str;
        std::cin >> str;

        Seven s1(str);
        Seven s2({1, 2, 4});
        Seven s3 = s1.subtract(s2);

        std::cout << s3.to_string() << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Invalid input: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
