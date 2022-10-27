#include <iostream>

#include "modules/any/any.hpp"

int main() {
    const Any any = 10;
    std::cout << (any_cast<int>(any) == 10) << std::endl;
    {
        Any other_any = any;
        std::cout << (any_cast<int>(any) == 10) << std::endl;
        std::cout << (any_cast<int>(other_any) == 10) << std::endl;
    }
    {
        Any other_any(std::move(any));
        std::cout << (any_cast<int>(other_any) == 10) << std::endl;
    }
    // Any a = 5;
    // std::cout << a.storage << std::endl;
    // a = std::string("aba");
    // std::cout << a.storage << std::endl;
    // std::cout << any_cast<std::string>(a) << std::endl;
    return 0;
}
