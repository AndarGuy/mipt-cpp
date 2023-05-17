/*

Дана строка, состоящая из строчных и заглавных латинских букв, цифр и знаков “:”, “/” и “.”. Известно, что строка
представляет собой корректно сформированный URL с указанием протокола. Ваша задача — определить этот протокол.

*/

#include <iostream>
#include <regex>

char transformation(const char c) {
    return std::tolower(c);
}

int main() {
    std::regex pattern("[0-9A-Za-z]{2,10}://");
    std::string string;
    std::getline(std::cin, string);
    std::smatch answer;
    if (std::regex_search(string, answer, pattern)) {
        std::string result = answer[0];
        std::transform(result.begin(), result.end(), result.begin(), transformation);
        for (auto iterator = result.begin(); iterator != std::find(result.begin(), result.end(), ':'); iterator++) {
            std::cout << *iterator;
        }
    }
}