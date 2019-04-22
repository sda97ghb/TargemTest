#pragma once

#include <iostream>

namespace utils {
    class ConsoleLog {
    public:
        template <typename T>
        static void d(T value) {
            std::cout << value << std::endl;
        }
    };

    class DisabledLog {
    public:
        template <typename T>
        static void d(T) {}
    };

//    using Log = ConsoleLog; // Вывод лога в консоль
    using Log = DisabledLog; // Отключение вывод лога
}
