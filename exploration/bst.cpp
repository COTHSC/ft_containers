#include <iostream>

class leaf {
public:
  leaf(){};
  ~leaf(){};
  leaf *right;
  leaf *left;
  leaf *root;
  int value;
};

leaf *createNode(int value) {
  leaf *res = new leaf;
  if (res) {
    res->value = value;
    res->right = NULL;
    res->left = NULL;
  }
  return res;
}

void printBT(const std::string &prefix, const leaf *node, bool isLeft) {
  if (node != nullptr) {
    std::cout << prefix;

    std::cout << (isLeft ? "├──" : "└──");

    // print the value of the node
    std::cout << node->value << std::endl;

    // enter the next tree level - left and right branch
    printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
    printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
  }
}

void printBT(const leaf *node) { printBT("", node, false); }

int main() {
  leaf *n1 = createNode(1);
  leaf *n2 = createNode(2);
  leaf *n3 = createNode(3);
  leaf *n4 = createNode(4);
  leaf *n5 = createNode(5);
  leaf *n6 = createNode(6);
  n1->left = n2;
  n1->right = n3;
  n3->left = n4;
  n3->right = n5;

  // printTree(n1);
  printBT(n1);
  return 0;
}
