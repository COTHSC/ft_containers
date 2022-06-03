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
      this->currentNode = rhs->currentNode;
    }
    return *this;
  }
  ~mapIterator(){};

  T &operator*() const { return currentNode->value; };
  T &operator->() const { return &currentNode->value; };

  mapIterator &operator++() {
    if (currentNode->_sentinel)
      currentNode = currentNode->getMin();
    else {
      currentNode->getSuccesor();
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
} // namespace ft
#endif
