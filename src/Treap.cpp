#include <iostream>
#include "../include/Treap.h"
#include "../include/Random.h"
#include "../include/TreePrinter.h"

Treap::Node::Node(double value, Node* parent, Node* left, Node* right, Node* leftParent, Node* rightParent) {
  this->data = value;
  this->parent = parent;
  this->left = left;
  this->right = right;
  this->leftParent = leftParent;
  this->rightParent = rightParent;
  priority = Random::getReal(0, 1);
}

Treap::Node *Treap::search(double value) {
  return binarySearch(value, root);
}

Treap::Node *Treap::fingerSearch(double value) {
  if (value == finger->data) return finger;
  // LCA = Lowest common ancestor of the node contains value and the finger
  Node* LCA = root;
  Node* current = finger;
  if (value > finger->data) {
    while (current && current->data <= value) {
      LCA = current;
      current = current->rightParent;
    }
  } else {
    while (current && current->data >= value) {
      LCA = current;
      current = current->leftParent;
    }
  }
  Node* foundNode = binarySearch(value, LCA);
  if (foundNode) {
    finger = foundNode;
  }
  return foundNode;
}

Treap::Node *Treap::binarySearch(double value, Treap::Node* startNode) {
  Node* current = startNode;
  while (current && current->data != value) {
    current = (current->data > value) ? current->left : current->right;
  }
  return current;
}

bool Treap::treapAdd(double value, Node* &current, Node* prev) {
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

bool Treap::add(double value) {
  return treapAdd(value, root);
}

bool Treap::treapRemove(double value, Treap::Node* &current) {
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

bool Treap::remove(double value) {
  return treapRemove(value, root);
}

void Treap::leftRotate(Node* &node) {
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

void Treap::rightRotate(Node* &node) {
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

void Treap::display(bool showPriority) {
  TreePrinter::printTree(root, showPriority);
}

Treap::~Treap() {
  cleanupMemory(root);
}

void Treap::cleanupMemory(Node* node) {
  if (!node) return;
  cleanupMemory(node->left);
  cleanupMemory(node->right);
  delete node;
}

