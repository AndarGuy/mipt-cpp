/*

Поезд отправляется в h1:m1, время в пути h2:m2. Во сколько прибывает поезд?

*/

#include <iostream>

#define N constant_n

int main() {
    std::pair<uint32_t, uint32_t> time_a, time_b;
    scanf("%u:%u", &time_a.first, &time_a.second);
    scanf("%u:%u", &time_b.first, &time_b.second);
    printf("%02d:%02d\n", (time_a.first + time_b.first + (time_a.second + time_b.second) / 60) % 24,
           (time_a.second + time_b.second) % 60);
}