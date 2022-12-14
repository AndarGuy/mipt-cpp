
### String

До сих пор мы использовали только `C-строки`. Как вы могли уже заметить, работа с ними доставляет определённые неудобства:

- Они или хранятся на стеке. и тогда размер фиксирован, либо хранятся в куче, и за памятью приходится следить разработчику.
- Не хранят размер или иные характеристики, так как являются тривиальным объектом (массивом `char`), из-за чего приходится использовать функционал библиотеки `cstring`.

В стандартное библиотеке языка `C++` [есть класс](https://en.cppreference.com/w/cpp/string/basic_string) `std::string`, который инкапсулирует в себе логику всю работы со строкой, предоставляя интерфейс **"безразмерной строки**", в которой аллокации памяти происходят _"под капотом"_. Также вы получаете возможность взаимодействовать с потоками, конкатенировать строки, итерироваться по строке и прочие плюшки _"из коробки"_. При за счёт методов, которые позволяют работать с `C-строкой`, лежащей под `std::string`, можно работать и с некоторыми функциями из `cstring`.


##### Задание
В этой задаче вам предстоит написать упрощённый аналог класса `std::string`.


Реализуйте класс `String`, предоставляющий интерфейс **"безразмерной строки"**, работающей по  [мультипликативной схеме расширения](https://en.wikipedia.org/wiki/Dynamic_array#Geometric_expansion_and_amortized_cost) **с коэффициентом 2**.



* Конструктор по умолчанию - создает пустую строку
```c++
String str;
// str.Size() = 0;
// str.Capacity() = 0;
// str.Data = nullptr;
```
* Конструктор, принимающий `size` и `symbol`, - создает строку длины `size`, заполненную символами `symbol`.
```c++
String str(3, 'a');
// str == "aaa"
```
* Конструктор, принимающий массив `char` (`const char*`) и количество первых символов (`size`), которые нужно скопировать.
```c++
String str("aaa", 1);
// str == "a"
```
* Конструктор, принимающий `С-строку` (`const char*`) и создающий на ее основе строку.
* Правило "трех" (Конструктор копирования, оператор присваивания, деструктор).
* Константный и неконстантный оператор доступа по индексу  `[]`.
* Методы `Front()` и `Back()` - ссылка на первый и последний символы.
* Методы `CStr()` и `Data()` - возвращают `C-строку` (`const char*`).
* Метод `Empty()` - `true`, если строка пуста (`size` 0).
* Методы `Size()` и `Length()` - размер строки.
* Метод `Capacity()` - текущая вместимость.
* Метод `Clear()` - устанавливает размер в 0, `capacity` **не** изменяется .
* Метод `Swap(other)` - обменивает содержимое с другой строкой `other` за `O(1)`.
* Метод `PopBack()` - удаляет последний символ  (при `size == 0` `UB` - реализуйте на своё усмотрение).
* Метод `PushBack(symbol)` - добавляет символ `symbol` в конец строки (при необходимости строка расширяется).
* Операция `+=` - принимает другую строку (`String`) и приписывает ее в конец текущей.
* Метод `Resize(new_size, symbol)` - изменяет размер на `new_size`. Если вместимость не позволяет хранить столько символов, то выделяется новый буфер с вместимостью `new_size`. В случае `new_size > size` заполняет недостающие символы значением `symbol`.
* Метод `Reserve(new_capacity)` - изменяет `capacity` до `new_capacity`, если исходная вместимость меньше, и не изменяет объект иначе. `size` не изменяется.
* Метод `ShrinkToFit()` - уменьшает `capacity` до `size`.
* Оператор `+` (конкатенация строк).
* Операторы сравнения `==` и `<=>` `(spaceship)` задающие лексикографический порядок.
* Операторы  `<<` и `>>` для работы с потоками.
