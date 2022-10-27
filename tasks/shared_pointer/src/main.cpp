#include <iostream>

#include "modules/shared_pointer/shared_pointer.hpp"

int main() {
    // {
    //     auto raw_ptr = new int;
    //     SharedPointer<int> first_shared_ptr(raw_ptr);
    //     SharedPointer<int> second_shared_ptr;
    //     second_shared_ptr = first_shared_ptr;
    //     second_shared_ptr = SharedPointer<int>();

    //     std::cout << first_shared_ptr.use_count() << std::endl;
    // }

    // {
    //     auto raw_ptr = new int;
    //     SharedPointer<int> first_shared_ptr(raw_ptr);
    //     auto other_raw_ptr = new int;
    //     first_shared_ptr = SharedPointer(other_raw_ptr);

    //     std::cout << first_shared_ptr.use_count() << std::endl;
    // }

    // {  // reset empty
    //     SharedPointer<int> a;
    //     a.reset();
    //     std::cout << (a.use_count() == 0);

    //     a.reset(new int);
    //     std::cout << (a.use_count() == 1);

    //     a.reset();
    //     std::cout << (a.use_count() == 0);
    // }

    {
        {  // reset shared
            auto ptr1 = new int(5);
            SharedPointer<int> a(ptr1);
            SharedPointer<int> b = a;

            std::cout << (a.use_count()) << std::endl;

            b.reset();
            std::cout << (a.use_count() == 1) << std::endl;
            std::cout << (a.get() == ptr1) << std::endl;
            std::cout << (b.use_count() == 0) << std::endl;
            std::cout << (b.get() == nullptr) << std::endl;

            b = a;
            auto ptr2 = new int(7);
            a.reset(ptr2);
            std::cout << (a.use_count() == 1) << std::endl;
            std::cout << (a.get() == ptr2) << std::endl;
            std::cout << (b.use_count() == 1) << std::endl;
            std::cout << (b.get() == ptr1) << std::endl;
        }
    }
    return 0;
}