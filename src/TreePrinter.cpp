#include "../include/TreePrinter.h"

void TreePrinter::printTree(Treap::Node *root, bool showPriority, Trunk *prev, bool isLeft) {
  if (root == nullptr)
    return;

  std::string prev_str = "    ";
  Trunk *trunk = new Trunk(prev, prev_str);

  printTree(root->left, showPriority, trunk, true);

  if (!prev)
    trunk->str = "———";
  else if (isLeft) {
    trunk->str = ".———";
    prev_str = "    |";
  } else {
    trunk->str = "`———";
    prev->str = prev_str;
  }

  showTrunks(trunk);
  std::cout << root->data;
  if (showPriority) {
    std::cout << " | " << root->priority;
  }
  std::cout<< std::endl;

  if (prev)
    prev->str = prev_str;
  trunk->str = "    |";

  printTree(root->right, showPriority, trunk, false);
  delete trunk;
}

void TreePrinter::showTrunks(TreePrinter::Trunk *p) {
  if (p == nullptr)
    return;
  showTrunks(p->prev);
  std::cout << p->str;
}
