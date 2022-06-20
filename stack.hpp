#ifndef STACK_HPP
#define STACK_HPP
#include "is_integral.hpp"
#include "vector.hpp"
#include "vectorIterator.hpp"
#include <iostream>

namespace ft {
template <class T, class Container = ft::vector<T> > class stack {
public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef Container container_type;

  explicit stack(const container_type &ctnr = container_type())
      : c(ctnr){

        };

  ~stack(){};

  bool empty() const { return (c.empty()); };

  size_type size() const { return (c.size()); };

  value_type &top() { return (c.back()); };

  const value_type &top() const { return (c.back()); };

  void pop() { c.pop_back(); };

  void push(const value_type &val) { c.push_back(val); };

  template <class U, class ctnr>
  friend bool operator==(const stack<U, ctnr> &lhs, const stack<U, ctnr> &rhs);

  template <class U, class ctnr>
  friend bool operator<(const stack<U, ctnr> &lhs, const stack<U, ctnr> &rhs);

protected:
  container_type c;
};

template <class T, class Container>
bool operator==(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return (lhs.c == rhs.c);
};

template <class T, class Container>
bool operator!=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return (!operator==(lhs, rhs));
};

template <class T, class Container>
bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
  return (lhs.c < rhs.c);
};

template <class T, class Container>
bool operator<=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return (operator<(lhs, rhs) || operator==(lhs, rhs));
};

template <class T, class Container>
bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
  return (!(operator<(lhs, rhs)) && !operator==(lhs, rhs));
};

template <class T, class Container>
bool operator>=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return (!(operator<(lhs, rhs)) || operator==(lhs, rhs));
};

}; // namespace ft
#endif
