#include <iostream>
#include <cstdlib>
#include "../include/Random.h"
#include "../include/Treap.h"

int main() {
  Treap treap = Treap();

  treap.add(10);
  std::cout << "First root" << std::endl;
  std::cout << treap.root->value << std::endl;
  std::cout << treap.root->priority << std::endl;

  treap.add(12);
  std::cout << "\nNew root" << std::endl;
  std::cout << treap.root->value << std::endl;
  std::cout << treap.root->priority << std::endl;

  if (treap.root->left) {
    std::cout << "\nLeft" << std::endl;
    std::cout << treap.root->left->value << std::endl;
    std::cout << treap.root->left->priority << std::endl;
  } else {
    std::cout << "\nRight" << std::endl;
    std::cout << treap.root->right->value << std::endl;
    std::cout << treap.root->right->priority << std::endl;
  }
  return 0;
}
