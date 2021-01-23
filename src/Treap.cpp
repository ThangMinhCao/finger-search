#include <cstdlib>
#include <random>
#include <iostream>
#include "../include/Treap.h"
#include "../include/Random.h"

Treap::Node::Node(int value, Node *parent, Node *left, Node *right) {
  this->value = value;
  this->parent = parent;
  this->left = left;
  this->right = right;
  priority = Random::getReal(0, 1);
}

bool Treap::add(int value) {
  return true;
}

bool Treap::remove(int) {
  return true;
}

void Treap::leftRotate(Node *node) {
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
}

void Treap::rightRotate(Node *node) {
  Node *parent = node->parent;
  Node *l = node->left;
  node->parent = l;
  if (l->right != nullptr) {
    l->right->parent = node;
 }
  node->left = l->right;
  l->right = node;
  l->parent = parent;
  if (node->parent != nullptr) {
    if (parent->left == node) {
      parent->left = l;
    } else {
      parent->right = l;
    }
  }
}
