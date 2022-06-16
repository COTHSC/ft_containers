#ifndef MAP_HPP
#define MAP_HPP

// #include "mapIterator.hpp"
#include "compare.hpp"
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
  typedef tree<value_type, Compare, Alloc> tree_type;
  typedef mapIterator<value_type> iterator;
  typedef constMapIterator<value_type> const_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
  // typedef typename ft::pair<const key_type, mapped_type> value_type;

  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _red_black_tree(), _allocator(alloc), _comparator(comp){};

  template <class InputIT>
  map(InputIT first, InputIT last) : _red_black_tree() {
    insert(first, last);
    /* _red_black_tree.printBT(); */
  };

  map(const map &og) { *this = og; };
  map &operator=(const map &rhs) {
    if (this != &rhs) {
      _allocator = Alloc(rhs._allocator);
      _red_black_tree = rhs._red_black_tree;
    }
    return *this;
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

  reverse_iterator rbegin() { return reverse_iterator(end()); };

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  };

  reverse_iterator rend() { return reverse_iterator(begin()); };

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  };

  iterator find(const key_type &key) {
    if (_red_black_tree.find(ft::make_pair(key, mapped_type())) !=
        _red_black_tree.get_sentinel()) {
      iterator it(_red_black_tree.find(ft::make_pair(key, mapped_type())));
      return it;
    }
    return end();
  }

  const_iterator find(const key_type &key) const {
    if (_red_black_tree.find(ft::make_pair(key, mapped_type())) !=
        _red_black_tree.get_sentinel()) {
      iterator it(_red_black_tree.find(ft::make_pair(key, mapped_type())));
      return it;
    }
    return end();
  }
  size_type count(const key_type &key) const {
    if (_red_black_tree.find(ft::make_pair(key, mapped_type())) !=
        _red_black_tree.get_sentinel())
      return 1;
    return 0;
  }
  ft::pair<iterator, bool> insert(const value_type &value) {
    bool result = _red_black_tree.insert(value);
    iterator it = _red_black_tree.find(value);
    return ft::make_pair(it, result);
  };

  iterator insert(iterator hint, const value_type &val) {
    _red_black_tree.insert(val);
    return _red_black_tree.find(val);
    // return begin();
  };
  // iterator lower_bound(const key_type &key) const {
  //   iterator it(
  //       _red_black_tree.getLowerBound(ft::make_pair(key, mapped_type())));
  //   return it;
  // }

  void erase(iterator first, iterator last) {
    key_type next = 0;
    iterator tmp = first;
    while (first != last) {
      ++tmp;
      next = (*tmp).first;
      // std::cerr << "this is tbdel: " << (*first).first << std::endl;
      // std::cerr << "this is next: " << next << std::endl;
      erase(first);
      if (tmp == end())
        break;
      // _red_black_tree.printBT();
      tmp = find(next);
      first = tmp;
    }
  };

  void erase(iterator pos) { _red_black_tree.delete_rb(*pos); }

  size_type erase(const key_type &key) {
    return (_red_black_tree.delete_rb(ft::make_pair(key, mapped_type())));
  }

  iterator lower_bound(const key_type &key) {
    iterator it = begin();
    while (it != end()) {
      if (_comparator((*it).first, key) == false) {
        break;
      }
      ++it;
    }
    return it;
  }

  void swap(map &other) { _red_black_tree.treeSwap(other._red_black_tree); }
  bool empty() const { return !_red_black_tree.is_empty(); }

  const_iterator lower_bound(const key_type &key) const {
    const_iterator it = begin();
    while (it != end()) {
      if (_comparator((*it).first, key) == false) {
        break;
      }
      ++it;
    }
    return it;
  }

  void clear() { _red_black_tree.clearTree(); }

  const_iterator upper_bound(const key_type &key) const {
    const_iterator it = begin();
    while (it != end()) {
      if (_comparator(key, (*it).first)) {
        break;
      }
      ++it;
    }
    return it;
  }
  iterator upper_bound(const key_type &key) {
    iterator it = begin();
    iterator ite = end();

    while (it != ite) {
      if (_comparator(key, (*it).first)) {
        break;
      }
      ++it;
    }
    return it;
  }

  // ft::pair<iterator, bool> insert(const value_type &value) const {
  //   bool result = _red_black_tree.insert(value);
  //   return result;
  // };

  pair<iterator, iterator> equal_range(const key_type &key) {
    return (ft::make_pair(lower_bound(key), upper_bound(key)));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
    return (ft::make_pair(lower_bound(key), upper_bound(key)));
  }

  mapped_type &operator[](const key_type &key) {
    // std::cerr << "this is key: " << key << std::endl;
    node_type *ptr = _red_black_tree.find(ft::make_pair(key, mapped_type()));
    if (!ptr->_sentinel) {
      return ptr->value.second;
    }
    insert(ft::make_pair(key, mapped_type()));
    // _red_black_tree.printBT();
    ptr = _red_black_tree.find(ft::make_pair(key, mapped_type()));
    return ptr->value.second;
    // _red_black_tree.printBT();
    // ft::pair<iterator, bool> tmp = insert(ft::make_pair(key, mapped_type()));
    // return insert(ft::make_pair(key, mapped_type())).first->second;
    // node_type *node = _red_black_tree.find(ft::make_pair(key,
    // mapped_type())); if (!node->_sentinel) {
    //   return node->value.second;
    // }
    // insert(ft::make_pair(key, mapped_type()));
    // node = _red_black_tree.find(ft::make_pair(key, mapped_type()));
    // return node->value.second;
  }

  iterator begin() { return iterator(_red_black_tree.min()); }
  const_iterator begin() const { return const_iterator(_red_black_tree.min()); }
  iterator end() { return iterator(_red_black_tree.max()->right); }
  const_iterator end() const {
    return const_iterator(_red_black_tree.max()->right);
  }

  tree_type _red_black_tree;
  size_type size() const { return _red_black_tree.getSize(); }
  size_type max_size() const { return _red_black_tree.getMaxSize(); }

  key_compare key_comp() const { return _comparator; }
  value_compare value_comp() const { return value_compare(_comparator); }

private:
  allocator_type _allocator;
  key_compare _comparator;
};

template <class key, class T, class compare, class Alloc>
bool operator<(const ft::map<key, T, compare, Alloc> &lhs,
               const ft::map<key, T, compare, Alloc> &rhs) {
  return (lex_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class key, class T, class compare, class Alloc>
bool operator<=(const ft::map<key, T, compare, Alloc> &lhs,
                const ft::map<key, T, compare, Alloc> &rhs) {
  return !(rhs < lhs);
}

template <class key, class T, class compare, class Alloc>
bool operator>(const ft::map<key, T, compare, Alloc> &lhs,
               const ft::map<key, T, compare, Alloc> &rhs) {
  return (rhs < lhs);
}

template <class key, class T, class compare, class Alloc>
bool operator>=(const ft::map<key, T, compare, Alloc> &lhs,
                const ft::map<key, T, compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template <class key, class T, class compare, class Alloc>
bool operator==(const ft::map<key, T, compare, Alloc> &lhs,
                const ft::map<key, T, compare, Alloc> &rhs) {
  if (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()))
    return true;
  return false;
  // return !(lhs < rhs);
}

template <class key, class T, class compare, class Alloc>
bool operator!=(const ft::map<key, T, compare, Alloc> &lhs,
                const ft::map<key, T, compare, Alloc> &rhs) {
  return !(lhs == rhs);
  // return !(lhs < rhs);
}

} // namespace ft

#endif
