#pragma once

#include <atomic>

namespace utils {
    /**
     * @brief Совместно используемые данные со счетчиком ссылок
     */
    template <typename T>
    struct SharedData {
        SharedData(T* data) :
            data(data),
            ref_count(1)
        {}

        ~SharedData() {
            delete data;
        }

        template<typename... Args>
        static SharedData<T>* create(Args... args) {
            T* data = new T(args...);
            return new SharedData<T>(data);
        }

        SharedData<T>* makeRef() {
            ++ ref_count;
            return this;
        }

        bool derefAndCheckDelete() {
            return (-- ref_count) == 0;
        }

        T* data;
        std::atomic_int ref_count;
    };
}
