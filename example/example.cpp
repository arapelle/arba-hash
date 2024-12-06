#include <arba/hash/hash.hpp>
#include <arba/hash/version.hpp>
#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << arba::hash::project_name() << std::endl;
    std::cout << "EXIT SUCCESS" << std::endl;
    return EXIT_SUCCESS;
}
