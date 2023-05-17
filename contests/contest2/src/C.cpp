/*

Некоторые скобочные структуры правильные, другие — неправильные. Ваша задача — определить правильная ли скобочная
структура.

*/

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <stack>

char Match(char bracket) {
    switch (bracket) {
        case '}':
            return '{';
        case ')':
            return '(';
        case '>':
            return '<';
        case ']':
            return '[';
    }
    return '\0';
}

int main() {
    std::stack<char> brackets;

    for (char bracket = 0; (bracket = getc(stdin)) != -1;) {
        if (bracket == '{' || bracket == '(' || bracket == '<' || bracket == '[') {
            brackets.push(bracket);
        } else {
            char pair = Match(bracket);
            if (pair == '\0') {
                continue;
            }
            if (brackets.empty()) {
                printf("NO");
                return 0;
            }
            char top = brackets.top();
            brackets.pop();
            if (pair != top) {
                printf("NO");
                return 0;
            }
        }
    }

    if (brackets.empty()) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}