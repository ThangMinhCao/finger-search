#include <iostream>
#include <fstream>
#include "../include/Treap.h"
#include "../include/TreePrinter.h"

template<class Node>
void Treap<Node>::printTotalNodesVisited() {
  // std::cout << "Total Comparisons [BS|FS]: "
  //           << BSTotalComparisons << " | "
  //           << FSTotalComparisons << std::endl;

  // std::ofstream data_file;
  // data_file.open("results.txt", std::ios_base::app);
  // data_file << "Total Comparisons [BS|FS]: "
  //           << BSTotalComparisons << " | "
  //           << FSTotalComparisons << std::endl;
  // data_file.close();
}

template<class Node>
Node* Treap<Node>::search(double value) {
  numNodesVisited = 0;
  Node* foundNode = binarySearch(value, root, numNodesVisited);
  return foundNode;
}

template<class Node>
Node* Treap<Node>::fingerSearch(double value) {
  numNodesVisited = 0;
  if (value == finger->data) return finger;
  // LCA = Lowest common ancestor of the node contains value and the finger
  Node* LCA = root;
  Node* current = finger;
  if (value > finger->data) {
    while (current && current->data <= value) {
      LCA = current;
      current = current->rightParent;
      numNodesVisited++;
    }
  } else {
    while (current && current->data >= value) {
      LCA = current;
      current = current->leftParent;
      numNodesVisited++;
    }
  }
  numNodesVisited--;
  Node* foundNode = binarySearch(value, LCA, numNodesVisited);
  // if (foundNode) {
  //   finger = foundNode;
  // }
  return foundNode;
  
  // Node* foundNode = binarySearch(value, root, FSTotalComparisons);
  // return foundNode;
}

template<class Node>
Node* Treap<Node>::binarySearch(double value, Node* startNode, int& numNodesVisited) {
  Node* current = startNode;
  while (current && current->data != value) {
    current = (current->data > value) ? current->left : current->right;
    numNodesVisited += 1;
  }
  return current;
}

template<class Node>
bool Treap<Node>::treapAdd(double value, Node* &current, Node* prev) {
  if (!current) {
    current = new Node(value, prev);
    if (prev && prev->left == current) {
      current->rightParent = prev;
      current->leftParent = prev->leftParent;
    } else if (prev && prev->right == current) {
      current->leftParent = prev;
      current->rightParent = prev->rightParent;
    }
    if (!prev) {
      finger = current;
    }
    return true;
  }
  if (value == current->data) return false;
  if (value > current->data) {
    if (!treapAdd(value, current->right, current)) return false;
    if (current->priority > current->right->priority) {
      leftRotate(current);
    }
  } else {
    if (!treapAdd(value, current->left, current)) return false;
    if (current->priority > current->left->priority) {
      rightRotate(current);
    }
  }
  return true;
}

template<class Node>
bool Treap<Node>::add(double value) {
  return treapAdd(value, root);
}

template<class Node>
bool Treap<Node>::treapRemove(double value, Node* &current) {
  if (!current) return false;
  if (value > current->data) return treapRemove(value, current->right);
  if (value < current->data) return treapRemove(value, current->left);

  if (!current->left && !current->right) {
    delete current;
    current = nullptr;
  } else if (!current->left || !current->right) {
    Node* deletingNode = current;
    current = (!current->left) ? current->right : current->left;
    current->parent = deletingNode->parent;
    delete deletingNode;
  } else {
    if (current->left->priority > current->right->priority) {
      leftRotate(current);
      treapRemove(value, current->left);
    } else {
      rightRotate(current);
      treapRemove(value, current->right);
    }
  }
  return true;
}

template<class Node>
bool Treap<Node>::remove(double value) {
  return treapRemove(value, root);
}

template<class Node>
void Treap<Node>::leftRotate(Node* &node) {
  Node *parent = node->parent;
  Node *r = node->right;
  node->parent = r;
  // Handle left and right parents
  node->rightParent = r;
  r->leftParent = node->leftParent;

  if (r->left) {
    r->left->parent = node;
  }
  node->right = r->left;
  r->left = node;
  r->parent = parent;
  if (parent) {
    if (parent->left == node) {
      parent->left = r;
    } else {
      parent->right = r;
    }
  }
  node = r;
}

template<class Node>
void Treap<Node>::rightRotate(Node* &node) {
  Node *parent = node->parent;
  Node *l = node->left;
  node->parent = l;

  // Handle left and right parents
  node->leftParent = l;
  l->rightParent = node->rightParent;

  if (l->right) {
    l->right->parent = node;
 }
  node->left = l->right;
  l->right = node;
  l->parent = parent;
  if (parent) {
    if (parent->left == node) {
      parent->left = l;
    } else {
      parent->right = l;
    }
  }
  node = l;
}

template<class Node>
void Treap<Node>::display(bool showPriority) {
  TreePrinter::printTree(root, showPriority);
}

template<class Node>
Treap<Node>::~Treap() {
  cleanupMemory(root);
}

template<class Node>
void Treap<Node>::cleanupMemory(Node* node) {
  if (!node) return;
  cleanupMemory(node->left);
  cleanupMemory(node->right);
  delete node;
}

template class Node<int>;
template class Node<long>;
template class Node<long long unsigned>;
template class Node<float>;
template class Node<double>;

template class Treap<Node<int>>;
template class Treap<Node<long>>;
template class Treap<Node<long long unsigned>>;
template class Treap<Node<float>>;
template class Treap<Node<double>>;