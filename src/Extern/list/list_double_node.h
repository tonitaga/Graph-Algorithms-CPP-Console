#ifndef SRC_LIST_S21_LIST_DOUBLE_NODE_H
#define SRC_LIST_S21_LIST_DOUBLE_NODE_H

#include <iostream>

namespace ng {
template <class T>
class DoubleNode {
 private:
  DoubleNode<T> *next_;
  DoubleNode<T> *prev_;
  T *data_;

 public:
  DoubleNode() : next_(nullptr), prev_(nullptr), data_() {}
  explicit DoubleNode(const T &value) : next_(nullptr), prev_(nullptr), data_(value) {}
  explicit DoubleNode(T &&value)
      : next_(nullptr), prev_(nullptr), data_(std::move(value)) {}
  DoubleNode(const DoubleNode &other)
      : next_(other.next_), prev_(other.prev_), data_(other.data_) {}
  ~DoubleNode() = default;

  DoubleNode &operator=(const DoubleNode &other) {
    next_ = other.next_;
    prev_ = other.prev_;
    data_ = other.data_;
    return *this;
  }

  DoubleNode *&next() { return next_; }
  DoubleNode *&prev() { return prev_; }
  T *&data() { return data_; }

  void connect() {
    if (prev_) prev_->next() = next_;
    if (next_) next_->prev() = prev_;
  }

  void insert_before(DoubleNode *node) {
    if (node->prev_) {
      node->prev_->next_ = this;
      prev_ = node->prev_;
    }
    node->prev_ = this;
    next_ = node;
  }
};

}  // namespace s21

#endif  // !SRC_LIST_S21_LIST_DOUBLE_NODE_H