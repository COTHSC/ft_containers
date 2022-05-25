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

  leaf(int sentinel = 0) : _sentinel(sentinel), key(0), value(" "){};
  leaf(leaf *sentinel) {
    children[1] = sentinel;
    children[0] = sentinel;
  };
  ~leaf(){};
  // leaf *right;
  // leaf *left;
  leaf *parent;
  leaf *children[2];
  // index is left = 0
  // right = 1
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

  leaf *find(int key) {
    if (!size)
      return sentinel;
    return find_rec(key, root);
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

  bool delete_node(int key) {
    leaf *tbdel = find(key);
    return delete_node_rec(*tbdel);
  }

  bool delete_node_rec(leaf &tbdel) {
    if (tbdel._sentinel) {
      std::cerr << "NODE WAS NOT FOUND AND COULD NOT BE DELETED" << std::endl;
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

#define LEFT 0
#define RIGHT 1
#define left children[LEFT]
#define right children[RIGHT]

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

#define RotateDir(N, dir) RotateDirRoot(N, dir)
#define RotateLeft(N) RotateDirRoot(T, N, LEFT)
#define RotateRight(N) RotateDirRoot(T, N, RIGHT)
#define childDir(N) (N == (N->parent)->right ? RIGHT : LEFT)

  bool RBinsert(int key, std::string val) {
    int side = 0;
    leaf *grandparent;
    leaf *uncle;

    if (!size) {
      root = new leaf(key, val, sentinel, sentinel);
      root->color = BLACK;
      size++;
      return true;
    }
    side = insert(key, val);
    int dir = side - 1;

    leaf *parent = cursor->parent;
    leaf *P = cursor->parent;
    cursor = find(key);

    while (!(parent = cursor->parent)->_sentinel) {
      // IF the parent is black its all good, just return
      if (cursor->parent->color == BLACK)
        return true;

      // from now on we know the parent is red

      if ((grandparent = parent->parent)
              ->_sentinel) // if the grandparent is sentinel go to case 4
        goto Case_I4;

      // else parent is red and grandparent is a sentinel

      dir = childDir(
          parent); // on which side of the grandparent is parent located
      uncle = grandparent->children[1 - dir]; // thats just how uncles work
                                              //
      if (uncle->_sentinel ||
          uncle->color ==
              BLACK) // if the uncle is a sentinel or is black go to case I56
        goto Case_I56;
      parent->color = BLACK;
      uncle->color = BLACK;
      grandparent->color = RED;
      cursor = grandparent;
    }

  Case_I4: // P is the root and red:
    parent->color = BLACK;
    return true;                               // insertion complete
                                               //
  Case_I56:                                    // P red && U black:
    if (cursor == parent->children[1 - dir]) { // Case_I5 (P red && U black && N
                                               // inner grandchild of G):
      RotateDir(parent, dir);                  // P is never the root
      cursor = parent;                         // new current node
      parent = grandparent->children[dir];     // new parent of N
      // fall through to Case_I6
    }
    // end of RBinsert1
    // Case_I6 (P red && U black && N outer grandchild of G):
    RotateDirRoot(grandparent, 1 - dir); // G may be the root
    parent->color = BLACK;
    grandparent->color = RED;
    return true; // insertion complete
                 // end of RBinsert1
  };

  // insert can probably benefit from more synergy with search or find,
  // especially since find returns the correctly positioned sentinel node if no
  // matching node is found.
  int insert(int key, std::string val) {
    if (!size) {
      root = new leaf(key, val, sentinel, sentinel);
      size++;
      return true;
    }
    cursor = root;
    return insert_rec(key, val);
  }

  int insert_rec(int key, std::string val) {
    if (val == cursor->value)
      return 0;
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

  // std::cerr << "this is the next after 4 " << elm.next(4)->value <<
  // std::endl; std::cerr << "this is the next after 1 " << elm.next(1)->value
  // << std::endl; std::cerr << "this is the next after 9 " <<
  // elm.next(9)->value << std::endl; std::cerr << "this is the next after 3 "
  // << elm.next(3)->value << std::endl; std::cerr << "this is the prev before 4
  // " << elm.prev(4)->value << std::endl; std::cerr << "this is the prev before
  // 1 " << elm.prev(1)->value << std::endl; std::cerr << "this is the prev
  // before 9 " << elm.prev(9)->value << std::endl; std::cerr << "this is the
  // prev before 3 " << elm.prev(3)->value << std::endl;

  // std::cerr << "\n\n";
  // std::cerr << elm.min()->value << std::endl;
  // std::cerr << elm.max()->value << std::endl;
  // std::cerr << elm.find(4)->value << std::endl;
  // std::cerr << elm.find(1)->value << std::endl;
  // std::cerr << elm.find(8)->value << std::endl;
  // std::cerr << elm.find(3)->value << std::endl;
  // std::cerr << elm.find(100)->value << std::endl;
  // elm.delete_node(3);
  // elm.delete_node(9);
  // elm.delete_node(7);
  //// elm.delete_node(2);
  // elm.printBT();

  tree oak;
  oak.RBinsert(20, "twenty");
  oak.RBinsert(3, "three");
  oak.RBinsert(22, "twenty two");
  oak.printBT();
  oak.RBinsert(23, "twenty three");
  oak.printBT();
  oak.RBinsert(4, "four");
  oak.printBT();
  oak.RBinsert(5, "five");
  oak.RBinsert(11, "eleven");
  oak.RBinsert(9, "nine");
  oak.printBT();
  oak.printBT();
  oak.RBinsert(2, "two");
  oak.RBinsert(4, "four");
  oak.RBinsert(10, "ten");
  oak.RBinsert(12, "twelve");
  oak.printBT();
  oak.RBinsert(13, "thirteen");
  oak.RBinsert(5, "five");
  oak.RBinsert(6, "six");
  oak.RBinsert(7, "seven");
  oak.printBT();
  oak.RBinsert(8, "eight");
  oak.RBinsert(8, "eight");
  oak.RBinsert(8, "eight");
  oak.RBinsert(8, "eight");
  oak.RBinsert(8, "eight");
  oak.RBinsert(8, "eight");
  oak.printBT();
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

  return 0;
}
