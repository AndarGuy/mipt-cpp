#include <iostream>

#include "modules/abs/abs.hpp"
#include "modules/complex/complex.hpp"

using namespace std;

int main() {
    Complex complex(1.0, 1.0);

    Complex minus = -complex;

    cout << minus.getReal() << " " << complex.getReal();

    return 0;
}
