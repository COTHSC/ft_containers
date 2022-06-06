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
  typedef std::size_t size_type;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef leaf<value_type> node_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef tree<value_type> tree_type;
  typedef mapIterator<value_type> iterator;
  typedef constMapIterator<value_type> const_iterator;
  // typedef typename ft::pair<const key_type, mapped_type> value_type;

  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _allocator(alloc), _comparator(comp), _red_black_tree(){};

  template <class InputIT>
  explicit map(InputIT first, InputIT last) : _red_black_tree() {
    insert(first, last);
  };
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

  template <class InputIT> void insert(InputIT first, InputIT last) {
    while (first != last) {
      insert(*first);
      ++first;
    }
  };

  bool insert(const value_type &value) {
    bool result = _red_black_tree.insert(value);
    return result;
  };

  iterator lower_bound(const key_type &key) const {
    iterator it(
        _red_black_tree.getLowerBound(ft::make_pair(key, mapped_type())));
    return it;
  }

  iterator upper_bound(const key_type &key) const {
    iterator it(
        _red_black_tree.getUpperBound(ft::make_pair(key, mapped_type())));
    return it;
  }

  // ft::pair<iterator, bool> insert(const value_type &value) const {
  //   bool result = _red_black_tree.insert(value);
  //   return result;
  // };

  iterator begin() { return iterator(_red_black_tree.min()); }
  const_iterator begin() const { return const_iterator(_red_black_tree.min()); }
  iterator end() { return iterator(_red_black_tree.max()); }
  const_iterator end() const { return const_iterator(_red_black_tree.max()); }

  tree_type _red_black_tree;
  size_type size() const { return _red_black_tree.getSize(); }
  size_type max_size() const { return 1; }

private:
  allocator_type _allocator;
  key_compare _comparator;
};

} // namespace ft

#endif
