// #include "mapIterator.hpp"
#include "vectorIterator.hpp"
namespace ft {
template <typename Iter> class reverse_iterator {
public:
  typedef Iter iterator_type;
  typedef
      typename ft::iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iter>::value_type value_type;
  typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iter>::pointer pointer;
  typedef typename ft::iterator_traits<Iter>::reference reference;

  reverse_iterator() : current(iterator_type()){};
  explicit reverse_iterator(iterator_type it) : current(it){};
  template <class U>
  reverse_iterator(const reverse_iterator<U> &rev_it)
      : current(rev_it.base()){};
  iterator_type base() const { return current; };

  template <class U>
  reverse_iterator &operator=(const reverse_iterator<U> &other) {
    current = other.base();
    return *this;
  };

  reference operator*() const {
    Iter tmp = current;
    return *--tmp;
  };
  pointer operator->() const { return &(operator*()); };
  reference operator[](difference_type n) const { return (base()[-n - 1]); };

  reverse_iterator &operator++() {
    --current;
    return *this;
  };

  reverse_iterator operator++(int) {
    reverse_iterator tmp(base());
    --current;
    return tmp;
  };

  reverse_iterator &operator--() {
    ++current;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator tmp(base());
    ++current;
    return tmp;
  };

  reverse_iterator operator+(difference_type n) const {
    return (reverse_iterator<iterator_type>(current - n));
  };

  reverse_iterator operator-(difference_type n) const {
    return (reverse_iterator<iterator_type>(current + n));
  };

  reverse_iterator &operator+=(difference_type n) {
    current -= n;
    return *this;
  };
  reverse_iterator &operator-=(difference_type n) {
    current += n;
    return (*this);
  };

protected:
  iterator_type current;
};

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1> &lhs,
                const reverse_iterator<Iterator2> &rhs) {
  return (lhs.base() == rhs.base());
};

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1> &lhs,
                const reverse_iterator<Iterator2> &rhs) {
  return (lhs.base() != rhs.base());
};

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1> &lhs,
               const reverse_iterator<Iterator2> &rhs) {
  return (lhs.base() > rhs.base());
};

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1> &lhs,
                const reverse_iterator<Iterator2> &rhs) {
  return (lhs.base() >= rhs.base());
};

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1> &lhs,
               const reverse_iterator<Iterator2> &rhs) {
  return (lhs.base() < rhs.base());
};

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1> &lhs,
                const reverse_iterator<Iterator2> &rhs) {
  return (lhs.base() <= rhs.base());
};

template <class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n,
          const reverse_iterator<Iter> &it) {
  return (reverse_iterator<Iter>(it.base() - n));
};

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator2>::difference_type
operator-(const reverse_iterator<Iterator1> &lhs,
          const reverse_iterator<Iterator2> &rhs) {
  return (rhs.base() - lhs.base());
};
} // namespace ft
