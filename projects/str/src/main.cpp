#include <iostream>
#include <typeinfo>

#include "modules/string/string.hpp"

// auto test_data = GENERATE(std::make_tuple(/*lhs=*/"a", /*rhs=*/"b"), std::make_tuple(/*lhs=*/"aa", /*rhs=*/"b"),
//                           std::make_tuple(/*lhs=*/"a", /*rhs=*/"bb"), std::make_tuple(/*lhs=*/"aa", /*rhs=*/"bb"),
//                           std::make_tuple(/*lhs=*/"", /*rhs=*/"a"), std::make_tuple(/*lhs=*/"", /*rhs=*/"b"));
int main() {
    String s;
    String &ss = s;
    ss += "";
    std::cout << typeid(s).name();
}
