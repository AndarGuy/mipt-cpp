#include <any>
#include <typeindex>
#include <vector>

#define Reset reset
#define Swap swap
#define HasValue has_value
#define MakeAny make_any
#define AnyCast any_cast

class Any {
 private:
  struct Base {
    virtual std::type_index type() = 0;
    virtual Base* clone() = 0;
    virtual ~Base() {
    }
  };

  template <class T>
  struct Derived : Base {
    T object;
    Derived(const T& object) : object(object) {
    }
    Base* clone() override {
      return new Derived<T>(this->object);
    }
    std::type_index type() override {
      return std::type_index(typeid(T));
    }
  };

 public:
  Base* storage = nullptr;
  Any() = default;

  template <class T>
  Any(const T& object) : storage(new Derived<T>(object)) {
  }

  Any(const Any& any) : storage(any.storage->clone()) {
  }

  Any(Any&& any) {
    this->swap(any);
    any.storage = nullptr;
  }

  Any& operator=(const Any& any) {
    if (this->storage == any.storage)
      return *this;
    this->reset();
    this->storage = any.storage->clone();
    return *this;
  }

  Any& operator=(Any&& any) {
    if (this->storage == any.storage)
      return *this;
    this->reset();
    this->swap(any);
    return *this;
  }

  template <class T>
  Any& operator=(const T&& object) {
    this->reset();
    this->storage = new Derived<T>(object);
    return *this;
  }

  // `reset()` - обнуляет объект, делая его пустым;
  void reset() {
    delete storage;
    storage = nullptr;
  }

  // `Swap(std::any&)` - обменивает содержимое;
  void swap(Any& any) {
    std::swap(this->storage, any.storage);
  }

  // `HasValue()` - `true`, если объект не пуст, `false` иначе;
  bool has_value() const {
    return this->storage != nullptr;
  }

  ~Any() {
    this->reset();
  }

  template <class T>
  friend T any_cast(const Any& value);
};

template <class T, typename... Args>
Any make_any(Args... args) {
  T* object = new T(args...);
  return Any(object);
}

template <class T>
T any_cast(const Any& value) {
  if (!value.has_value())
    throw std::bad_any_cast();
  if (std::type_index(typeid(T)) != value.storage->type())
    throw std::bad_any_cast();
  Any::Derived<T>* link = dynamic_cast<Any::Derived<T>*>(value.storage);
  return link->object;
}