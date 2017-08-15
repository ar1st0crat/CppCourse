#include <iostream>
#include "sequential.h"
#include "associative.h"

int main()
{
    std::cout << "Sequential containers:" << std::endl << std::endl;
    sequential_containers_demo();

    std::cout << std::endl << "Associative containers:" << std::endl << std::endl;
    associative_containers_demo();

    return 0;
}
