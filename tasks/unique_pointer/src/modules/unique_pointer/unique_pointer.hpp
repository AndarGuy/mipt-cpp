#include <iostream>

template <typename T>
class UniquePointer {
   public:
    /// @brief Конструктор по умолчанию (создает нулевой указатель).
    UniquePointer() = default;

    /// @brief Конструктор от указателя (сохраняет указатель на объект).
    /// @param ptr Указатель на объект
    UniquePointer(T *ptr) noexcept : UniquePointer() {
        this->pointer = ptr;
    }

    /// @brief Конструктор копирования и копирующее присваивание
    /// должны быть явно запрещены.
    UniquePointer(const UniquePointer &other) = delete;
    /// @brief Конструктор копирования и копирующее присваивание
    /// должны быть явно запрещены.
    UniquePointer &operator=(const UniquePointer &other) = delete;

    template <typename V>
    UniquePointer(const UniquePointer<V> &&other) {
        std::cout << std::is_convertible_v<V, T> << std::endl;
        if (std::is_convertible_v<V, T>) *this = (UniquePointer &&) other;
    }

    /// @brief Перемещающий конструктор и перемещающее присваивание
    /// должны передавать владение объектом.
    UniquePointer(const UniquePointer &&other) noexcept : UniquePointer() {
        *this = (UniquePointer &&) other;
    }

    /// @brief Перемещающий конструктор и перемещающее присваивание
    /// должны передавать владение объектом.
    UniquePointer &operator=(UniquePointer &&other) noexcept {
        this->pointer = std::move(other.pointer);
        other.reset();
        return *this;
    }

    /// @brief Метод `Release()`, который отлучает класс от владения
    /// текущим ресурсом и возвращает указатель на него.
    const T *release() {
        T *temp = this->pointer;
        this->reset();
        return temp;
    }

    /// @brief Метод `Reset(T* ptr = nullptr)`, меняет указатель,
    /// которым владеет объект (старый ресурс удаляется).
    void reset(T *ptr = nullptr) {
        this->pointer = ptr;
    }

    /// @brief Метод `Swap(UniquePtr&)`.
    void swap(UniquePointer &other) {
        std::swap(this->pointer, other.pointer);
    }

    /// @brief Метод `Get()`, возвращающий указатель на объект.
    T *get() const {
        return this->pointer;
    }

    /// @brief Оператор разыменовывания `operator*`.
    T &operator*() const {
        return *this->pointer;
    }

    /// @brief Оператор "стрелочка" `operator->`.
    T *operator->() const { return this->pointer; }

    /// @brief Оператор приведения к `bool` (`operator bool`).
    operator bool() const {
        return this->pointer != nullptr;
    }

   private:
    T *pointer = nullptr;
};

/// @brief Реализуйте внешнюю шаблонную функцию `MakeUnique`,
/// принимающую произвольное число параметров и возвращающую `UniquePtr`
/// на объект созданный с помощью данных параметров конструктора.
template <class T, typename... Args>
UniquePointer<T> make_unique(Args... args) {
    T *object = new T(args...);
    return UniquePointer<T>(object);
}