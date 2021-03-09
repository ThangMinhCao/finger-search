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

template<typename T>
Node<T>* Treap<T>::search(T value) {
  numNodesVisited = 0;
  Node<T>* foundNode = binarySearch(value, root, numNodesVisited);
  return foundNode;
}

template<typename T>
Node<T>* Treap<T>::fingerSearch(T value) {
  numNodesVisited = 0;
  if (value == finger->data) return finger;
  // LCA = Lowest common ancestor of the node contains value and the finger
  Node<T>* LCA = root;
  Node<T>* current = finger;
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
  Node<T>* foundNode = binarySearch(value, LCA, numNodesVisited);
  if (foundNode) {
    finger = foundNode;
  }
  return foundNode;
}

template<typename T>
Node<T>* Treap<T>::binarySearch(double value, Node<T>* startNode, int& numNodesVisited) {
  Node<T>* current = startNode;
  while (current && current->data != value) {
    current = (current->data > value) ? current->left : current->right;
    numNodesVisited += 1;
  }
  return current;
}

template<typename T>
bool Treap<T>::treapAdd(double value, Node<T>* &current, Node<T>* prev) {
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

template<typename T>
bool Treap<T>::add(T value) {
  return treapAdd(value, root);
}

template<class T>
bool Treap<T>::treapRemove(double value, Node<T>* &current) {
  if (!current) return false;
  if (value > current->data) return treapRemove(value, current->right);
  if (value < current->data) return treapRemove(value, current->left);

  if (!current->left && !current->right) {
    delete current;
    current = nullptr;
  } else if (!current->left || !current->right) {
    Node<T>* deletingNode = current;
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

template<class T>
bool Treap<T>::remove(T value) {
  return treapRemove(value, root);
}

template<class T>
void Treap<T>::leftRotate(Node<T>* &node) {
  Node<T> *parent = node->parent;
  Node<T> *r = node->right;
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

template<class T>
void Treap<T>::rightRotate(Node<T>* &node) {
  Node<T> *parent = node->parent;
  Node<T> *l = node->left;
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

template<class T>
void Treap<T>::display(bool showPriority) {
  TreePrinter::printTree(root, showPriority);
}

template<class T>
Treap<T>::~Treap() {
  cleanupMemory(root);
}

template<class T>
void Treap<T>::cleanupMemory(Node<T>* node) {
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

template class Treap<int>;
template class Treap<long>;
template class Treap<long long unsigned>;
template class Treap<float>;
template class Treap<double>;