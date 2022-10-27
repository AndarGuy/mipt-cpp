#include <iostream>

#include "modules/array/array.hpp"

int main() {
    Array<int, 4> arr{1, 2, 3, 4};

    std::cout << arr.size();
    return 0;
}
