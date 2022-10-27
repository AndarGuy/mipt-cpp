#include <iostream>

class String {
   public:
    /// @brief Конструктор по умолчанию - создает пустую строку.
    String();

    /// @brief Конструктор копирования.
    /// @param other Строка для копирования.
    String(const String& other);

    /// @brief Деструктор.
    ~String();

    /// @brief Конструктор, принимающий `size` и `filler`, - создает строку длины `size`, заполненную символами `filler`.
    /// @param size Размер создаваемой строки.
    /// @param filler Символ заполнения строки.
    String(unsigned int size, char filler);

    String(const char* string, unsigned int slice);

    String(const char* string);

    /// @brief Получение размера текущей строки.
    /// @return Размер строки.
    unsigned int size() const;
    unsigned int length() const;

    /// @brief Получение максимальной вместимость строки.
    /// @return Максимальная вместимость строки.
    unsigned int capacity() const;

    /// @brief Получение ссылки на последний символ строки.
    /// @return Ссылка на последний символ строки.
    char& front() const;

    /// @brief Получение ссылки на первый символ строки.
    /// @return Ссылка на первый символ строки.
    char& back() const;

    /// @brief Получение c-style строку.
    /// @return Ссылка на строку.
    const char* cstring() const;

    /// @brief Получение указателя на строку.
    /// @return Указатель на строку.
    const char* data() const;

    /// @brief Проверка строки на пустоту.
    /// @return Возвращает @value true, если строка пустая, иначе – false.
    bool empty();

    /// @brief Очистить строку.
    void clear();

    /// @brief Меняется содержимым с другой строкой `other` за O(1).
    /// @param other - другая строка.
    void swap(String& other);

    /// @brief Удаляет последний символ.
    /// @return Удаленный символ.
    char pop_back();

    /// @brief добавляет символ `symbol` в конец строки (при необходимости строка расширяется).
    /// @param symbol
    void push_back(char symbol);

    /// @brief Изменяет размер на `new_size`. Если вместимость не позволяет хранить столько символов, то выделяется новый буфер с вместимостью `new_size`. В случае `new_size` > `size` заполняет недостающие символы значением `filler`.
    /// @param new_size Новый размер строки.
    /// @param filler Символ заполнения.
    void resize(unsigned int new_size, char filler);

    /// @brief Изменяет `capacity` до `new_capacity`, если исходная вместимость меньше, и не изменяет объект иначе `size` не изменяется.
    /// @param new_capacity Новый размер.
    void reserve(unsigned int new_capacity);

    /// @brief уменьшает `capacity` до `size`.
    void shrink();

    /// @brief Оператор `+` (конкатенация строк).
    /// @param left Левая строка для конкатенации.
    /// @param right Парвая строка для конкатенации.
    /// @return Результат конкатенации, новая строка.
    friend String operator+(const String& left, const String& right);

    /// @brief Операция `+=` - принимает другую строку `right` и приписывает ее в конец текущей.
    /// @param right Строка, которую нужно приписать в конец заданной.
    /// @return Результат конкатенации, исходная строка.
    String& operator+=(const String& right);

    /// @brief Оператор сравнения `==` задающие лексикографический порядок.
    /// @param left Строка А.
    /// @param right Срока Б.
    /// @return Результат сравнения двух строк.
    friend bool operator==(String const& left, String const& right);
    friend bool operator!=(String const& left, String const& right);

    /// @brief Оператор присваивания.
    /// @param other Присваеваеваемая строка.
    /// @return Присвоенная строка.
    String& operator=(const String& other);

    /// @brief Операторы  `<<` и `>>` для работы с потоками.
    /// @param os Используемый поток.
    /// @param string Строка для ввода/вовода.
    /// @return Исходный поток.
    friend std::ostream&
    operator<<(std::ostream& os, String const& string);

    /// @brief Операторы  `<<` и `>>` для работы с потоками.
    /// @param os Используемый поток.
    /// @param string Строка для ввода/вовода.
    /// @return Исходный поток.
    friend std::ostream& operator>>(std::ostream& os, String const& string);

    /// @brief Константный и неконстантный оператор доступа по индексу `index` `[]`.
    /// @param index Индекс
    /// @return Требуемый элемент.
    char& operator[](int index);
    const char& operator[](int index) const;

    /// @brief Оператор сравнения `<=>` задающий лексикографический порядок.
    /// @param left Строка А
    /// @param right Строка Б
    /// @return Число – результат сравнения.
    friend int operator<=>(const String& left, const String& right);

   private:
    /// @brief Массив для хранения символов.
    char* _string = nullptr;

    /// @brief Вместимость массива.
    unsigned int _capacity;

    /// @brief Кол-во элементов в массиве.
    unsigned int _size;

    const unsigned int EXPANSION_COEFFICIENT = 2;
};