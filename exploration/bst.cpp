#include <iostream>

class leaf {
public:
  leaf(int key, std::string value, leaf *root, leaf *sentinel,
       int is_sentinel = 0)
      : key(key), value(value), _sentinel(is_sentinel), right(sentinel),
        root(root), left(sentinel){};
  leaf(int sentinel = 0) : _sentinel(sentinel), key(0), value(" "){};
  leaf(leaf *sentinel) : right(sentinel), left(sentinel){};
  ~leaf(){};
  leaf *right;
  leaf *left;
  leaf *root;
  std::string value;
  int key;
  bool _sentinel;

private:
};

class tree {
public:
  tree() {
    sentinel = new leaf(1);
    size = 0;
  };
  ~tree(){};

  leaf *min() { return min_rec(root); }
  leaf *max() { return max_rec(root); }
  leaf *min(leaf *subtree) { return min_rec(subtree); }
  leaf *max(leaf *subtree) { return max_rec(subtree); }

  // BST-Successor(x)
  //   if x.right ≠ NIL then
  //     return Tree-Minimum(x.right)
  //   end if
  //   y := x.parent
  //   while y ≠ NIL and x = y.right then
  //     x := y
  //     y := y.parent
  //   repeat
  //   return y

  leaf *next(int key) {
    cursor = root;
    cursor = find(key);
    if (cursor->_sentinel)
      return sentinel;
    if (!cursor->right->_sentinel)
      return min(cursor->right);
    leaf *parent = cursor->root;
    while (!parent->_sentinel && cursor == parent->right) {
      cursor = parent;
      parent = parent->root;
    }
    return parent;
  }
  // BST-Predecessor(x)
  //    if x.left ≠ NIL then
  //      return Tree-Maximum(x.left)
  //    end if
  //    y := x.parent
  //    while y ≠ NIL and x = y.left then
  //      x := y
  //      y := y.parent
  //    repeat
  //    return y
  leaf *prev(int key) {
    cursor = find(key);
    if (cursor->_sentinel)
      return sentinel;
    if (!cursor->left->_sentinel)
      return max(cursor->left);
    leaf *parent = cursor->root;
    while (!parent->_sentinel && cursor == parent->left) {
      cursor = parent;
      parent = parent->root;
    }
    return parent;
  }

  leaf *min_rec(leaf *ptr) {
    if (ptr->left->_sentinel) {
      return ptr;
    }
    return min_rec(ptr->left);
  }

  leaf *max_rec(leaf *ptr) {
    if (ptr->right->_sentinel) {
      return ptr;
    }
    return max_rec(ptr->right);
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
      if (ptr->left->_sentinel)
        return sentinel;
      return find_rec(key, ptr->left);
    }
    if (ptr->right->_sentinel)
      return sentinel;
    return find_rec(key, ptr->right);
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
    if (!tbdel.right->_sentinel && !tbdel.left->_sentinel) {
      tbdel.value = min(tbdel.right)->value;
      tbdel.key = min(tbdel.right)->key;
      return delete_node_rec(*min(tbdel.right));
    } else {
      if (!tbdel.left->_sentinel) {
        tbdel.key = tbdel.left->key;
        tbdel.value = tbdel.left->value;
        *tbdel.left = *sentinel;
        return true;
      } else if (!tbdel.right->_sentinel) {
        tbdel.key = tbdel.right->key;
        tbdel.value = tbdel.right->value;
        *tbdel.right = *sentinel;
      } else {
        tbdel = *sentinel;
      }
      return true;
    }
  }

  bool insert(int key, std::string val) {
    if (!size) {
      root = new leaf(key, val, sentinel, sentinel);
      size++;
      return true;
    }
    cursor = root;
    return insert_rec(key, val);
  }

  bool insert_rec(int key, std::string val) {
    if (val == cursor->value)
      return 0;
    if (key < cursor->key) {
      if (cursor->left->_sentinel)
        cursor->left = new leaf(key, val, cursor, sentinel);
      else {
        cursor = cursor->left;
        insert_rec(key, val);
      }
      return 1;
    } else {
      if (cursor->right->_sentinel)
        cursor->right = new leaf(key, val, cursor, sentinel);
      else {
        cursor = cursor->right;
        insert_rec(key, val);
      }
      return 1;
    }
    return false;
  };

  void printBT(const std::string &prefix, const leaf *node, bool isLeft) {
    if (node != nullptr) {
      std::cout << prefix;
      std::cout << (isLeft ? "├──" : "└──");
      std::cout << node->value << std::endl;
      printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
      printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
  }

  void printBT() { printBT("", root, false); }

protected:
  leaf *sentinel;
  leaf *root;
  leaf *cursor;
  size_t size;
};

leaf *createNode(int key, std::string val) {
  leaf *res = new leaf;
  if (res) {
    res->value = val;
    res->key = key;
    res->right = NULL;
    res->left = NULL;
  }
  return res;
}

void printBT(const std::string &prefix, const leaf *node, bool isLeft) {
  if (node != nullptr) {
    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << node->value << std::endl;
    printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
    printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
  }
}

void printBT(const leaf *node) { printBT("", node, false); }

int main() {

  tree elm;
  elm.insert(3, "three");
  elm.insert(1, "one");
  elm.insert(5, "five");
  elm.insert(11, "eleven");
  elm.insert(9, "nine");
  elm.insert(2, "two");
  elm.insert(4, "four");
  elm.insert(10, "ten");
  elm.insert(12, "twelve");
  elm.insert(13, "thirteen");
  elm.insert(5, "five");
  elm.insert(6, "six");
  elm.insert(7, "seven");
  elm.insert(8, "eight");
  elm.insert(8, "eight");
  elm.insert(8, "eight");
  elm.insert(8, "eight");
  elm.insert(8, "eight");
  elm.insert(8, "eight");
  elm.printBT();

  std::cerr << "this is the next after 4 " << elm.next(4)->value << std::endl;
  std::cerr << "this is the next after 1 " << elm.next(1)->value << std::endl;
  std::cerr << "this is the next after 9 " << elm.next(9)->value << std::endl;
  std::cerr << "this is the next after 3 " << elm.next(3)->value << std::endl;
  std::cerr << "this is the prev before 4 " << elm.prev(4)->value << std::endl;
  std::cerr << "this is the prev before 1 " << elm.prev(1)->value << std::endl;
  std::cerr << "this is the prev before 9 " << elm.prev(9)->value << std::endl;
  std::cerr << "this is the prev before 3 " << elm.prev(3)->value << std::endl;

  std::cerr << "\n\n";
  std::cerr << elm.min()->value << std::endl;
  std::cerr << elm.max()->value << std::endl;
  std::cerr << elm.find(4)->value << std::endl;
  std::cerr << elm.find(1)->value << std::endl;
  std::cerr << elm.find(8)->value << std::endl;
  std::cerr << elm.find(3)->value << std::endl;
  std::cerr << elm.find(100)->value << std::endl;
  elm.delete_node(3);
  elm.delete_node(9);
  elm.delete_node(7);
  // elm.delete_node(2);
  elm.printBT();

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

  tree oak;
  oak.insert(3, "three");
  oak.insert(1, "one");
  oak.insert(5, "five");
  oak.insert(11, "eleven");
  oak.insert(9, "nine");
  oak.insert(2, "two");
  oak.insert(4, "four");
  oak.insert(10, "ten");
  oak.insert(12, "twelve");
  oak.insert(13, "thirteen");
  oak.insert(5, "five");
  oak.insert(6, "six");
  oak.insert(7, "seven");
  oak.insert(8, "eight");
  oak.insert(8, "eight");
  oak.insert(8, "eight");
  oak.insert(8, "eight");
  oak.insert(8, "eight");
  oak.insert(8, "eight");
  // oak.printBT();

  return 0;
}
