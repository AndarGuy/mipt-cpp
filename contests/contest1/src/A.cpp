/*

Вывести через пробел данные слова, приведённые к нижнему регистру, в обратном лексикографическом порядке и без
повторений.

*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cctype>
#include <set>

#define N constant_n

std::vector<std::string> A([[maybe_unused]] const uint32_t N, const std::vector<std::string> &words) {
    std::vector<std::string> transformed(words.begin(), words.end());
    for (auto &word : transformed) {
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
    }
    std::sort(transformed.begin(), transformed.end());
    std::set<std::string> unique(transformed.begin(), transformed.end());
    std::vector<std::string> answer(unique.rbegin(), unique.rend());
    return answer;
}

int main() {
    uint32_t N = 0;
    std::cin >> N;
    std::vector<std::string> words(N);
    for (auto &word : words) {
        std::cin >> word;
    }

    auto answer = A(N, words);
    for (auto &word : answer) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}