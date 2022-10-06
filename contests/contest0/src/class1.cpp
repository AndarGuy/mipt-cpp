/*

Написать функцию Time add(Time a, int min), которая увеличивает время таймера на число минут min и возвращает время, которое будет показывать таймер.

*/

#include <math.h>

#include <cstdlib>
#include <iostream>
using namespace std;

class Time {
   public:
    int hour;
    int min;
};

Time add(Time a, int min) {
    int new_min = a.min + min;
    a.hour += new_min / 60;
    a.hour %= 24;
    a.min = new_min % 60;
    return a;
}

int main() {
    Time a, newtime;
    int min;

    // Получить a  из консоли
    cin >> a.hour >> a.min;

    // Получить min  из консоли
    cin >> min;
    newtime = add(a, min);
    cout << newtime.hour << ":" << newtime.min << endl;
}