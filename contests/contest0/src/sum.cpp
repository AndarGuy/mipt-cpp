#include <math.h>

#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T>
T summ_of_numbers(T x, T y) {
    return x + y;
}

int main() {
    cout << summ_of_numbers(1, 2);
}