/*

Дана последовательность чисел, оканчивающаяся нулём. Последовательность обрабоатывется по следующим правилам: если число
положительное оно добавляется в стек, если отрицательно и по модулю меньше значения на вершине стека - прибавляется к
числу на вершине, если больше или равно - убирает его с вершны стека (в случае когда стек пустой, отрицательное число
просто игнорируется). Необходимо определить какая будет глубина стека и какое значение окажется на его вершине.

*/

#include <iostream>
#include <vector>
#include <stack>

std::pair<int32_t, int32_t> TaskB(const std::vector<int32_t> &numbers) {
    std::stack<int32_t> stack;
    for (auto number : numbers) {
        if (number > 0) {
            stack.push(number);
        } else if (number < 0 && !stack.empty()) {
            if (-number < stack.top()) {
                stack.top() += number;
            } else {
                stack.pop();
            }
        }
    }

    return {stack.size(), stack.empty() ? -1 : stack.top()};
}

int main() {
    std::vector<int32_t> numbers;
    do {
        int32_t number;
        std::cin >> number;
        numbers.push_back(number);
    } while (numbers[numbers.size() - 1] != 0);

    std::pair<int32_t, int32_t> answer = TaskB(numbers);
    std::cout << answer.first << " " << answer.second << std::endl;

    return 0;
}