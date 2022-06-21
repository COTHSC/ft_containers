#include <iostream>
#include <stdlib.h>
#include <unistd.h>

enum color_t { BLACK, RED };

class leaf {
public:
  // TODO this constructor is used to insert new leaves with a value, I really
  // shouldnt need  the default sentinel value here...
  leaf(int key, std::string value, leaf *root, leaf *sentinel,
       int is_sentinel = 0)
      : key(key), value(value), _sentinel(is_sentinel), parent(root),
        color(RED) {
    children[1] = sentinel;
    children[0] = sentinel;
  };

  leaf(int sentinel = 0)
      : _sentinel(sentinel), key(0), value(" "), color(BLACK){};
  leaf(leaf *sentinel) {
    children[1] = sentinel;
    children[0] = sentinel;
  };
  ~leaf(){};
  leaf *parent;
  leaf *children[2];
  std::string value;
  int key;
  bool _sentinel;
  enum color_t color;

private:
};

class tree {
public:
  tree() {
    sentinel = new leaf(1);
    root = sentinel;
    cursor = root;
    size = 0;
  };
  ~tree() {
    deallocate(root);
    delete sentinel;
  };

  void deallocate(leaf *node) {
    if (node->_sentinel)
      return;
    deallocate(node->children[0]);
    deallocate(node->children[1]);
    delete node;
  }
  leaf *min() { return min_rec(root); }
  leaf *max() { return max_rec(root); }
  leaf *min(leaf *subtree) { return min_rec(subtree); }
  leaf *max(leaf *subtree) { return max_rec(subtree); }

  leaf *next(int key) {
    cursor = root;
    cursor = find(key);
    if (cursor->_sentinel)
      return sentinel;
    if (!cursor->children[1]->_sentinel)
      return min(cursor->children[1]);
    leaf *parent = cursor->parent;
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

  void RB_transplant(leaf *og, leaf *ng) {
    if (og->parent->_sentinel) {
      root = ng;
    } else if (og == og->parent->left) {
      og->parent->left = ng;
    } else {
      og->parent->right = ng;
    }
    ng->parent = og->parent;
    // delete og;
    // TODO need to deallocate the node right about here
  }

  void delete_rb(int index) {
    cursor = find(index);
    if (cursor->_sentinel)
      return;
    RB_delete(cursor);
  }

  void RBDeleteFixUp(leaf *pNode) {
    leaf *pAidNode = NULL;
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

  void RB_delete_fixup(leaf *x) {
    leaf *w;
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        w = x->parent->right;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          RotateLeft(x->parent);
          w = x->parent->right;
        }
        if (w->left->color == BLACK && w->right->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          RotateRight(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        RotateLeft(x->parent);
        x = root;
      }
      x->color = BLACK;
    }
  }

  void RB_delete(leaf *tbdel) {
    leaf *y = tbdel;
    leaf *x;
    enum color_t y_original_color = y->color;

    if (tbdel->left->_sentinel) {
      x = tbdel->right;
      RB_transplant(tbdel, tbdel->left);
      // printBT();
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
      // RB_delete_fixup(x);
      RBDeleteFixUp(x);
    }
    delete tbdel;
  }

  leaf *prev(int key) {
    cursor = find(key);
    if (cursor->_sentinel)
      return sentinel;
    if (!cursor->children[0]->_sentinel)
      return max(cursor->children[0]);
    leaf *parent = cursor->parent;
    while (!parent->_sentinel && cursor == parent->children[0]) {
      cursor = parent;
      parent = parent->parent;
    }
    return parent;
  }

  leaf *find(int key) {
    if (!size)
      return sentinel;
    return find_rec(key, root);
  }

  leaf *min_rec(leaf *ptr) {
    if (ptr->children[0]->_sentinel) {
      return ptr;
    }
    return min_rec(ptr->children[0]);
  }

  leaf *max_rec(leaf *ptr) {
    if (ptr->children[1]->_sentinel) {
      return ptr;
    }
    return max_rec(ptr->children[1]);
  }

  leaf *find_rec(int key, leaf *ptr) {
    if (ptr->key == key)
      return ptr;
    if (ptr->key > key) {
      if (ptr->children[0]->_sentinel)
        return sentinel;
      return find_rec(key, ptr->children[0]);
    }
    if (ptr->children[1]->_sentinel)
      return sentinel;
    return find_rec(key, ptr->children[1]);
  }

  void RB_Transplant(leaf *u, leaf *v) {
    if (root == sentinel) {
      root = v;
    } else if (u == u->parent->children[0]) {
      u->parent->children[0] = v;
    } else {
      u->parent->children[1] = v;
    }
    v->parent = u->parent;
  }
  // deletion
  bool delete_node(int key) {
    leaf *tbdel = find(key);
    int ret = delete_node_rec(*tbdel);
    return ret;
  }

  bool delete_node_rec(leaf &tbdel) {
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

  leaf *RotateDirRoot(leaf *P, int dir) { // dir ∈ { LEFT, RIGHT }
    leaf *G = P->parent;
    leaf *S = P->children[1 - dir];
    leaf *C;
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

  bool insert(int key, std::string val) {
    int side = 0;
    leaf *parent;
    leaf *grandparent;
    leaf *uncle;
    int dir;

    if (!size) {
      root = new leaf(key, val, sentinel, sentinel);
      root->color = BLACK;
      size++;
      return true;
    }
    side = insert_node(key, val);
    // printBT();
    dir = side - 1;
    cursor = find(key);
    // std::cerr << cursor->key << std::endl;

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

  //   1    Shift-Nodes(T, u, v)
  // 2      if u.parent = NIL then
  // 3        T.root := v
  // 4      else if u = u.parent.left then
  // 5        u.parent.left := v
  // 5      else
  // 6        u.parent.right := v
  // 7      end if
  // 8      if v ≠ NIL then
  // 9        v.parent := u.parent
  // 10     end if

  void Shift_Nodes(leaf *parent, leaf *child) {
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
  // 1    BST-Delete(T, z)
  // 2      if z.left = NIL then
  // 3        Shift-Nodes(T, z, z.right)
  // 4      else if z.right = NIL then
  // 5        Shift-Nodes(T, z, z.left)
  // 6      else
  // 7        y := Tree-Successor(z)
  // 8        if y.parent ≠ z then
  // 9          Shift-Nodes(T, y, y.right)
  // 10         y.right := z.right
  // 11         y.right.parent := y
  // 12       end if
  // 13       Shift-Nodes(T, z, y)
  // 14       y.left := z.left
  // 15       y.left.parent := y
  // 16     end if
  // bool BST_Delete(leaf *node) {
  //   if (node->children[0]->_sentinel) {
  //     Shift_Nodes(node, node->right);
  //   } else if (node->children[1]->_sentinel) {
  //     Shift_Nodes(node, node->left);
  //   }
  //   else {
  //
  //   }
  // }
  // insert can probably benefit from more synergy with search or find,
  // especially since find returns the correctly positioned sentinel node if no
  // matching node is found.
  int insert_node(int key, std::string val) {
    if (!size) {
      root = new leaf(key, val, sentinel, sentinel);
      size++;
      return true;
    }
    cursor = root;
    return insert_rec(key, val);
  }

  int insert_rec(int key, std::string val) {
    if (key == cursor->key)
      return false;
    if (key < cursor->key) {
      if (cursor->children[0]->_sentinel)
        cursor->children[0] = new leaf(key, val, cursor, sentinel);
      else {
        cursor = cursor->children[0];
        insert_rec(key, val);
      }
      return 1;
    } else {
      if (cursor->children[1]->_sentinel)
        cursor->children[1] = new leaf(key, val, cursor, sentinel);
      else {
        cursor = cursor->children[1];
        insert_rec(key, val);
      }
      return 2;
    }
    return false;
  };

  bool delete_leaf(int key) {
    cursor = find(key);
    leaf *parent = cursor->parent;
    leaf *sibling;
    leaf *close_nephew;
    leaf *distant_nephew;
    int dir;

    dir = childDir(cursor);
    parent->children[dir] = sentinel;

    if (cursor->_sentinel) {
      return false;
    }
    if (cursor == root && !cursor->left->_sentinel &&
        !cursor->right->_sentinel) {
      size = 0;
      delete cursor;
      root = sentinel;
      return true;
    }

    if (!cursor->left->_sentinel && !cursor->right->_sentinel) {
      delete_node(cursor->key);
    }

    if (cursor->left->_sentinel && cursor->right->_sentinel &&
        cursor->color == RED) {
      delete cursor;
      cursor = sentinel;
      return true;
    }
    // return true;

    while (!(parent = cursor->parent)->_sentinel) {
      sibling = parent->children[1 - dir];
      distant_nephew = sibling->children[1 - dir];
      close_nephew = sibling->children[dir];
      if (sibling->color == RED) {
        goto Case_sibling;
        if (close_nephew->color == RED)
          goto Case_5;
        if (parent->color == RED)
          goto Case_4;
        sibling->color = RED;
        cursor = parent;
      }
    }
    return true;
  Case_sibling:
    RotateDirRoot(parent, dir);
    parent->color = RED;
    sibling->color = BLACK;
    sibling = close_nephew;
    distant_nephew = sibling->children[1 - dir];
    if (distant_nephew->color == RED)
      goto Case_6;
    close_nephew = sibling->children[dir];
    if (close_nephew->color == RED)
      goto Case_5;

  Case_4:
    sibling->color = RED;
    parent->color = BLACK;
    return true;

  Case_5:
    RotateDir(sibling, 1 - dir);
    sibling->color = RED;
    close_nephew->color = BLACK;
    distant_nephew = sibling;
    sibling = close_nephew;

  Case_6:
    RotateDirRoot(cursor, dir);
    sibling->color = parent->color;
    parent->color = BLACK;
    distant_nephew->color = BLACK;
    return true;
  }

  void printBT(const std::string &prefix, const leaf *node, bool isLeft) {
    if (!node->_sentinel) {
      std::cout << prefix;
      std::cout << (isLeft ? "├──" : "└──");
      //      std::system("Color E4");
      //      std::cerr << "\x1B[31mTexting\033[0m\t\t" << std::endl;
      if (node->color == RED)
        std::cout << "\x1B[31m" << node->value << "\033[0m\t\t" << std::endl;
      else
        std::cout << node->value << std::endl;

      printBT(prefix + (isLeft ? "│   " : "    "), node->children[0], true);
      printBT(prefix + (isLeft ? "│   " : "    "), node->children[1], false);
    }
  }

  void printBT() { printBT(" ", root, false); }

protected:
  leaf *sentinel;
  leaf *root;
  leaf *cursor;
  size_t size;
};

void printBT(const std::string &prefix, const leaf *node, bool isLeft) {
  if (node != nullptr) {
    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << node->value << std::endl;
    printBT(prefix + (isLeft ? "│   " : "    "), node->children[0], true);
    printBT(prefix + (isLeft ? "│   " : "    "), node->children[1], false);
  }
}

void printBT(const leaf *node) { printBT("", node, false); }

int main() {

  // tree elm;
  // elm.insert(3, "three");
  // elm.insert(1, "one");
  // elm.insert(5, "five");
  // elm.insert(11, "eleven");
  // elm.insert(9, "nine");
  // elm.insert(2, "two");
  // elm.insert(4, "four");
  // elm.insert(10, "ten");
  // elm.insert(12, "twelve");
  // elm.insert(13, "thirteen");
  // elm.insert(5, "five");
  // elm.insert(6, "six");
  // elm.insert(7, "seven");
  // elm.insert(8, "eight");
  // elm.insert(8, "eight");
  // elm.insert(8, "eight");
  // elm.insert(8, "eight");
  // elm.insert(8, "eight");
  // elm.insert(8, "eight");
  // elm.printBT();

  // // std::cerr << "this is the next after 4 " << elm.next(4)->value <<
  // // std::endl; std::cerr << "this is the next after 1 " <<
  // elm.next(1)->value
  // // << std::endl; std::cerr << "this is the next after 9 " <<
  // // elm.next(9)->value << std::endl; std::cerr << "this is the next after 3
  // "
  // // << elm.next(3)->value << std::endl; std::cerr << "this is the prev
  // before 4
  // // " << elm.prev(4)->value << std::endl; std::cerr << "this is the prev
  // before
  // // 1 " << elm.prev(1)->value << std::endl; std::cerr << "this is the prev
  // // before 9 " << elm.prev(9)->value << std::endl; std::cerr << "this is the
  // // prev before 3 " << elm.prev(3)->value << std::endl;

  // // std::cerr << "\n\n";
  // // std::cerr << elm.min()->value << std::endl;
  // // std::cerr << elm.max()->value << std::endl;
  // // std::cerr << elm.find(4)->value << std::endl;
  // // std::cerr << elm.find(1)->value << std::endl;
  // // std::cerr << elm.find(8)->value << std::endl;
  // // std::cerr << elm.find(3)->value << std::endl;
  // // std::cerr << elm.find(100)->value << std::endl;
  // // elm.delete_node(3);
  // // elm.delete_node(9);
  // // elm.delete_node(7);
  // //// elm.delete_node(2);
  // // elm.printBT();

  // tree oak;
  // oak.insert(20, "twenty");
  // oak.insert(3, "three");
  // oak.insert(22, "twenty two");
  // oak.printBT();
  // oak.insert(23, "twenty three");
  // oak.printBT();
  // oak.insert(4, "four");
  // oak.printBT();
  // oak.insert(5, "five");
  // oak.insert(11, "eleven");
  // oak.insert(9, "nine");
  // oak.printBT();
  // oak.printBT();
  // oak.insert(2, "two");
  // oak.insert(4, "four");
  // oak.insert(10, "ten");
  // oak.insert(12, "twelve");
  // oak.printBT();
  // oak.insert(13, "thirteen");
  // oak.insert(5, "five");
  // oak.insert(6, "six");
  // oak.insert(7, "seven");
  // oak.printBT();
  // oak.insert(8, "eight");
  // oak.insert(8, "eight");
  // oak.insert(8, "eight");
  // oak.insert(8, "eight");
  // oak.insert(8, "eight");
  // oak.insert(8, "eight");
  // oak.printBT();
  // tree oak;
  // oak.insert(1, elm.min()->value);
  // // elm.delete_node(elm.min()->key);
  // oak.insert(2, elm.min()->value);
  // // elm.delete_node(elm.min()->key);
  // oak.insert(elm.min()->key, elm.min()->value);
  // // elm.delete_node(elm.min()->key);
  // // oak.insert(elm.min()->key, elm.min()->value);
  // // elm.delete_node(elm.min()->key);
  // // oak.insert(elm.min()->key, elm.min()->value);
  // // elm.delete_node(elm.min()->key);
  // // oak.insert(elm.min()->key, elm.min()->value);
  // // elm.delete_node(elm.min()->key);
  tree yew;
  yew.insert(2, "two");
  // yew.printBT();
  yew.insert(4, "four");
  // yew.printBT();
  yew.insert(10, "ten");
  // yew.printBT();
  yew.insert(3, "three");
  yew.insert(7, "seven");
  yew.insert(10, "ten");
  yew.insert(32, "thirty two");
  yew.insert(6, "six");
  yew.insert(5, "five");

  std::cerr << "this is the tree after all insert" << std::endl;
  yew.printBT();
  std::cerr << std::endl;
  yew.delete_rb(3);

  std::cerr << "this is the tree after 3 " << std::endl;
  yew.printBT();
  std::cerr << std::endl;

  yew.delete_rb(4);

  std::cerr << "this is the tree after 4 " << std::endl;
  yew.printBT();
  std::cerr << std::endl;

  yew.delete_rb(3);
  yew.delete_rb(3);
  yew.delete_rb(2);

  std::cerr << "this is the tree after 2 " << std::endl;
  yew.printBT();
  std::cerr << std::endl;

  // yew.delete_rb(10);
  // yew.delete_rb(3);
  yew.delete_rb(10);

  std::cerr << "this is the tree after 10 " << std::endl;
  yew.printBT();
  std::cerr << std::endl;

  std::cerr << "this is the tree after all delete " << std::endl;
  yew.printBT();
  std::cerr << std::endl;
  // yew.printBT();
  // yew.insert(20, "twenty");
  // yew.insert(30, "thirty");
  // yew.insert(1, "one");
  // yew.printBT();
  return 0;
}
