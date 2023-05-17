/*

Для каждого эксперимента записаны показания часов когда он начался и сколько минут длился. Отсортируйте времена
окончания экспериментов (как оно показано на часах) в порядке возрастания. Ни один эксперимент не длился более 24 часов.

*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int main() {
    uint32_t N = 0;
    std::cin >> N;

    std::vector<std::pair<uint32_t, uint32_t>> schedule(N);
    for (size_t i = 0; i < N; i++) {
        scanf("%u:%u", &schedule[i].first, &schedule[i].second);
        uint32_t add;
        std::cin >> add;
        schedule[i].second += add;
        schedule[i].first += schedule[i].second / 60;
        schedule[i].first %= 24;
        schedule[i].second %= 60;
    }
    std::sort(schedule.begin(), schedule.end());
    for (auto [hours, minutes] : schedule) {
        printf("%02d:%02d\n", hours, minutes);
    }

    return 0;
}