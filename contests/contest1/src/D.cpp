/*

Найти самое популярное слово из данных без учёта регистра и найти количество его вхождений.

*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#define N constant_n

std::pair<std::string, uint32_t> TaskD([[maybe_unused]] const uint32_t N, const std::vector<std::string> &words) {
    std::vector<std::string> transformed(words.begin(), words.end());
    for (auto &word : transformed) {
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
    }
    std::map<std::string, uint32_t> dictionary;
    for (auto &word : transformed) {
        dictionary[word]++;
    }

    std::pair<std::string, uint32_t> answer;
    for (auto &[word, count] : dictionary) {
        if (count > answer.second) {
            answer = {word, count};
        }
    }

    return answer;
}

int main() {
    uint32_t N = 0;
    std::cin >> N;
    std::vector<std::string> words(N);
    for (auto &word : words) {
        std::cin >> word;
    }

    auto [word, count] = TaskD(N, words);
    std::cout << word << " " << count << std::endl;

    return 0;
}