/*

Прямоугольник и квадрат

Треугольник задан координатами своих вершин.

Треугольник a равен треугольнику b, если его можно переместить, при необходимости повернуть и наложить на треугольник b.

*/

#include <math.h>

#include <cstdlib>
#include <iostream>

using namespace std;

// Класс координат
class Coord {
   public:
    int x;
    int y;
};

// Класс треугольника
class Triangle {
   public:
    Coord p1, p2, p3;
};

// вспомогательная функция - считывает со стандартного потока ввода координаты точки и возвращает их через класс Coord.
Coord getPoint() {
    Coord coordinate;
    cin >> coordinate.x >> coordinate.y;
    return coordinate;
}

// получает данные треугольника, т.е. считывает со стандартного потока ввода координаты вершин треугольника, заполняет структуру Triangle и возвращает её через tri
void getTri(Triangle& tri) {
    tri.p1 = getPoint();
    tri.p2 = getPoint();
    tri.p3 = getPoint();
}

// сравнивает треугольник a с b. Если они равны, возвращает 1, если нет, возвращает 0.
int cmp(Triangle a, Triangle b) {
    int sidesA[3], sidesB[3];
    sidesA[0] = (a.p1.x - a.p2.x) * (a.p1.x - a.p2.x) + (a.p1.y - a.p2.y) * (a.p1.y - a.p2.y);
    sidesA[1] = (a.p1.x - a.p3.x) * (a.p1.x - a.p3.x) + (a.p1.y - a.p3.y) * (a.p1.y - a.p3.y);
    sidesA[2] = (a.p3.x - a.p2.x) * (a.p3.x - a.p2.x) + (a.p3.y - a.p2.y) * (a.p3.y - a.p2.y);

    sidesB[0] = (b.p1.x - b.p2.x) * (b.p1.x - b.p2.x) + (b.p1.y - b.p2.y) * (b.p1.y - b.p2.y);
    sidesB[1] = (b.p1.x - b.p3.x) * (b.p1.x - b.p3.x) + (b.p1.y - b.p3.y) * (b.p1.y - b.p3.y);
    sidesB[2] = (b.p3.x - b.p2.x) * (b.p3.x - b.p2.x) + (b.p3.y - b.p2.y) * (b.p3.y - b.p2.y);

    return (sidesA[0] == sidesB[0] && sidesA[1] == sidesB[1] && sidesA[2] == sidesB[2]) ||
           (sidesA[0] == sidesB[1] && sidesA[1] == sidesB[2] && sidesA[2] == sidesB[0]) ||
           (sidesA[0] == sidesB[2] && sidesA[1] == sidesB[0] && sidesA[2] == sidesB[1]);
}

int main() {
    Triangle triangleA, triangleB;
    getTri(triangleA);
    getTri(triangleB);
    cout << cmp(triangleA, triangleB);
}