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

bool Treap::treapAdd(int value, Node* &current, Node* prev) {
  if (current == nullptr) {
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

bool Treap::remove(int) {
  return true;
}

void Treap::leftRotate(Node* &node) {
  Node *parent = node->parent;
  Node *r = node->right;
  node->parent = r;
  if (r->left != nullptr) {
    r->left->parent = node;
  }
  node->right = r->left;
  r->left = node;
  r->parent = parent;
  if (parent != nullptr) {
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
  if (l->right != nullptr) {
    l->right->parent = node;
 }
  node->left = l->right;
  l->right = node;
  l->parent = parent;
  if (parent != nullptr) {
    if (parent->left == node) {
      parent->left = l;
    } else {
      parent->right = l;
    }
  }
  node = l;
}

void Treap::display() const {
  TreePrinter::printTree(root);
}

Treap::~Treap() {
  cleanupMemory(root);
}

void Treap::cleanupMemory(Node* node) {
  if (node == nullptr) return;
  cleanupMemory(node->left);
  cleanupMemory(node->right);
  delete node;
}
