/*

Теперь Шерлок Жеглов собирает mac-адреса (шестёрки байт, разделённых двоеточием, байт записан как шестнадцатеричные
цифры)

*/

#include <iostream>
#include <regex>

int main() {
    const std::regex pattern("([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})");
    std::string string;
    while (std::cin >> string) {
        std::smatch answer;
        if (std::regex_search(string, answer, pattern)) {
            std::cout << answer[0] << '\n';
        }
    }
    return 0;
}
