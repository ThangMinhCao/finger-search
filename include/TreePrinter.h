#ifndef FINGER_SEARCH_TREEPRINTER_H
#define FINGER_SEARCH_TREEPRINTER_H

#include "../include/Treap.h"
#include <iostream>

/**
 * Implementation code of this class is from internet resource
 * Source: https://www.techiedelight.com/c-program-print-binary-tree/
 */
class TreePrinter {
  struct Trunk {
    Trunk *prev;
    std::string str;

    Trunk(Trunk *prev, std::string str) {
      this->prev = prev;
      this->str = str;
    }
  };

  public:
    static void printTree(Treap::Node *root, bool showPriority, Trunk *prev= nullptr, bool isLeft=false);

  private:
    static void showTrunks(Trunk *p);
};

#endif //FINGER_SEARCH_TREEPRINTER_H
