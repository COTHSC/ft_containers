#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP
#include "red_black_tree.hpp"
#include "vectorIterator.hpp"

namespace ft {

template <class T>
class mapIterator : public ft::iterator<ft::random_access_iterator_tag, T> {
public:
  typedef random_access_iterator_tag iterator_category;
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
  operator mapIterator<value_type const>() const;
  T &operator*() const { return currentNode->value; };
  T *operator->() const { return &currentNode->value; };

  mapIterator &operator++() {
    if (currentNode->_sentinel)
      currentNode = currentNode->getMin();
    else {
      currentNode->getSuccessor();
    }
    return *this;
  }

  mapIterator &operator++(int) {
    mapIterator tmp(*this);
    operator++();
    return tmp;
  }

  mapIterator &operator--() {
    if (currentNode->_sentinel) {
      currentNode = currentNode->getMax();
    } else {
      std::cerr << "I AM IN ELSE" << std::endl;
      currentNode = currentNode->getPredecessor();
    }
    return *this;
  }

  mapIterator &operator--(int) {
    leaf<T> tmp(*this);
    operator--();
    return tmp;
  }

  node *currentNode;
};

template <class T>
class constMapIterator
    : public ft::iterator<ft::random_access_iterator_tag, T> {
public:
  typedef random_access_iterator_tag iterator_category;
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
    /* if (*this != rhs) { */
    this->currentNode = rhs.currentNode;
    /* } */
    return *this;
  }
  ~constMapIterator(){};

  T &operator*() const { return currentNode->value; };
  T *operator->() const { return &currentNode->value; };

  constMapIterator &operator++() {
    if (currentNode->_sentinel) {
      currentNode = currentNode->getMin();
    } else {
      currentNode = currentNode->getSuccessor();
      /* rtd::cerr << currentNode->value.first << std::endl; */
    }
    return *this;
  }

  constMapIterator &operator++(int) {
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

  constMapIterator &operator--(int) {
    leaf<T> tmp(*this);
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
