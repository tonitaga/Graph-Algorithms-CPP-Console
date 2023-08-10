#ifndef SRC_LIST_S21_LIST_H
#define SRC_LIST_S21_LIST_H

#include <initializer_list>
#include <iostream>

#include "list_double_node.h"
#include "list_iterator.h"

namespace ng {
template <class T, class Allocator = std::allocator<T>>
class List {
 public:
  using value_type = T;
  using allocator_type = Allocator;
  using allocator_node = std::allocator<DoubleNode<T>>;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;
  using node_type = DoubleNode<value_type>;
  using node_pointer = node_type *;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

 private:
  size_type size_;
  node_pointer root_;
  node_pointer end_;
  allocator_type allocator_;
  allocator_node allocator_node_;

 public:
  explicit List(const Allocator &allocator = Allocator())
      : size_(0u), root_(nullptr), allocator_(allocator) {
    new_end();
  }
  explicit List(size_type size, const T & = T(), const Allocator & = Allocator());
  List(std::initializer_list<value_type> const &items);
  List(const List &other);
  List(List &&other) noexcept;
  ~List();

  List &operator=(const List &other);
  List &operator=(List &&other) noexcept;

  void assign(size_type count, const_reference value);
  void assign(std::initializer_list<value_type> const &items);

  /*=========================================================*/
  /*                                                         */
  /*                    LIST ELEMENT ACCESS                  */
  /*                                                         */
  /*=========================================================*/

  reference front() { return *(root_->data()); }
  const_reference front() const { return *(root_->data()); }
  reference back();
  const_reference back() const;

  /*=========================================================*/
  /*                                                         */
  /*                      LIST ITERATORS                     */
  /*                                                         */
  /*=========================================================*/

  iterator begin() { return iterator(root_); }
  iterator end() { return iterator(end_); }
  const_iterator cbegin() const { return const_iterator(root_); }
  const_iterator cend() const { return const_iterator(end_); }

  /*=========================================================*/
  /*                                                         */
  /*                      LIST CAPACITY                      */
  /*                                                         */
  /*=========================================================*/

  bool empty() const { return size_ == 0u; };
  size_type size() const { return size_; };
  size_type max_size() const { return allocator_.max_size() / 6; };

  /*=========================================================*/
  /*                                                         */
  /*                      LIST MODIFIERS                     */
  /*                                                         */
  /*=========================================================*/

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void push_back(value_type &&value);
  void push_front(const_reference value);
  void push_front(value_type &&value);
  void pop_back();
  void pop_front();
  void swap(List &other);
  void merge(List &other);
  void splice(iterator pos, List &other);
  void reverse() noexcept;
  void unique();
  void sort();

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it(const_cast<node_pointer>(pos.node()));
    return insert(it, value_type(std::forward<Args>(args)...));
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    push_back(value_type(std::forward<Args>(args)...));
  }

  template <class... Args>
  void emplace_front(Args &&...args) {
    push_front(value_type(std::forward<Args>(args)...));
  }

 private:
  node_pointer new_node(const_reference value);
  node_pointer new_node(value_type &&value);
  node_pointer new_end();
  void delete_node(node_pointer node);
  node_pointer middle(node_pointer root);
  node_pointer merge_sort(node_pointer root);
  node_pointer merge(node_pointer left, node_pointer right);
};
}  // namespace s21

#include "list_realization.h"

#endif  // !SRC_LIST_S21_LIST_H