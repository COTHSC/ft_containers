#include <iostream>

class leaf {
public:
  leaf(){};
  ~leaf(){};
  leaf *right;
  leaf *left;
  leaf *root;
  std::string value;
  int key;
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
  leaf *n1 = createNode(1, "one");
  leaf *n2 = createNode(2, "two");
  leaf *n3 = createNode(3, "three");
  leaf *n4 = createNode(4, "four");
  leaf *n5 = createNode(5, "five");
  leaf *n6 = createNode(6, "six");
  n1->left = n2;
  n1->right = n3;
  n3->left = n4;
  n3->right = n5;

  // printTree(n1);
  printBT(n1);
  return 0;
}
