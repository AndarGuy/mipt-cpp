/*

Необходимо выяснить количество неповторяющихся чисел в последовательности.

*/

#include <iostream>
#include <vector>
#include <stack>
#include <set>

#define N constant_n

int32_t TaskC([[maybe_unused]] const uint32_t N, const std::vector<int32_t> &numbers) {
    std::set<int32_t> unique(numbers.begin(), numbers.end());
    return unique.size();
}

int main() {
    uint32_t N = 0;
    std::cin >> N;
    std::vector<int32_t> numbers(N);
    for (auto &number : numbers) {
        std::cin >> number;
    }

    auto answer = TaskC(N, numbers);
    std::cout << answer << std::endl;

    return 0;
}