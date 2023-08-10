#ifndef SRC_HELPERS_QUEUE_H_
#define SRC_HELPERS_QUEUE_H_

#include <iostream>

#include "list.h"

namespace ng {
    template <class T, class Container = ng::List<T>>
    class Queue {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;
        using container_type = Container;

    public:
        explicit Queue(const container_type &container = container_type())
                : _container(container) {}
        Queue(std::initializer_list<value_type> const &items) : _container(items) {}

        reference front() { return _container.front(); }
        const_reference front() const { return _container.front(); }

        bool empty() const noexcept { return _container.empty(); }
        size_type size() const noexcept { return _container.size(); }

        void push(const_reference value) { _container.push_back(value); }
        void push(value_type &&value) { _container.push_back(std::move(value)); }
        void pop() { _container.pop_front(); }
        void swap(Queue &other) { _container.swap(other._container); }

    private:
        container_type _container;
    };
}  // namespace s21

#endif //SRC_HELPERS_QUEUE_H_
