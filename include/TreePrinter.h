#ifndef FINGER_SEARCH_TREEPRINTER_H
#define FINGER_SEARCH_TREEPRINTER_H

#include "../include/Treap.h"
#include <iostream>

/**
 * Implementation code of this class is from TechieDelight.com
 * Source: https://www.techiedelight.com/c-program-print-binary-tree/
 */
class TreePrinter {
  struct Trunk {
    Trunk* prev;
    std::string str;

    Trunk(Trunk *prev, std::string str) {
      this->prev = prev;
      this->str = str;
    }
  };

  public:
    template<class Node>
    static void printTree(Node* root, bool showPriority, Trunk* prev= nullptr, bool isLeft=false);

  private:
    static void showTrunks(Trunk *p) {
      if (p == nullptr)
        return;
      showTrunks(p->prev);
      std::cout << p->str;
    };
};

template<class Node>
void TreePrinter::printTree(Node* root, bool showPriority, Trunk* prev, bool isLeft) {
  if (root == nullptr)
    return;

  std::string prev_str = "    ";
  Trunk* trunk = new Trunk(prev, prev_str);

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

#endif //FINGER_SEARCH_TREEPRINTER_H
