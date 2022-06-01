#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "red_black_tree.cpp"
#include <iostream>

namespace ft {
template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, T>>>

class map {
public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef tree<value_type> tree_type;

  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _allocator(alloc), _comparator(comp), _red_black_tree(){};

private:
  allocator_type _allocator;
  key_compare _comparator;
  tree_type _red_black_tree;
};
} // namespace ft

#endif
