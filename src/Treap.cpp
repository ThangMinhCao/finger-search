#include <iostream>
#include "../include/Treap.h"
#include "../include/Random.h"
#include "../include/TreePrinter.h"

Treap::Node::Node(int value, Node* parent, Node* left, Node* right) {
  this->data = value;
  this->parent = parent;
  this->left = left;
  this->right = right;
  priority = Random::getReal(0, 1);
}

Treap::Node *Treap::find(int value) const {
  Node* current = root;
  while (current && current->data != value) {
    current = (current->data > value) ? current->left : current->right;
  }
  return current;
}

bool Treap::treapAdd(int value, Node* &current, Node* prev) {
  if (!current) {
    current = new Node(value, prev);
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

bool Treap::add(int value) {
  return treapAdd(value, root);
}

bool Treap::treapRemove(int value, Treap::Node* &current) {
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

bool Treap::remove(int value) {
  return treapRemove(value, root);
}

void Treap::leftRotate(Node* &node) {
  Node *parent = node->parent;
  Node *r = node->right;
  node->parent = r;
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

void Treap::display(bool showPriority) const {
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
