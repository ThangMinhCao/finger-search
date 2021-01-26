#include <iostream>
#include <cstdlib>
#include "../include/Random.h"
#include "../include/Treap.h"
#include "../include/TreePrinter.h"

int main() {
  Treap treap = Treap();

  for (int i = 0; i < 5; i++) {
    treap.add(Random::getInt(1, 10));
  }
  treap.display();

  Treap::Node* foundNode = treap.find(5);
  std::cout << "Found node data: " << foundNode->data << std::endl;
  return 0;
}
