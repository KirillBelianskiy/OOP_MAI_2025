#include <iostream>
#include <string>
#include "classes.h"

int main()
{
    std::string str;
    std::getline(std::cin, str);

    try
    {
        Seven s1(str);
        Seven s2({1, 2, 4});
        Seven s3 = s1.subtract(s2);
        std::cout << s3.to_string() << std::endl;
    }
    catch (InvalidInput& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (OutOfRange& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (Exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
