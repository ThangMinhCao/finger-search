#include <iostream>
#include <cstdlib>
#include "../include/Random.h"
#include "../include/Treap.h"
#include "../include/TreePrinter.h"

int main() {
  Treap treap = Treap();

  for (int i = 0; i < 10; i++) {
    treap.add(Random::getInt(1, 100));
  }
  treap.display();

  return 0;
}
