### SharedPtr

#### `std::shared_ptr` (C++11)

Шаблонный класс `std::shared_ptr` предоставляет интерфейс указателя на данные в динамической области с автоматическим
контролем своевременного выделения и удаления ресурсов. `std::shared_ptr` реализует
семантику *разделяемого владения ресурсом*, что означает, что у одного ресурса может быть несколько равноправных
владельцев. При этом гарантируется, что ресурс не будет освобожден пока существует хотя бы один его владелец (хотя бы
один объект `std::shared_ptr` указывает на ресурс).

Однако при большом желании можно допустить утечки памяти *зацикливая* `std::shared_ptr`. Для таких целей существуют 
"слабые указатели" `std::weak_ptr`, которые не считаются полноценными владельцами ресурса, но из них при необходимости
можно получить "сильный указатель" `std::shared_ptr` на объект, если тот еще не удален.

#### Задание

Реализуйте шаблонные классы `SharedPtr` и `WeakPtr` - упрощенные аналоги `std::shared_ptr` и `std::weak_ptr`
#### Детали реализации

Шаблонный класс `SharedPtr` должен поддерживать:
* Конструктор по умолчанию (создает нулевой указатель).
* Конструктор от указателя (сохраняет указатель на владеемый объект).
* Конструктор копирования и копирующее присваивание (создают новую ссылку на тот же объект).
* Конструктор от `WeakPtr`, который работает аналогично методу `Lock()`, но в случае
`Expired() == true` должно бросаться исключение `std::bad_weak_ptr`.
* Перемещающий конструктор и перемещающее присваивание должны передавать владение объектом.
* Должны быть поддержаны разрешённые конверсии (например от ребёнка к родителю)
* Метод `Reset(T* ptr = nullptr)`, меняет указатель, которым владеет объект.
* Метод `Swap(SharedPtr<T>&)`.
* Метод `Get()`, возвращающий указатель на владеемый объект.
* Метод `UseCount()`, возвращающий число "сильных" ссылок на объект.
* Оператор разыменовывания `operator*`.
* Оператор "стрелочка" `operator->`.
* Оператор приведения к `bool` (`operator bool`).


Шаблонный класс `WeakPtr` должен поддерживать:
* Аналогичные конструкторов (по умолчанию, копирования, перемещения) и операторов присваивания.
* Должны быть поддержаны разрешённые конверсии (например от ребёнка к родителю)
* Конструктор от `SharedPtr` (увеличивает число "слабых" ссылок)
* Метод `Swap(WeakPtr<T>&)`
* Метод `Reset()`, отвязывающего указатель от объекта
* Метод `UseCount()`, возвращающего число "сильных" ссылок на объект
* Метод `Expired()`, возвращающий `true`, если сильных ссылок на объект уже нет (объект удален)
* Метод `Lock()`, возвращающий `SharedPtr` на объект (если `Expired() == true`, то возвращается пустой указатель)


Дополнительно необходимо реализовать внешнюю шаблонную функцию `MakeShared`, принимающую произвольное число параметров и
возвращающую `SharedPtr` на объект созданный с помощью данных параметров конструктора.
