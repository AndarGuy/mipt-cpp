/*

Линейка 1

На линейке отмечены сантиметры и миллиметры.
Сантиметров на линейке не больше 300.
Лист бумаги в клетку.
2 клетки = 1 см.

*/

#include <cstdlib>
#include <iostream>

using namespace std;

class Lin {
   public:
    int cm;  // сантиметры
    int mm;  // миллиметры
};

// печатает длину в сантиметрах и миллиметрах.
void printLin(Lin a) {
    cout << a.cm << " " << a.mm;
}

// вычисляет размер листа бумаги в сантиметрах и миллиметрах. Лист бумаги измерен в клеточках.

Lin convertToLin(int cells) {
    Lin linear;
    linear.cm = cells / 2;
    linear.mm = cells % 2 ? 5 : 0;
    return linear;
}

int main() {
    int cells;

    cin >> cells;

    printLin(convertToLin(cells));
}