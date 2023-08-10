#ifndef SRC_LIST_S21_LIST_REALIZATION_H
#define SRC_LIST_S21_LIST_REALIZATION_H

#include "list.h"

namespace ng {
template <typename T, typename A>
List<T, A>::List(size_type size, const T &value, const A &a)
    : size_(0), root_(nullptr), allocator_(a) {
  new_end();
  assign(size, value);
}

template <typename T, typename A>
List<T, A>::List(std::initializer_list<value_type> const &items) : List() {
  for (auto x : items) {
    push_back(x);
  }
}

template <typename T, typename A>
List<T, A>::List(const List &other) : List() {
  if (!other.empty()) {
    node_pointer it = other.root_;
    while (it != other.end_) {
      push_back(*it->data());
      it = it->next();
    }
  }
}

template <typename T, typename A>
List<T, A>::List(List &&other) noexcept
    : size_(other.size_), root_(other.root_), end_(other.end_) {
  other.root_ = nullptr;
  other.end_ = nullptr;
  other.size_ = 0u;
}

template <typename T, typename A>
List<T, A>::~List() {
  clear();
  if (end_) {
    delete_node(end_);
  }
}

template <typename T, typename A>
List<T, A> &List<T, A>::operator=(const List &other) {
  clear();
  end_ = new_node(value_type());
  for (auto it = other.cbegin(); it != other.cend(); ++it) {
    push_back(*it);
  }
  return *this;
}

template <typename T, typename A>
List<T, A> &List<T, A>::operator=(List &&other) noexcept {
  root_ = other.root_;
  end_ = other.end_;
  size_ = other.size_;
  other.root_ = other.end_ = nullptr;
  other.size_ = 0u;
  return *this;
}

template <typename T, typename A>
void List<T, A>::assign(size_type count, const_reference value) {
  for (size_type i = 0; i != count; ++i) {
    push_back(value);
  }
}

template <typename T, typename A>
void List<T, A>::assign(std::initializer_list<value_type> const &items) {
  for (auto x : items) {
    push_back(x);
  }
}

template <typename T, typename A>
T &List<T, A>::back() {
  if (size_ >= 1u) {
    return *(end_->prev()->data());
  } else {
    return *(end_->data());
  }
}

template <typename T, typename A>
const T &List<T, A>::back() const {
  if (size_ >= 1u) {
    return *(end_->prev()->data());
  } else {
    return *(end_->data());
  }
}

template <typename T, typename A>
void List<T, A>::clear() {
  if (size_ == 0u) return;
  while (root_) {
    end_ = root_->next();
    delete_node(root_);
    root_ = end_;
  }
  size_ = 0u;
  root_ = nullptr;
}

template <typename T, typename A>
void List<T, A>::push_back(const_reference value) {
  node_pointer newnode = new_node(value);
  newnode->insert_before(end_);
  if (size_ == 0u) root_ = newnode;
  ++size_;
}

template <typename T, typename A>
void List<T, A>::push_back(value_type &&value) {
  node_pointer newnode = new_node(value);
  newnode->insert_before(end_);
  if (size_ == 0u) root_ = newnode;
  ++size_;
}

template <typename T, typename A>
void List<T, A>::push_front(const_reference value) {
  if (size_ == 0u) {
    push_back(value);
  } else {
    node_pointer newnode = new_node(value);
    newnode->prev() = nullptr;
    newnode->next() = root_;
    root_->prev() = newnode;
    root_ = newnode;
    ++size_;
  }
}

template <typename T, typename A>
void List<T, A>::push_front(value_type &&value) {
  if (size_ == 0u) {
    push_back(value);
  } else {
    node_pointer newnode = new_node(value);
    newnode->prev() = nullptr;
    newnode->next() = root_;
    root_->prev() = newnode;
    root_ = newnode;
    ++size_;
  }
}

template <typename T, typename A>
void List<T, A>::pop_back() {
  if (size_ == 1u)
    pop_front();
  else if (size_ > 1u) {
    node_pointer tmp = end_->prev();
    end_->prev()->connect();
    delete_node(tmp);
    --size_;
  }
}

template <typename T, typename A>
void List<T, A>::pop_front() {
  if (size_ == 0u)
    return;
  else if (size_ == 1u) {
    delete_node(root_);
    root_ = end_;
    end_->prev() = nullptr;
  } else {
    node_pointer tmp = root_->next();
    delete_node(root_);
    root_ = tmp;
  }
  --size_;
}

template <typename T, typename A>
void List<T, A>::swap(List &other) {
  List<value_type> tmp(other);
  other = *this;
  *this = tmp;
  tmp.clear();
}

template <typename T, typename A>
void List<T, A>::merge(List &other) {
  if (&other == this) {
    return;
  }
  if (size_ == 0u) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
  } else {
    iterator begin1 = begin();
    iterator begin2 = other.begin();
    iterator end1 = end();
    iterator end2 = other.end();

    while (begin2 != end2) {
      iterator begin_now = begin();
      iterator end_now = end();
      while (begin_now != end_now) {
        if (*begin2 < *begin_now) {
          this->insert(begin_now, *begin2);
          other.pop_front();
          break;
        }
        ++begin_now;
      }
      ++begin2;
    }
  }
}

template <typename T, typename A>
void List<T, A>::splice(iterator pos, List &other) {
  other.end_->prev()->next() = pos.node();
  if (pos == begin()) {
    root_ = other.root_;
  } else {
    pos.node()->prev()->next() = other.root_;
    pos.node()->prev() = other.end_->prev();
  }
  size_ += other.size_;
  other.size_ = 0u;
  other.root_ = other.end_;
  other.end_->prev() = nullptr;
  other.end_->next() = nullptr;
}

template <typename T, typename A>
void List<T, A>::reverse() noexcept {
  if (size_ != 0u) {
    node_pointer head = end_->prev();
    auto it = begin();
    node_pointer current = it.node();
    node_pointer tmp;
    for (int i = 0; i != (int)size_; ++i) {
      tmp = current->next();
      if (i == 0) {
        current->next() = end_;
      } else {
        current->next() = current->prev();
      }
      current->prev() = tmp;
      current = current->prev();
    }
    root_ = head;
  }
}

template <typename T, typename A>
ListIterator<T> List<T, A>::insert(iterator pos, const_reference value) {
  iterator inserted;
  if (pos == begin()) {
    push_front(value);
    inserted = begin();
  } else if (pos == end()) {
    push_back(value);
    inserted = end_->prev();
  } else {
    node_pointer newnode = new_node(value);
    newnode->insert_before(pos.node());
    ++size_;
    inserted = iterator(newnode);
  }
  return inserted;
}

template <typename T, typename A>
void List<T, A>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
  } else if (pos == end()) {
    pop_back();
  } else {
    pos.node()->connect();
    delete_node(pos.node());
    --size_;
  }
}

template <typename T, typename A>
void List<T, A>::unique() {
  List<T, A> tmp;
  for (iterator it = begin(); it != end(); ++it) {
    if (*it == *(it + 1)) {
      while (*it == *(it + 1)) {
        it += 1;
      }
      tmp.push_back(*it);
    } else {
      tmp.push_back(*it);
    }
  }
  swap(tmp);
}

template <typename T, typename A>
void List<T, A>::sort() {
  if (size_ == 0) {
    return;
  }
  root_ = merge_sort(root_);
}

template <typename T, typename A>
DoubleNode<T> *List<T, A>::new_node(const_reference value) {
  node_pointer newnode = allocator_node_.allocate(1);
  allocator_node_.construct(newnode, node_type());
  newnode->data() = allocator_.allocate(1);
  allocator_.construct(newnode->data(), value);
  return newnode;
}

template <typename T, typename A>
DoubleNode<T> *List<T, A>::new_node(value_type &&value) {
  node_pointer newnode = allocator_node_.allocate(1);
  allocator_node_.construct(newnode, node_type());
  newnode->data() = allocator_.allocate(1);
  allocator_.construct(newnode->data(), std::move(value));
  return newnode;
}

template <typename T, typename A>
DoubleNode<T> *List<T, A>::new_end() {
  end_ = new_node(value_type());
  root_ = end_;
  end_->prev() = nullptr;
  end_->next() = nullptr;
  return end_;
}

template <typename T, typename A>
void List<T, A>::delete_node(node_pointer node) {
  allocator_.destroy(node->data());
  allocator_.deallocate(node->data(), 1);
  allocator_node_.destroy(node);
  allocator_node_.deallocate(node, 1);
}

template <typename T, typename A>
DoubleNode<T> *List<T, A>::middle(node_pointer root) {
  node_pointer fast_move = root->next();
  node_pointer slow_move = root;
  while (fast_move != end_ && fast_move->next() != end_) {
    fast_move = fast_move->next()->next();
    slow_move = slow_move->next();
  }
  return slow_move;
}

template <typename T, typename A>
DoubleNode<T> *List<T, A>::merge_sort(node_pointer root) {
  if (root == end_ || root->next() == end_) {
    return root;
  }
  node_pointer mid = middle(root);
  node_pointer left = root;
  node_pointer right = mid->next();
  mid->next() = end_;

  left = merge_sort(left);
  right = merge_sort(right);

  node_pointer result = merge(left, right);
  return result;
}

template <typename T, typename A>
DoubleNode<T> *List<T, A>::merge(node_pointer left, node_pointer right) {
  if (left == end_) return right;
  if (right == end_) return left;

  node_pointer answer;
  if (*left->data() < *right->data()) {
    answer = left;
    answer->next() = merge(left->next(), right);
  } else {
    answer = right;
    answer->next() = merge(left, right->next());
  }
  return answer;
}

}  // namespace s21

#endif  // !SRC_LIST_S21_LIST_REALIZATION_H
