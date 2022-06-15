#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP
#include "red_black_tree.hpp"
#include <iostream>
namespace ft {

struct output_iterator_tag {};
struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct iterator {
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Category iterator_category;
};

template <class Iter> struct iterator_traits {
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
};
template <class T> struct iterator_traits<T *> {

  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template <class T> struct iterator_traits<const T *> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template <typename vector>
class vectorIterator
    : public ft::iterator<ft::random_access_iterator_tag, vector> {

public:
  typedef vector value_type;
  typedef vector &reference_type;
  typedef size_t size_type;
  typedef value_type *pointer_type;
  typedef std::ptrdiff_t difference_type;

  vectorIterator(){};
  vectorIterator(const vectorIterator &rhs) : _ptr(rhs._ptr){};
  //    vectorIterator(pointer_type ptr) : _ptr(ptr) {};
  vectorIterator(pointer_type ptr) : _ptr(ptr){};
  //    vectorIterator(vector *ptr) : _ptr(ptr) {};
  ~vectorIterator(){};

  vectorIterator &operator=(vectorIterator const &rhs) {
    _ptr = rhs._ptr;
    return *this;
  };

  // operator vectorIterator< const vector>() const;
  // bool operator==(vectorIterator const &rhs) {
  //   return (_ptr == rhs._ptr);
  // };
  operator vectorIterator<const vector>() const {
    return vectorIterator<const vector>(_ptr);
  }

  bool operator!=(vectorIterator const &rhs) { return !(_ptr == rhs._ptr); };

  reference_type operator[](size_type idx) { return *(_ptr + idx); };

  vectorIterator operator+(difference_type idx) const {
    vectorIterator<vector> tmp(_ptr + idx);
    return tmp;
  };

  difference_type operator+(vectorIterator &rhs) { return (_ptr + rhs._ptr); };
  pointer_type base(void) const { return _ptr; };

  difference_type operator-(vectorIterator &rhs) { return (_ptr - rhs._ptr); };

  vectorIterator operator-(difference_type diff) const {
    //_ptr -= diff;
    // return (*this);
    vectorIterator<vector> tmp(_ptr - diff);
    return tmp;
  };
  vectorIterator &operator+=(difference_type op) {
    _ptr += op;
    return *this;
  };
  vectorIterator &operator-=(difference_type op) {
    _ptr -= op;
    return *this;
  };

  vectorIterator &operator++(void) {
    _ptr += 1;
    return *this;
  };

  vectorIterator operator++(int) {
    vectorIterator tmp(*this);
    _ptr += 1;
    return tmp;
  };

  vectorIterator &operator--(void) {
    _ptr -= 1;
    return *this;
  };

  vectorIterator operator--(int) {
    vectorIterator tmp(*this);
    _ptr -= 1;
    return tmp;
  };

  reference_type operator*() { return *_ptr; };

  pointer_type operator->() {
    return &(operator*());
    //  return *_ptr;
  };

  pointer_type _ptr;

protected:
};

template <class T>
vectorIterator<T> operator+(typename vectorIterator<T>::difference_type n,
                            vectorIterator<T> const &rhs) {
  return rhs + n;
};

template <typename T, typename U>
typename vectorIterator<T>::difference_type
operator-(const vectorIterator<T> &lhs, const vectorIterator<U> &rhs) {
  return (lhs.base() - rhs.base());
};

template <typename iterator1, typename iterator2>
bool operator!=(const vectorIterator<iterator1> &lhs,
                const vectorIterator<iterator2> &rhs) {
  return (lhs._ptr != rhs._ptr);
};
template <typename iterator1, typename iterator2>
bool operator==(const vectorIterator<iterator1> &lhs,
                const vectorIterator<iterator2> &rhs) {
  return (lhs._ptr == rhs._ptr);
};

template <typename iterator1, typename iterator2>
bool operator<(const vectorIterator<iterator1> &lhs,
               const vectorIterator<iterator2> &rhs) {
  return (lhs._ptr < rhs._ptr);
};
template <typename iterator1, typename iterator2>
bool operator>(const vectorIterator<iterator1> &lhs,
               const vectorIterator<iterator2> &rhs) {
  return (lhs._ptr > rhs._ptr);
};

template <typename iterator1, typename iterator2>
bool operator<=(const vectorIterator<iterator1> &lhs,
                const vectorIterator<iterator2> &rhs) {
  return (lhs._ptr <= rhs._ptr);
};
template <typename iterator1, typename iterator2>
bool operator>=(const vectorIterator<iterator1> &lhs,
                const vectorIterator<iterator2> &rhs) {
  return (lhs._ptr >= rhs._ptr);
};

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
    this->current = other.base();
    return *this;
  };

  reference operator*() const {
    iterator_type tmp(current);
    return *--tmp;
  };
  pointer operator->() const { return &(this->operator*()); };
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
  Iter current;
};

// template< class Iter >
// class reverse_iterator
// {
//   public:
//     typedef Iter iterator_type;
//     typedef typename iterator_traits<Iter>::value_type value_type;
//     typedef typename iterator_traits<Iter>::iterator_category
//     iterator_category; typedef typename
//     iterator_traits<Iter>::difference_type difference_type; typedef typename
//     iterator_traits<Iter>::pointer pointer; typedef typename
//     iterator_traits<Iter>::reference reference;

//     reverse_iterator(): current(){};
//     explicit reverse_iterator( iterator_type x ) : current(x) {};
//     template< class U >
//     reverse_iterator( const reverse_iterator<U>& other ) :
//     current(other.base()){}; template< class U > reverse_iterator& operator=(
//     const reverse_iterator<U>& other ) { this->current = other.base(); return
//     *this; };
//     /**
//      * @brief Returns the underlying base iterator. That is
//      ft::reverse_iterator(it).base() == it
//      * @return iterator_type
//      */
//     iterator_type base() const { return current; };
//     reference operator*() const { iterator_type tmp = current; return
//     *--tmp;}; pointer operator->() const { return &(operator*()); };
//     reference operator[]( difference_type n ) const { return base()[-n-1]; };
//     /**
//      * @brief Increments or decrements the iterator.
//               Inverse operations are applied to the underlying operator
//               because of the reverse order.
//      * @return reverse_iterator&, or reverse_iterator
//      */
//     reverse_iterator& operator++() { --current; return *this; };
//     reverse_iterator& operator--() { ++current; return *this; };
//     reverse_iterator operator++( int ) { reverse_iterator tmp(base());
//     current--; return tmp; }; reverse_iterator operator--( int ) {
//     reverse_iterator tmp(base()); current++; return tmp; }; reverse_iterator
//     operator+( difference_type n ) const { return reverse_iterator(base() -
//     n); }; reverse_iterator operator-( difference_type n ) const { return
//     reverse_iterator(base() + n); }; reverse_iterator& operator+=(
//     difference_type n ){ current = base() - n; return *this; };
//     reverse_iterator& operator-=( difference_type n ){ current = base() + n;
//     return *this; };

//   protected:
//     iterator_type current;
// };
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

template <class T>
class mapIterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer_type;
  typedef T &reference;
  typedef typename ft::leaf<T> node;
  // typedef typename ft::mapIterator<value_type> iterator;

  mapIterator() : currentNode(){};
  mapIterator(node *mapNode) : currentNode(mapNode){};
  mapIterator(mapIterator const &rhs) : currentNode(rhs.currentNode){};
  mapIterator &operator=(const mapIterator &rhs) {
    if (this != &rhs) {
      this->currentNode = rhs.currentNode;
    }
    return *this;
  }
  ~mapIterator(){};
  operator mapIterator<const value_type>() const {
    return mapIterator<const value_type>(currentNode);
  };
  reference operator*() const { return currentNode->value; };
  pointer_type operator->() const { return &currentNode->value; };

  mapIterator &operator++() {
    if (currentNode->_sentinel) {
      currentNode = currentNode->getMin();
    } else {
      currentNode = currentNode->getSuccessor();
    }
    return *this;
  }

  mapIterator operator++(int) {
    mapIterator tmp(*this);
    operator++();
    return tmp;
  }

  mapIterator &operator--() {
    if (currentNode->_sentinel) {
      currentNode = currentNode->getMax();
      // std::cerr << "this is the maximum apparently: "
      //           << currentNode->value.first << std::endl;
    } else {
      currentNode = currentNode->getPredecessor();
    }
    return *this;
  }

  mapIterator operator--(int) {
    mapIterator tmp(*this);
    operator--();
    return tmp;
  }

  node *currentNode;
};

template <class T>
class constMapIterator
    : public ft::iterator<ft::bidirectional_iterator_tag, T> {
public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef const T value_type;
  typedef const T *pointer_type;
  typedef const T &reference;
  typedef typename ft::leaf<T> node;
  // typedef typename ft::leaf<const T> const_node;
  // typedef typename ft::mapIterator<value_type> iterator;

  constMapIterator() : currentNode(){};
  constMapIterator(node *mapNode) : currentNode(mapNode){};
  constMapIterator(constMapIterator const &rhs)
      : currentNode(rhs.currentNode){};
  constMapIterator(const mapIterator<T> &rhs) : currentNode(rhs.currentNode){};

  constMapIterator &operator=(const mapIterator<T> &rhs) {
    this->currentNode = rhs.currentNode;
    return *this;
  }
  ~constMapIterator(){};

  reference operator*() const { return currentNode->value; };
  pointer_type operator->() const { return &currentNode->value; };

  constMapIterator &operator++() {
    if (currentNode->_sentinel) {
      currentNode = currentNode->getMin();
    } else {
      currentNode = currentNode->getSuccessor();
      /* rtd::cerr << currentNode->value.first << std::endl; */
    }
    return *this;
  }

  constMapIterator operator++(int) {
    constMapIterator tmp(*this);
    operator++();
    return tmp;
  }

  constMapIterator &operator--() {
    if (currentNode->_sentinel) {
      currentNode = currentNode->getMax();
    } else {
      currentNode = currentNode->getPredecessor();
    }
    return *this;
  }

  constMapIterator operator--(int) {
    constMapIterator tmp(*this);
    operator--();
    return tmp;
  }
  // reference operator[](difference_type n) const { return base()[-n - 1]; };
  node *currentNode;
};

template <typename T1, typename T2>
bool operator==(const mapIterator<T1> &lhs, const constMapIterator<T2> &rhs) {
  return lhs.currentNode == rhs.currentNode;
};
template <typename T1, typename T2>
bool operator!=(const mapIterator<T1> &lhs, const constMapIterator<T2> &rhs) {
  return !operator==(lhs, rhs);
};

template <typename T1, typename T2>
bool operator==(const mapIterator<T1> &lhs, const mapIterator<T2> &rhs) {
  return lhs.currentNode == rhs.currentNode;
};
template <typename T1, typename T2>
bool operator!=(const mapIterator<T1> &lhs, const mapIterator<T2> &rhs) {
  return !operator==(lhs, rhs);
};

template <typename T1, typename T2>
bool operator==(const constMapIterator<T1> &lhs, const mapIterator<T2> &rhs) {
  return lhs.currentNode == rhs.currentNode;
};
template <typename T1, typename T2>
bool operator!=(const constMapIterator<T1> &lhs, const mapIterator<T2> &rhs) {
  return !operator==(lhs, rhs);
};

template <typename T1, typename T2>
bool operator==(const constMapIterator<T1> &lhs,
                const constMapIterator<T2> &rhs) {
  return lhs.currentNode == rhs.currentNode;
};
template <typename T1, typename T2>
bool operator!=(const constMapIterator<T1> &lhs,
                const constMapIterator<T2> &rhs) {
  return !operator==(lhs, rhs);
}

}; // namespace ft
#endif
