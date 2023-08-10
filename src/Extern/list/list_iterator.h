#ifndef SRC_LIST_S21_LIST_ITERATORS_H
#define SRC_LIST_S21_LIST_ITERATORS_H

#include "list_double_node.h"

namespace ng {
template <class T>
class ListConstIterator;

template <class T>
class ListIterator {
 public:
  using value_type = T;
  using reference = T &;
  using pointer = T *;
  using node_pointer = DoubleNode<T> *;
  using const_iterator = ListConstIterator<T>;

 private:
  node_pointer iterator_;

 public:
  ListIterator() : iterator_(nullptr) {}
  explicit ListIterator(node_pointer node) : iterator_(node) {}
  ListIterator(const ListIterator &other_iterator)
      : iterator_(other_iterator.iterator_) {}
  ListIterator(ListIterator &&other_iterator) noexcept
      : iterator_(other_iterator.iterator_) {}
  ~ListIterator() { iterator_ = nullptr; }

  void operator=(const ListIterator &other) { iterator_ = other.iterator_; }

  void operator=(ListIterator &&other) { iterator_ = other.iterator_; }

  bool operator==(const ListIterator &other) {
    return iterator_->data() == other.iterator_->data();
  }

  bool operator!=(const ListIterator &other) {
    return iterator_ != other.iterator_;
  }

  ListIterator &operator++()  //! Prefix
  {
    iterator_ = iterator_->next();
    return *this;
  }

  ListIterator &operator++(int)  //! Postfix
  {
    auto tmp = *this;
    tmp.iterator_ = tmp.iterator_->next();
    return *this;
  }

  node_pointer base() {
    node_pointer pointer = iterator_;
    return pointer;
  }

  ListIterator operator+(int value) {
    ListIterator tmp(*this);
    return tmp += value;
  }

  ListIterator &operator+=(int value) {
    for (int i = 0; i < value; i++) iterator_ = iterator_->next();
    return *this;
  }

  ListIterator &operator--()  //! Prefix
  {
    iterator_ = iterator_->prev();
    return *this;
  }

  ListIterator &operator--(int)  //! Postfix
  {
    auto tmp = *this;
    tmp.iterator_ = tmp.iterator_->prev();
    return *this;
  }

  ListIterator operator-(int value) {
    ListIterator tmp(*this);
    return tmp -= value;
  }

  ListIterator &operator-=(int value) {
    for (int i = 0; i != value; ++i) iterator_ = iterator_->prev();
    return *this;
  }

  reference operator*() { return *(iterator_->data()); }

  node_pointer node() {
    node_pointer tmp = iterator_;
    return tmp;
  }
};

template <class T>
class ListConstIterator {
 public:
  using value_type = const T;
  using reference = const T &;
  using pointer = const T *;
  using node_pointer = DoubleNode<T> *;

 private:
  node_pointer const_iterator;

 public:
  ListConstIterator() : const_iterator(nullptr) {}
  explicit ListConstIterator(node_pointer node) : const_iterator(node) {}
  ListConstIterator(const ListConstIterator &other)
      : const_iterator(other.const_iterator) {}
  ListConstIterator(ListConstIterator &&other) noexcept
      : const_iterator(other.const_iterator) {}
  ~ListConstIterator() { const_iterator = nullptr; }

  void operator=(const ListConstIterator &other) {
    const_iterator = other.const_iterator;
  }

  void operator=(ListConstIterator &&other) {
    const_iterator = other.const_iterator;
  }

  bool operator==(const ListConstIterator &other) {
    return const_iterator->data() == other.const_iterator->data();
  }

  bool operator!=(const ListConstIterator &other) {
    return const_iterator != other.const_iterator;
  }

  ListConstIterator &operator++()  //! Prefix
  {
    const_iterator = const_iterator->next();
    return *this;
  }

  ListConstIterator &operator++(int)  //! Postfix
  {
    auto tmp = *this;
    tmp.const_iterator = tmp.const_iterator->next();
    return *this;
  }

  ListConstIterator &operator+=(int value) {
    for (int i = 0; i != value; ++i) const_iterator = const_iterator->next();
    return *this;
  }

  ListConstIterator operator+(int value) {
    ListConstIterator tmp(*this);
    return tmp += value;
  }

  ListConstIterator &operator--()  //! Prefix
  {
    const_iterator = const_iterator->prev();
    return *this;
  }

  ListConstIterator &operator--(int)  //! Postfix
  {
    auto tmp = *this;
    tmp.const_iterator = tmp.const_iterator->prev();
    return *this;
  }

  ListConstIterator &operator-=(int value) {
    for (int i = 0; i != value; ++i) const_iterator = const_iterator->prev();
    return *this;
  }

  ListConstIterator operator-(int value) {
    ListConstIterator tmp(*this);
    return tmp -= value;
  }

  reference operator*() { return *(const_iterator->data()); }
  node_pointer node() {
    node_pointer tmp = const_iterator;
    return tmp;
  }
};
}  // namespace s21

#endif  // !SRC_LIST_S21_LIST_ITERATORS_H
