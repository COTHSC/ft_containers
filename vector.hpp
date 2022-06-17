#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "is_integral.hpp"
#include "vectorIterator.hpp"
#include <iostream>
static class ft_nullptr_t {
private:
  void operator&() const;

public:
  template <class T> operator T *() const { return 0; }
  template <class C, class T> operator T C::*() const { return 0; }
} ft_nullptr_t = {};

template <bool Condition, typename T = void> struct enable_if {};

template <typename T> struct enable_if<true, T> { typedef T type; };

namespace ft {

template <class T, class Allocator = std::allocator<T>> class vector {
public:
  typedef T value_type;
  typedef value_type &reference;
  typedef value_type const &const_reference;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;

  typedef vectorIterator<T> iterator;
  typedef vectorIterator<const T> const_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;

  /* jconstructors and destructors */

  explicit vector(const allocator_type &alloc = allocator_type())
      : _size(0), _capacity(0), _allocator(alloc){};

  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type())
      : _size(0), _capacity(0), _allocator(alloc) {
    assign(first, last);
  };

  explicit vector(size_type count, const T &value = T(),
                  const Allocator &alloc = Allocator())
      : _size(count), _capacity(_size * 2), _allocator(alloc),
        _array(_allocator.allocate(_capacity)) {
    for (size_type i = 0; i < _size; ++i) {
      _allocator.construct(_array + i, value);
    }
  };

  vector(const vector &rhs)
      : _size(rhs.size()), _capacity(rhs.capacity()),
        _allocator(rhs.get_allocator()) {
    if (_capacity)
      _array = _allocator.allocate(_capacity);
    for (size_type i = 0; i < _size; ++i) {
      _allocator.construct(_array + i, rhs[i]);
    }
    // std::cerr << "this is capacity: " << _capacity << std::endl;
  };

  vector &operator=(const vector &rhs) {
    this->resize(rhs.size());
    for (size_type i = 0; i < this->size(); i++)
      _array[i] = rhs[i];
    return *this;
  }
  ~vector() {
    if (_capacity) {
      clear();
      _allocator.deallocate(_array, _capacity);
    }
  };

  void clear() {
    while (_size)
      pop_back();
  };
  iterator begin() { return iterator(&_array[0]); };

  reverse_iterator rbegin() { return reverse_iterator(end()); };

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  };

  const_iterator begin() const { return const_iterator(&_array[0]); };

  iterator end() { return iterator(&_array[_size]); };

  reverse_iterator rend() { return reverse_iterator(begin()); };

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  };

  const_iterator end() const { return const_iterator(&_array[_size]); };

  size_type size() const { return _size; };

  size_type max_size() const { return _allocator.max_size(); }

  bool empty() const { return (_size == 0); };

  size_type capacity() const { return _capacity; };

  void assign(size_type n, const value_type &val) {
    _size = 0;
    while (_size < n) {
      push_back(val);
    }
  };

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last,
              typename enable_if<!ft::is_integral<InputIterator>::value,
                                 InputIterator>::type * = ft_nullptr_t) {
    _size = 0;
    while (first != last) {
      push_back(*first);
      ++first;
    }
  };

  // TODO refactor this, the solution for unnalocated arrays is ugly
  void push_back(const value_type &val) {
    if (_size >= _capacity) {
      value_type *tmp;
      if (!_capacity) {
        _capacity = 1;
        _array = _allocator.allocate(_capacity);
        _allocator.construct(_array + _size, val);
        ++_size;
        return;
      }
      _capacity = _capacity * 2;
      tmp = _allocator.allocate(_capacity);
      for (size_type i = 0; i < _size; ++i) {
        _allocator.construct(tmp + i, _array[i]);
      }
      // if (_capacity) {
      _allocator.deallocate(_array, _capacity / 2);
      // }
      _array = tmp;
    }
    _allocator.construct(_array + _size, val);
    ++_size;
  };

  reference at(size_type n) {
    if (n >= _size)
      throw std::out_of_range("exception");
    return (_array[n]);
  };
  const_reference at(size_type n) const {
    if (n >= _size)
      throw std::out_of_range("exception");
    return (_array[n]);
  };
  reference front() { return (_array[0]); };
  const_reference front() const { return (_array[0]); };
  reference back() { return (_array[_size - 1]); };
  const_reference back() const { return (_array[_size - 1]); };
  void reserve(size_type n) {
    while (n >= _capacity) {
      size_type new_cap;
      if (!_capacity)
        new_cap = 1;
      else
        new_cap = _capacity * 2;
      value_type *tmp;
      tmp = _allocator.allocate(new_cap);
      for (size_type i = 0; i < _size; ++i) {
        _allocator.construct(tmp + i, _array[i]);
      }
      if (_capacity)
        _allocator.deallocate(_array, _capacity);
      _array = tmp;
      _capacity = new_cap;
    }
  };

  void resize(size_type n, value_type val = value_type()) {
    while (n < _size)
      pop_back();
    while (n > _size)
      push_back(val);
  };

  void pop_back() {
    if (_size > 0)
      _allocator.destroy(_array + (--_size));
  };

  friend std::ostream &operator<<(std::ostream &ostr, const vector &rhs) {
    for (size_type i = 0; i < rhs.size(); ++i)
      ostr << rhs[i] << std::endl;
    ostr << "THE CAPACITY OF THIS ARRAY IS: " << rhs.capacity() << std::endl;
    return ostr;
  };

  reference operator[](size_type n) { return _array[n]; };
  const_reference operator[](size_type n) const { return _array[n]; };

  allocator_type get_allocator() const { return _allocator; }

  iterator insert(iterator position, const value_type &val) {
    iterator it = this->begin();
    difference_type i = distance(this->begin(), position);
    _offset_by_n(1, i);
    _allocator.construct(_array + i, val);
    return position;
  };

  void insert(iterator position, size_type n, const value_type &val) {
    iterator it = this->begin();
    size_type i = 0;
    while (it != position) {
      ++i;
      ++it;
    }
    _offset_by_n(n, i);
    size_type to_insert = n;
    while (to_insert > 0) {
      _allocator.construct(_array + i++, val);
      to_insert--;
    }
  };

  template <class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last,
              typename enable_if<!ft::is_integral<InputIterator>::value,
                                 InputIterator>::type * = ft_nullptr_t) {
    iterator it = this->begin();
    difference_type i = distance(this->begin(), position);
    difference_type to_insert = distance(first, last);
    _offset_by_n(to_insert, i);
    while (first != last) {
      _allocator.construct(_array + i++, *first);
      ++first;
    }
  };

  iterator erase(iterator pos) {
    difference_type index = distance(this->begin(), pos);
    offset_by_n(1, index);
    pop_back();
    return pos;
  };

  iterator erase(iterator first, iterator last) {
    difference_type index = distance(this->begin(), first);
    difference_type nb_of_elements = distance(first, last);
    while (nb_of_elements) {
      erase(iterator(_array + index));
      --nb_of_elements;
    }
    return iterator(_array + index);
  };
  void swap(vector &other) {
    pointer tmp_array = this->_array;
    allocator_type tmp_allocator = this->_allocator;
    size_type tmp_capacity = this->_capacity;
    size_type tmp_size = this->_size;

    this->_allocator = other._allocator;
    this->_array = other._array;
    this->_capacity = other._capacity;
    this->_size = other._size;

    other._allocator = tmp_allocator;
    other._array = tmp_array;
    other._capacity = tmp_capacity;
    other._size = tmp_size;
  }

private:
  size_type _size;
  size_type _capacity;
  allocator_type _allocator;
  value_type *_array;

  template <class It>
  typename ft::iterator_traits<It>::difference_type do_distance(It first,
                                                                It last) {
    typename ft::iterator_traits<It>::difference_type result = 0;
    while (first != last) {
      ++first;
      ++result;
    }
    return result;
  }

  template <class It>
  typename ft::iterator_traits<It>::difference_type distance(It first,
                                                             It last) {
    return (do_distance(first, last));
  }

  void _offset_by_n(size_type n, size_type start_point) {
    if (_size + n >= _capacity) {
      reserve(_size + n);
    }
    size_type i = _size;
    while (i > start_point) {
      --i;
      _array[i + n] = _array[i];
    }
    _size += n;
  };

  void offset_by_n(size_type n, size_type start_point) {
    size_type i = start_point;
    if (!_size)
      return;
    while (i < _size - 1) {
      ++i;
      _array[i - n] = _array[i];
    }
  };
};

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
  while (first1 != last1) {
    if (!(*first1 == *first2))
      return false;
    ++first1;
    ++first2;
  }
  return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1)
      return false;
    else if (*first1 < *first2)
      return true;
    ++first1;
    ++first2;
  }
  return (first2 != last2);
}

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  if (lhs.size() != rhs.size())
    return 0;
  return (equal(lhs.begin(), lhs.end(), rhs.begin()));
};

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs == rhs);
};

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return (
      lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
};

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return (
      lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ||
      lhs == rhs);
};

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return (rhs < lhs);
};

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return (!(lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                    rhs.end())) ||
          lhs == rhs);
};
}; // namespace ft
#endif
