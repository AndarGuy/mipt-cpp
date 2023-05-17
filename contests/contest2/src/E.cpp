/*

При анализе лога работы ransomware обнаружились IP-адреса, куда он отправлял ключи шифрования. Помогите Шерлоку Жеглову,
работающему в Роскомнадзоре, достать эти адреса. IPv4-адреса могут быть записаны как 4 десятичные числа от 0 до 255,
разделённые точками.

*/

#include <iostream>
#include <regex>

int main() {
    const std::regex pattern("([0-9]{1,3}\\.){3}[0-9]{1,3}");
    std::string string;
    while (std::cin >> string) {
        std::smatch answer;
        if (std::regex_search(string, answer, pattern)) {
            std::cout << answer[0] << '\n';
        }
    }
    return 0;
}