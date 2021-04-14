#include <iostream>
#include <ctime>
#include <vector>
#include "../include/Skiplist.h"

using T = double;
#define NUM_NODES 100

void treapTest();

int main() {
  srand(time(nullptr));
//  Treap<T>::test(NUM_NODES);
  Skiplist<T>::test(NUM_NODES);
  return 0;
}
