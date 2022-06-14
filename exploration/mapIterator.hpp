#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP
#include "red_black_tree.hpp"
#include "vectorIterator.hpp"

namespace ft {

template <class t>
class mapiterator : public ft::iterator<ft::random_access_iterator_tag, t> {
public:
  typedef random_access_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef t value_type;
  typedef t *pointer_type;
  typedef t &reference;
  typedef typename ft::leaf<t> node;
  // typedef typename ft::mapiterator<value_type> iterator;

  mapiterator() : currentnode(){};
  mapiterator(node *mapnode) : currentnode(mapnode){};
  mapiterator(mapiterator const &rhs) : currentnode(rhs.currentnode){};
  mapiterator &operator=(const mapiterator &rhs) {
    if (this != &rhs) {
      this->currentnode = rhs.currentnode;
    }
    return *this;
  }
  ~mapiterator(){};
  operator mapiterator<value_type const>() const;
  reference operator*() const { return currentnode->value; };
  pointer_type operator->() const { return &currentnode->value; };

  mapiterator &operator++() {
    if (currentnode->_sentinel)
      currentnode = currentnode->getmin();
    else {
      currentnode = currentnode->getsuccessor();
    }
    return *this;
  }

  mapiterator operator++(int) {
    mapiterator tmp(*this);
    operator++();
    return tmp;
  }

  mapiterator &operator--() {
    if (currentnode->_sentinel) {
      // iterator it =
      currentnode = currentnode->getmax();
      // std::cerr << currentnode->_sentinel << std::endl;
      // currentnode = currentnode->parent;
    } else {
      currentnode = currentnode->getpredecessor();
    }
    return *this;
  }

  mapiterator operator--(int) {
    mapiterator tmp(*this);
    operator--();
    return tmp;
  }

  node *currentnode;
};

template <class t>
class constmapiterator
    : public ft::iterator<ft::random_access_iterator_tag, t> {
public:
  typedef random_access_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef const t value_type;
  typedef const t *pointer_type;
  typedef const t &reference;
  typedef typename ft::leaf<t> node;
  // typedef typename ft::leaf<const t> const_node;
  // typedef typename ft::mapiterator<value_type> iterator;

  constmapiterator() : currentnode(){};
  constmapiterator(node *mapnode) : currentnode(mapnode){};
  constmapiterator(constmapiterator const &rhs)
      : currentnode(rhs.currentnode){};
  constmapiterator(const mapiterator<t> &rhs) : currentnode(rhs.currentnode){};

  constmapiterator &operator=(const mapiterator<t> &rhs) const {
    /* if (*this != rhs) { */
    this->currentnode = rhs.currentnode;
    /* } */
    return *this;
  }
  ~constmapiterator(){};

  reference operator*() const { return currentnode->value; };
  pointer_type operator->() const { return &currentnode->value; };

  constmapiterator &operator++() {
    if (currentnode->_sentinel) {
      currentnode = currentnode->getmin();
    } else {
      currentnode = currentnode->getsuccessor();
      /* rtd::cerr << currentnode->value.first << std::endl; */
    }
    return *this;
  }

  constmapiterator operator++(int) {
    constmapiterator tmp(*this);
    operator++();
    return tmp;
  }

  constmapiterator &operator--() {
    if (currentnode->_sentinel) {
      currentnode = currentnode->getmax();
    } else {
      currentnode = currentnode->getpredecessor();
    }
    return *this;
  }

  constmapiterator operator--(int) {
    constmapiterator tmp(*this);
    operator--();
    return tmp;
  }
  // reference operator[](difference_type n) const { return base()[-n - 1]; };
  node *currentnode;
};

template <typename t1, typename t2>
bool operator==(const mapiterator<t1> &lhs, const constmapiterator<t2> &rhs) {
  return lhs.currentnode == rhs.currentnode;
};
template <typename t1, typename t2>
bool operator!=(const mapiterator<t1> &lhs, const constmapiterator<t2> &rhs) {
  return !operator==(lhs, rhs);
};

template <typename t1, typename t2>
bool operator==(const mapiterator<t1> &lhs, const mapiterator<t2> &rhs) {
  return lhs.currentnode == rhs.currentnode;
};
template <typename t1, typename t2>
bool operator!=(const mapiterator<t1> &lhs, const mapiterator<t2> &rhs) {
  return !operator==(lhs, rhs);
};

template <typename t1, typename t2>
bool operator==(const constmapiterator<t1> &lhs, const mapiterator<t2> &rhs) {
  return lhs.currentnode == rhs.currentnode;
};
template <typename t1, typename t2>
bool operator!=(const constmapiterator<t1> &lhs, const mapiterator<t2> &rhs) {
  return !operator==(lhs, rhs);
};

template <typename t1, typename t2>
bool operator==(const constmapiterator<t1> &lhs,
                const constmapiterator<t2> &rhs) {
  return lhs.currentnode == rhs.currentnode;
};
template <typename t1, typename t2>
bool operator!=(const constmapiterator<t1> &lhs,
                const constmapiterator<t2> &rhs) {
  return !operator==(lhs, rhs);
}

}; // namespace ft
#endif
