#include <cstdlib>
#include <iostream>

template <typename T>
class WeakPointer;

template <typename T>
class SharedPointer {
   private:
    struct Block {
        /// @brief Хранимый объект.
        T *object = nullptr;
        /// @brief Кол-во ссылок на сильные указатели.
        size_t shared_references;
        /// @brief Кол-во ссылок на слабые указатели.
        size_t weak_references;
    } *control_block = nullptr;

    friend class WeakPointer<T>;

   public:
    /// @brief Конструктор по умолчанию (создает нулевой указатель).
    SharedPointer() = default;

    /// @brief Конструктор от указателя (сохраняет указатель на владеемый объект).
    /// @param pointer Указатель на владеемый объект.
    SharedPointer(T *pointer) noexcept : control_block(new Block) {
        this->control_block->object = pointer;
        this->control_block->shared_references = pointer ? 1 : 0;
        this->control_block->weak_references = 0;
    }

    /// @brief Конструктор копирования.
    /// @param other Копируемый объект.
    SharedPointer(const SharedPointer &other) noexcept : control_block(other.control_block) {
        ++this->control_block->shared_references;
    }

    /// @brief Конструктор перемещения.
    /// @param other Куда перемещается объект.
    SharedPointer(SharedPointer &&other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    /// @brief Конструктор от `WeakPtr`, который работает аналогично методу `Lock()`, но в случае `Expired() == true` должно бросаться исключение `std::bad_weak_ptr`.
    /// @param other
    SharedPointer(const WeakPointer<T> &other) : control_block(other.control_block) {
        if (other.expired()) throw std::bad_weak_ptr();
        if (this->control_block) this->control_block->shared_references++;
    }

    /// @brief Должны быть поддержаны разрешённые конверсии (например от ребёнка к родителю).
    /// @tparam V Тип присваеваемого указателя.
    /// @param other Присваеваемый указатель.
    template <typename V>
    SharedPointer(const SharedPointer<V> &&other) : control_block(other.control_block) {
        if (!std::is_convertible_v<V, T>) throw std::bad_cast();
    }

    /// @brief Деструктор.
    ~SharedPointer() {
        if (this->control_block == nullptr) return;

        if (this->control_block->shared_references > 0) {
            --this->control_block->shared_references;
            return;
        }

        if (this->control_block->weak_references == 0) {
            delete this->control_block->object;
            delete this->control_block;
            return;
        }
    }

    /// @brief Копирующее присваивание.
    /// @param other Копируемый объект.
    SharedPointer &operator=(const SharedPointer &other) noexcept {
        if (*this == other) return *this;
        if (this->control_block) this->control_block->shared_references--;
        this->control_block = other.control_block;
        if (this->control_block) this->control_block->shared_references++;
        return *this;
    }

    /// @brief Переместительное присваивание.
    /// @param other Перемещаемый объект.
    SharedPointer &operator=(SharedPointer &&other) noexcept {
        if (*this == other) return *this;
        if (this->control_block) this->control_block->shared_references--;
        this->control_block = std::move(other.control_block);
        other.control_block = nullptr;
        return *this;
    }

    /// @brief Метод `Swap(UniquePtr&)`.
    void swap(SharedPointer &other) {
        std::swap(this->control_block, other.control_block);
    }

    /// @brief Метод `Reset(T* ptr = nullptr)`, меняет указатель, которым владеет объект.
    /// @param pointer Указатель, которым владеет объект.
    void reset(T *pointer = nullptr) {
        if (this->control_block) this->control_block->shared_references--;
        this->control_block = new Block;
        this->control_block->object = pointer;
        this->control_block->shared_references = pointer ? 1 : 0;
        this->control_block->weak_references = 0;
    }

    /// @brief Метод `UseCount()`, возвращающий число "сильных" ссылок на объект.
    /// @return Число "сильных" ссылок на объект.
    size_t use_count() const {
        if (!this->control_block) return 0;
        return this->control_block->shared_references;
    }

    /// @brief Метод `Get()`, возвращающий указатель на владеемый объект.
    T *get() const {
        if (!this->control_block) return nullptr;
        return this->control_block->object;
    }

    /// @brief Оператор разыменовывания `operator*`.
    T &operator*() const {
        return *this->control_block->object;
    }

    /// @brief Оператор "стрелочка" `operator->`.
    T *operator->() const { return this->get(); }

    /// @brief Оператор приведения к `bool` (`operator bool`).
    operator bool() const {
        return this->control_block && this->control_block->shared_references > 0;
    }

    bool operator==(const SharedPointer &other) const {
        return this->control_block == other.control_block;
    }
};

/// @brief Шаблонный класс `WeakPtr`.
/// @tparam T Объект на который ссылается указатель.
template <typename T>
class WeakPointer {
   public:
    /// @brief Конструктор по умолчанию (создает нулевой указатель).
    WeakPointer() = default;

    /// @brief Конструктор копирования.
    /// @param other Копируемый объект.
    WeakPointer(const WeakPointer &other) noexcept : control_block(other.control_block) {
        if (this->control_block) this->control_block->weak_references++;
    }

    WeakPointer(const SharedPointer<T> &other) noexcept : control_block(other.control_block) {
        if (this->control_block) other.control_block->weak_references++;
    }

    /// @brief Копирующее присваивание.
    /// @param other Копируемый объект.
    WeakPointer &operator=(const WeakPointer &other) noexcept {
        this->control_block = other.control_block;
        if (this->control_block) this->control_block->weak_references++;
        return *this;
    }

    /// @brief Конструктор перемещения.
    /// @param other Куда перемещается объект.
    WeakPointer(WeakPointer &&other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    /// @brief Должны быть поддержаны разрешённые конверсии (например от ребёнка к родителю).
    /// @tparam V Тип присваеваемого указателя.
    /// @param other Присваеваемый указатель.
    template <typename V>
    WeakPointer(const WeakPointer<V> &&other) {
        if (std::is_convertible_v<V, T>) *this = (WeakPointer &&) other;
    }

    void swap(WeakPointer<T> &other) {
        std::swap(this->control_block, other.control_block);
    }

    void reset() {
        if (this->control_block) this->control_block->weak_references--;
        this->control_block = nullptr;
    }

    bool expired() const {
        return !this->control_block || this->control_block->shared_references == 0;
    }

    SharedPointer<T> lock() const {
        if (this->expired()) return nullptr;
        SharedPointer<T> shared;
        shared.control_block = this->control_block;
        shared.control_block->shared_references++;
        return shared;
    }

    size_t use_count() const {
        if (!this->control_block) return 0;
        return this->control_block->shared_references;
    }

   private:
    struct SharedPointer<T>::Block *control_block = nullptr;

    friend class SharedPointer<T>;
};

/// @brief Дополнительно необходимо реализовать внешнюю шаблонную функцию `MakeShared`, принимающую произвольное число параметров и возвращающую `SharedPtr` на объект созданный с помощью данных параметров конструктора.
template <class T, typename... Args>
SharedPointer<T> make_shared(Args... args) {
    T *object = new T(args...);
    return SharedPointer<T>(object);
}