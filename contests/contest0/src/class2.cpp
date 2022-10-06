/*

Написать функцию int isEqual(Time a, int min), которая сравнивает время таймера с момента запуска и число минут min и возвращает 1, если число минут с момента запуска равно min, если не равны - возвращает 0.

*/

class Time {
   public:
    int hour;
    int min;
};

int isEqual(Time a, int min) {
    return a.hour * 60 + a.min == min;
}

int main() {
}