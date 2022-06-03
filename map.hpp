#ifndef MAP_HPP
#define MAP_HPP

#include "mapIterator.hpp"
#include "pair.hpp"
#include "red_black_tree.hpp"
#include "vectorIterator.hpp"
#include <functional>
#include <iostream>

namespace ft {
template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, T>>>

class map {
public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef leaf<value_type> node_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef tree<value_type> tree_type;
  typedef ft::mapIterator<value_type> iterator;
  // typedef typename ft::pair<const key_type, mapped_type> value_type;

  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _allocator(alloc), _comparator(comp), _red_black_tree(){};

  virtual ~map(){};

  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    friend class map;

  protected:
    key_compare comp;
    value_compare(Compare c) : comp(c) {}

  public:
    typedef bool result_type;

    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

  bool insert(const value_type &value) {
    bool result = _red_black_tree.insert(value);
    return result;
  };

  // ft::pair<iterator, bool> insert(const value_type &value) const {
  //   bool result = _red_black_tree.insert(value);
  //   return result;
  // };

  iterator begin() { return iterator(_red_black_tree.min()); }

  tree_type _red_black_tree;

private:
  allocator_type _allocator;
  key_compare _comparator;
};
} // namespace ft

#endif
