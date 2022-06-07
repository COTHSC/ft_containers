#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#define LEFT 0
#define RIGHT 1
#define left children[LEFT]
#define right children[RIGHT]
namespace ft {

enum color_t { BLACK, RED };
template <class T> class leaf {
public:
  // TODO this constructor is used to insert new leaves with a value, I really
  // shouldnt need  the default sentinel value here...
  // leaf(int key, T value, leaf *root, leaf *sentinel, int is_sentinel = 0)
  //     : value(value), _sentinel(is_sentinel), parent(root), color(RED) {
  //   children[1] = sentinel;
  //   children[0] = sentinel;
  // };

  leaf(T value, leaf *root, leaf *sentinel, int is_sentinel = 0)
      : value(value), _sentinel(is_sentinel), parent(root), color(RED) {
    children[1] = sentinel;
    children[0] = sentinel;
  };

  leaf(T value, leaf *sentinel) : value(value), _sentinel(0), color(RED) {
    children[1] = sentinel;
    children[0] = sentinel;
  };

  leaf(int sentinel = 0) : value(), _sentinel(sentinel), color(BLACK){};
  leaf(leaf *sentinel) {
    children[1] = sentinel;
    children[0] = sentinel;
  };

  leaf<T> *getMax() {
    leaf<T> *tmp = this;
    if (tmp->_sentinel) {
      while (!tmp->parent->_sentinel)
        tmp = tmp->parent;
    }
    while (!tmp->right->_sentinel) {
      tmp = tmp->right;
    }
    return tmp;
  }

  leaf<T> *getSuccessor() {
    if (!right->_sentinel) {
      /* std::cerr << "I am in if" << std::endl; */
      return right->getMin();
    }
    leaf<T> *searchedParent = this->parent;
    /* std::cerr << "this is parent:" << searchedParent->value.second <<
     * std::endl; */
    leaf<T> *tmp = this;
    while (!searchedParent->_sentinel && tmp == searchedParent->right) {
      /* std::cerr << "I am in else" << std::endl; */
      tmp = searchedParent;
      searchedParent = searchedParent->parent;
    }
    return searchedParent;
  }

  leaf<T> *getPredecessor() {
    if (!left->_sentinel) {
      return left->getMax();
    }
    leaf<T> *searchedParent = parent;
    leaf<T> *tmp = this;
    while (!searchedParent->_sentinel && tmp == searchedParent->left) {
      tmp = searchedParent;
      searchedParent = searchedParent->parent;
    }
    return searchedParent;
  }

  leaf<T> *getMin() {
    leaf<T> *tmp = this;
    if (tmp->_sentinel) {
      while (!tmp->parent->_sentinel)
        tmp = tmp->parent;
    }
    while (!tmp->left->_sentinel) {
      tmp = tmp->left;
    }
    return tmp;
  }

  ~leaf(){};
  leaf *children[2];
  T value;
  // int key;
  bool _sentinel;
  leaf *parent;
  enum color_t color;

private:
};

template <typename T, typename U>
bool operator==(const leaf<T> &lhs, const leaf<U> &rhs) {
  return lhs.value == rhs.value;
}

template <class T, class Compare = std::less<T>,
          class Alloc = std::allocator<leaf<T>>>
class tree {
  typedef T key_value_type;
  typedef Alloc allocator_type;
  typedef Compare value_compare;
  typedef leaf<T> leaf_type;
  typedef leaf<T> *leaf_ptr;
  typedef std::size_t size_type;

public:
  tree(const value_compare &comp = value_compare(),
       const allocator_type &alloc = allocator_type())
      : _comparator(comp), _allocator(alloc) {
    // sentinel = new leaf_type(1);
    sentinel = _allocator.allocate(sizeof(sentinel));
    _allocator.construct(sentinel, 1);

    // sentinel = _allocator(leaf_type(1));
    root = sentinel;
    cursor = root;
    size = 0;
  };

  ~tree() {
    deallocate(root);
    delete sentinel;
  };

  void deallocate(leaf_type *node) {
    if (node->_sentinel)
      return;
    deallocate(node->children[0]);
    deallocate(node->children[1]);
    delete node;
  }

  leaf_type *min() { return min_rec(root); }
  leaf_type *min() const { return min_rec(root); }
  leaf_type *max() { return max_rec(root); }
  leaf_type *max() const { return max_rec(root); }
  leaf_type *min(leaf_type *subtree) const { return min_rec(subtree); }
  leaf_type *max(leaf_type *subtree) const { return max_rec(subtree); }

  leaf_type *next(const key_value_type &val) const {
    cursor = root;
    cursor = find(val);
    if (cursor->_sentinel)
      return sentinel;
    if (!cursor->children[1]->_sentinel)
      return min(cursor->children[1]);
    leaf_type *parent = cursor->parent;
    while (!parent->_sentinel && cursor == parent->children[1]) {
      cursor = parent;
      parent = parent->parent;
    }
    return parent;
  }

#define RotateDir(N, dir) RotateDirRoot(N, dir)
#define RotateLeft(N) RotateDirRoot(N, LEFT)
#define RotateRight(N) RotateDirRoot(N, RIGHT)
#define childDir(N) (N == (N->parent)->right ? RIGHT : LEFT)
#define LEFT 0
#define RIGHT 1
#define left children[LEFT]
#define right children[RIGHT]

  void RB_transplant(leaf_type *og, leaf_type *ng) {
    if (og->parent->_sentinel) {
      root = ng;
    } else if (og == og->parent->left) {
      og->parent->left = ng;
    } else {
      og->parent->right = ng;
    }
    ng->parent = og->parent;
  }

  void delete_rb(key_value_type &val) {
    cursor = find(val);
    if (cursor->_sentinel)
      return;
    RB_delete(cursor);
  }

  void RBDeleteFixUp(leaf_type *pNode) {
    leaf_type *pAidNode = NULL;
    while ((pNode != root) && (pNode->color == BLACK)) {
      if (pNode == pNode->parent->left) {
        pAidNode = pNode->parent->right; // pAidNode is pNode's brother

        // CASE1: pNode's brother is RED:
        // * Paint pNode's brother(pAidNode) BLACK
        // * Paint pNode's parent RED
        // * Left Rotate pNode's parent
        // * point pAidNode to pNode's Parent right children
        if (pAidNode->color == RED) {
          pAidNode->color = BLACK;
          pNode->parent->color = RED;
          RotateLeft(pNode->parent);
          pAidNode = pNode->parent->right;
          continue;
        } // CASE1

        // CASE2: pNode's brother is BLACK and both his childrens are BLACK
        // * Paint pNode's brother(pAideNode) RED
        // * point pNode to pNode's parent
        if ((pAidNode->left->color == BLACK) &&
            (pAidNode->right->color == BLACK)) {
          pAidNode->color = RED;
          pNode = pNode->parent;
          continue;
        } // CASE2

        // CASE3: pNode's brother and his brother right children is BLACK
        //  * Paint pAidNode LEFT children as BLACK
        //  * Paint pAidNode as RED
        //  * Right Rotate pAidNode
        //  * point pAidNode to pNode parent right children
        else if (pAidNode->right->color == BLACK) {
          pAidNode->left->color = BLACK;
          pAidNode->color = RED;
          RotateRight(pAidNode);
          pAidNode = pNode->parent->right;
          continue;
        } // CASE3

        // CASE4: pNode's brother is BLACK, and his brother right children is
        // RED
        //  * Paint pAidNode as pNode's parent
        //  * Paint pNode's parent BLACK
        //  * Paint pAidNode right children BLACK
        //  * Left Rotate pNode's parent
        //  * Set pNode as the new root
        pAidNode->color = pNode->parent->color;
        pNode->parent->color = BLACK;
        pAidNode->right->color = BLACK;
        RotateLeft(pNode->parent);
        pNode = root;
      } else {
        pAidNode = pNode->parent->left; // pAidNode is pNode's brother

        // CASE1: pNode's brother is RED:
        // * Paint pNode's brother(pAidNode) BLACK
        // * Paint pNode's parent RED
        // * Left Rotate pNode's parent
        // * point pAidNode to pNode's Parent right children
        if (pAidNode->color == RED) {
          pAidNode->color = BLACK;
          pNode->parent->color = RED;
          RotateRight(pNode->parent);
          pAidNode = pNode->parent->left;
          continue;
        } // CASE1

        // CASE2: pNode's brother is BLACK and both his childrens are BLACK
        // * Paint pNode's brother(pAideNode) RED
        // * point pNode to pNode's parent
        if ((pAidNode->right->color == BLACK) &&
            (pAidNode->left->color == BLACK)) {
          pAidNode->color = RED;
          pNode = pNode->parent;
          continue;
        } // CASE2

        // CASE3: pNode's brother and his brother right children is BLACK
        //  * Paint pAidNode LEFT children as BLACK
        //  * Paint pAidNode as RED
        //  * Right Rotate pAidNode
        //  * point pAidNode to pNode parent right children
        else if (pAidNode->left->color == BLACK) {
          pAidNode->right->color = BLACK;
          pAidNode->color = RED;
          RotateLeft(pAidNode);
          pAidNode = pNode->parent->left;
          continue;
        } // CASE3

        // CASE4: pNode's brother is BLACK, and his brother right children is
        // RED
        //  * Paint pAidNode as pNode's parent
        //  * Paint pNode's parent BLACK
        //  * Paint pAidNode right children BLACK
        //  * Left Rotate pNode's parent
        //  * Set pNode as the new root
        pAidNode->color = pNode->parent->color;
        pNode->parent->color = BLACK;
        pAidNode->left->color = BLACK;
        RotateRight(pNode->parent);
        pNode = root;
      }
    } // while
    pNode->color = BLACK;
  }

  void RB_delete(leaf_type *tbdel) {
    leaf_type *y = tbdel;
    leaf_type *x;
    enum color_t y_original_color = y->color;

    if (tbdel->left->_sentinel) {
      x = tbdel->right;
      RB_transplant(tbdel, tbdel->left);
    } else if (tbdel->right->_sentinel) {
      x = tbdel->left;
      RB_transplant(tbdel, tbdel->left);
    } else {
      y = min(tbdel->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == tbdel) {
        x->parent = y;
      } else {
        RB_transplant(y, y->right);
        y->right = tbdel->right;
        y->right->parent = y;
      }
      RB_transplant(tbdel, y);
      y->left = tbdel->left;
      y->left->parent = y;
      y->color = tbdel->color;
    }
    if (y_original_color == BLACK) {
      RBDeleteFixUp(x);
    }
    delete tbdel;
  }

  leaf_type *prev(key_value_type val) const {
    cursor = find(val);
    if (cursor->_sentinel)
      return sentinel;
    if (!cursor->children[0]->_sentinel)
      return max(cursor->children[0]);
    leaf_type *parent = cursor->parent;
    while (!parent->_sentinel && cursor == parent->children[0]) {
      cursor = parent;
      parent = parent->parent;
    }
    return parent;
  }

  leaf_type *find(const key_value_type &val) const {
    if (!size)
      return sentinel;
    cursor = root;
    return find_rec(val);
  }

  leaf_type *find_rec(const key_value_type &val) const {
    if (val.first == cursor->value.first)
      return cursor;
    if (!_comparator(cursor->value, val)) {
      // if (cursor->value.first > val.first) {
      if (cursor->children[0]->_sentinel)
        return sentinel;
      cursor = cursor->left;
      return find_rec(val);
    }
    if (cursor->children[1]->_sentinel)
      return sentinel;
    cursor = cursor->right;
    return find_rec(val);
  }

  leaf_type *min_rec(leaf_type *ptr) const {
    if (ptr->children[0]->_sentinel) {
      return ptr;
    }
    return min_rec(ptr->children[0]);
  }

  leaf_type *max_rec(leaf_type *ptr) const {
    if (ptr->children[1]->_sentinel) {
      return ptr;
    }
    return max_rec(ptr->children[1]);
  }

  // deletion
  bool delete_node(int key) {
    leaf_type *tbdel = find(key);
    int ret = delete_node_rec(*tbdel);
    return ret;
  }

  bool delete_node_rec(leaf_type &tbdel) {
    if (tbdel._sentinel) {
      return false;
    }
    if (!tbdel.children[1]->_sentinel && !tbdel.children[0]->_sentinel) {
      tbdel.value = min(tbdel.children[1])->value;
      tbdel.key = min(tbdel.children[1])->key;
      return delete_node_rec(*min(tbdel.children[1]));
    } else {
      if (!tbdel.children[0]->_sentinel) {
        tbdel.key = tbdel.children[0]->key;
        tbdel.value = tbdel.children[0]->value;
        *tbdel.children[0] = *sentinel;
        return true;
      } else if (!tbdel.children[1]->_sentinel) {
        tbdel.key = tbdel.children[1]->key;
        tbdel.value = tbdel.children[1]->value;
        *tbdel.children[1] = *sentinel;
      } else {
        tbdel = *sentinel;
      }
      return true;
    }
  }

  leaf_type *RotateDirRoot(leaf_type *P, int dir) { // dir ∈ { LEFT, RIGHT }
    leaf_type *G = P->parent;
    leaf_type *S = P->children[1 - dir];
    leaf_type *C;
    if (S->_sentinel)
      return S; // pointer to true node required
    C = S->children[dir];
    P->children[1 - dir] = C;
    if (!C->_sentinel)
      C->parent = P;
    S->children[dir] = P;
    P->parent = S;
    S->parent = G;
    if (!G->_sentinel)
      G->children[P == G->right ? RIGHT : LEFT] = S;
    else
      root = S;
    return S; // new root of subtree
  }

  bool insert(key_value_type val) {
    int side = 0;
    leaf_type *parent;
    leaf_type *grandparent;
    leaf_type *uncle;
    int dir;

    if (!size) {
      // root = new leaf_type(val, sentinel);
      root = _allocator.allocate(sizeof(leaf<key_value_type>));
      _allocator.construct(root, leaf_type(val, sentinel));
      root->color = BLACK;
      root->parent = sentinel;
      size++;
      return true;
    }
    side = insert_node(val);
    dir = side - 1;
    cursor = find(val);
    while (!(parent = cursor->parent)->_sentinel) {
      // IF the parent is black its all good, just return
      if (cursor->parent->color == BLACK)
        return true;
      // from now on we know the parent is red
      if ((grandparent = parent->parent)->_sentinel)
        goto Case_parent_is_root_and_red;
      // else parent is red and grandparent is a sentinel
      dir = childDir(parent);
      uncle = grandparent->children[1 - dir];
      if (uncle->color == BLACK)
        goto Case_parent_is_red_uncle_is_black;
      parent->color = BLACK;
      uncle->color = BLACK;
      grandparent->color = RED;
      cursor = grandparent;
    }
  Case_parent_is_root_and_red: // P is the root and red:
    parent->color = BLACK;
    return true;
  Case_parent_is_red_uncle_is_black:
    if (cursor == parent->children[1 - dir]) {
      RotateDir(parent, dir);
      cursor = parent;
      parent = grandparent->children[dir];
    }
    RotateDirRoot(grandparent, 1 - dir);
    parent->color = BLACK;
    grandparent->color = RED;
    return true; // insertion complete
    return false;
  };

  void Shift_Nodes(leaf_type *parent, leaf_type *child) {
    if (parent->parent->_sentinel) {
      root = child;
    } else if (childDir(parent) == 0) {
      parent->parent->left = child;
    } else {
      parent->parent->right = child;
    }
    if (!child->parent->_sentinel) {
      child->parent = parent->parent;
    }
  }

  int insert_node(key_value_type val) {
    if (!size) {
      // root = new leaf_type(val, sentinel, sentinel);
      root = _allocator.allocate(sizeof(leaf_type));
      _allocator.construct(root, leaf_type(val, sentinel, sentinel));
      size++;
      return true;
    }
    cursor = root;
    return insert_rec(val);
  }

  leaf_type *getLowerBound(const key_value_type &val) const {
    leaf_type *node;
    node = find(val);
    if (node->_sentinel) {
      node = next(val);
    }
    return node;
  }

  leaf_type *getUpperBound(const key_value_type &val) const {
    leaf_type *node;
    node = find(val);
    if (node->_sentinel) {
      node = prev(val);
    }
    return node;
  }

  int insert_rec(key_value_type &val) {
    // if (value_compare(val, cursor))
    //   return false;
    if (_comparator(val, cursor->value)) {
      if (cursor->children[0]->_sentinel) {
        // cursor->children[0] = new leaf_type(val, cursor, sentinel);
        cursor->left = _allocator.allocate(sizeof(leaf_type));
        _allocator.construct(cursor->left, leaf_type(val, cursor, sentinel));
      } else {
        cursor = cursor->children[0];
        insert_rec(val);
      }
      return 1;
    } else {
      if (cursor->children[1]->_sentinel) {
        // cursor->children[1] = new leaf_type(val, cursor, sentinel);
        cursor->right = _allocator.allocate(sizeof(leaf_type));
        _allocator.construct(cursor->right, leaf_type(val, cursor, sentinel));
      } else {
        cursor = cursor->children[1];
        insert_rec(val);
      }
      return 2;
    }
    return false;
  };

  void printBT() { printBT(" ", root, false); }

  void printBT(const std::string &prefix, const leaf_type *node, bool isLeft) {
    if (!node->_sentinel) {
      std::cout << prefix;
      std::cout << (isLeft ? "├──" : "└──");
      if (node->color == RED)
        std::cout << "\x1B[31m" << node->value.second << "\033[0m\t\t"
                  << std::endl;
      else
        std::cout << node->value.second << std::endl;
      printBT(prefix + (isLeft ? "│   " : "    "), node->children[0], true);
      printBT(prefix + (isLeft ? "│   " : "    "), node->children[1], false);
    }
  }

  leaf_type *get_root() { return root; }
  leaf_type *get_sentinel() { return sentinel; }
  size_type getSize() const { return 1; }

protected:
  leaf_type *sentinel;
  leaf_type *root;
  mutable leaf_type *cursor;
  size_t size;
  Compare _comparator;
  allocator_type _allocator;
};
} // namespace ft
#endif
