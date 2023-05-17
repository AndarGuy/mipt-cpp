#include <cstdlib>
#include <iostream>

#define SharedPtr SharedPointer
#define WeakPtr WeakPointer
#define Lock lock
#define Expired expired
#define Reset reset
#define Swap swap
#define UseCount use_count
#define Get get
#define MakeShared make_shared

template <typename T>
class WeakPointer;

template <typename T>
class SharedPointer {
 private:
  struct Block {
    /// @brief Хранимый объект.
    T* object = nullptr;
    /// @brief Кол-во ссылок на сильные указатели.
    size_t shared_references;
    /// @brief Кол-во ссылок на слабые указатели.
    size_t weak_references;
  }* control_block = nullptr;

  friend class WeakPointer<T>;

 public:
  /// @brief Конструктор по умолчанию (создает нулевой указатель).
  SharedPointer() = default;

  /// @brief Конструктор от указателя (сохраняет указатель на владеемый объект).
  /// @param pointer Указатель на владеемый объект.
  SharedPointer(T* pointer) noexcept {
    if (pointer) {
      control_block = new Block;
      control_block->object = pointer;
      control_block->shared_references = 1;
      control_block->weak_references = 0;
    }
  }

  /// @brief Конструктор копирования.
  /// @param other Копируемый объект.
  SharedPointer(const SharedPointer& other) noexcept : control_block(other.control_block) {
    ++control_block->shared_references;
  }

  /// @brief Конструктор перемещения.
  /// @param other Куда перемещается объект.
  SharedPointer(SharedPointer&& other) noexcept : control_block(other.control_block) {
    other.control_block = nullptr;
  }

  /// @brief Конструктор от `WeakPtr`, который работает аналогично методу `Lock()`, но в случае `Expired() == true`
  /// должно бросаться исключение `std::bad_weak_ptr`.
  /// @param other
  SharedPointer(const WeakPointer<T>& other) : control_block(other.control_block) {
    if (other.expired())
      throw std::bad_weak_ptr();
    if (control_block)
      control_block->shared_references++;
  }

  /// @brief Должны быть поддержаны разрешённые конверсии (например от ребёнка к родителю).
  /// @tparam V Тип присваеваемого указателя.
  /// @param other Присваеваемый указатель.
  template <typename V>
  SharedPointer(SharedPointer<V>&& other) : control_block(std::exchange(other.control_block, nullptr)) {
  }

  /// @brief Деструктор.
  ~SharedPointer() {
    reset();
  }

  /// @brief Копирующее присваивание.
  /// @param other Копируемый объект.
  SharedPointer& operator=(const SharedPointer& other) noexcept {
    if (this == &other)
      return *this;
    reset();
    control_block = other.control_block;
    if (control_block)
      control_block->shared_references++;
    return *this;
  }

  /// @brief Переместительное присваивание.
  /// @param other Перемещаемый объект.
  SharedPointer& operator=(SharedPointer&& other) noexcept {
    if (this == &other)
      return *this;
    reset();
    control_block = std::move(other.control_block);
    other.control_block = nullptr;
    return *this;
  }

  /// @brief Метод `Swap(UniquePtr&)`.
  void swap(SharedPointer& other) {
    if (this == &other)
      return;
    std::swap(control_block, other.control_block);
  }

  /// @brief Метод `Reset(T* ptr = nullptr)`, меняет указатель, которым владеет объект.
  /// @param pointer Указатель, которым владеет объект.
  void reset(T* pointer = nullptr) {
    if (control_block) {
      if (--control_block->shared_references <= 0) {
        if (control_block->weak_references <= 0) {
          delete control_block->object;
          delete control_block;
        }
      }
    }

    control_block = nullptr;

    if (pointer) {
      control_block = new Block;
      control_block->object = pointer;
      control_block->shared_references = 1;
      control_block->weak_references = 0;
    }
  }

  /// @brief Метод `UseCount()`, возвращающий число "сильных" ссылок на объект.
  /// @return Число "сильных" ссылок на объект.
  size_t use_count() const {
    if (!control_block)
      return 0;
    return control_block->shared_references;
  }

  /// @brief Метод `Get()`, возвращающий указатель на владеемый объект.
  T* get() const {
    if (!control_block)
      return nullptr;
    return control_block->object;
  }

  /// @brief Оператор разыменовывания `operator*`.
  T& operator*() const {
    return *control_block->object;
  }

  /// @brief Оператор "стрелочка" `operator->`.
  T* operator->() const {
    return get();
  }

  /// @brief Оператор приведения к `bool` (`operator bool`).
  operator bool() const {
    return control_block && control_block->shared_references > 0;
  }

  bool operator==(const SharedPointer& other) const {
    return control_block == other.control_block;
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
  WeakPointer(const WeakPointer& other) noexcept : control_block(other.control_block) {
    if (control_block)
      control_block->weak_references++;
  }

  /// @brief Деструктор.
  ~WeakPointer() {
    reset();
  }

  WeakPointer(const SharedPointer<T>& other) noexcept : control_block(other.control_block) {
    if (control_block)
      other.control_block->weak_references++;
  }

  /// @brief Копирующее присваивание.
  /// @param other Копируемый объект.
  WeakPointer& operator=(const WeakPointer& other) noexcept {
    if (this == &other)
      return *this;
    reset();
    control_block = other.control_block;
    if (control_block)
      control_block->weak_references++;
    return *this;
  }

  /// @brief Конструктор перемещения.
  /// @param other Куда перемещается объект.
  WeakPointer(WeakPointer&& other) noexcept : control_block(other.control_block) {
    other.control_block = nullptr;
  }

  /// @brief Должны быть поддержаны разрешённые конверсии (например от ребёнка к родителю).
  /// @tparam V Тип присваеваемого указателя.
  /// @param other Присваеваемый указатель.
  template <typename V>
  WeakPointer(WeakPointer<V>&& other) : control_block(std::exchange(other.control_block, nullptr)) {
    // Replaced with initializer_list
  }

  void swap(WeakPointer<T>& other) {
    if (this == &other)
      return;
    std::swap(control_block, other.control_block);
  }

  void reset() {
    if (control_block) {
      if (--control_block->weak_references <= 0) {
        if (control_block->shared_references <= 0) {
          delete control_block->object;
          delete control_block;
        }
      }
    }

    control_block = nullptr;
  }

  bool expired() const {
    return !control_block || control_block->shared_references == 0;
  }

  SharedPointer<T> lock() const {
    if (expired())
      return nullptr;
    SharedPointer<T> shared;
    shared.control_block = control_block;
    shared.control_block->shared_references++;
    return shared;
  }

  size_t use_count() const {
    if (!control_block)
      return 0;
    return control_block->shared_references;
  }

 private:
  struct SharedPointer<T>::Block* control_block = nullptr;

  friend class SharedPointer<T>;
};

/// @brief Дополнительно необходимо реализовать внешнюю шаблонную функцию `MakeShared`, принимающую произвольное число
/// параметров и возвращающую `SharedPtr` на объект созданный с помощью данных параметров конструктора.
template <class T, typename... Args>
SharedPointer<T> make_shared(Args... args) {
  T* object = new T(args...);
  return SharedPointer<T>(object);
}