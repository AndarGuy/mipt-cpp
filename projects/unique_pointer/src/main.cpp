#include <iostream>

#include "modules/unique_pointer/unique_pointer.hpp"

typedef struct dog {
    int legs;
} Dog;

int main() {
    const auto ptr = make_unique<std::pair<int, int>>(1, 1);
    struct Base {};
    struct Derived : Base {};
    std::cout << ptr->first << " " << ptr->second << " " << std::is_convertible_v<UniquePointer<Derived>, UniquePointer<Base>>;
    return 0;
}