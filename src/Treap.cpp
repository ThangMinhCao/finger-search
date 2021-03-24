#include <iostream>
#include <fstream>
#include "../include/Treap.h"
#include "../include/TreePrinter.h"

template<class TreapNode>
void Treap<TreapNode>::printTotalNodesVisited() {
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
TreapNode<T>* Treap<T>::search(T value) {
  numNodesVisited = 0;
  TreapNode<T>* foundNode = binarySearch(value, root, numNodesVisited);
  return foundNode;
}

template<typename T>
TreapNode<T>* Treap<T>::fingerSearch(T value) {
  numNodesVisited = 0;
  if (value == finger->data) return finger;
  // LCA = Lowest common ancestor of the node contains value and the finger
  TreapNode<T>* LCA = root;
  TreapNode<T>* current = finger;
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
  TreapNode<T>* foundNode = binarySearch(value, LCA, numNodesVisited);
  if (foundNode) {
    finger = foundNode;
  }
  return foundNode;
}

template<typename T>
TreapNode<T>* Treap<T>::binarySearch(double value, TreapNode<T>* startNode, int& numNodesVisited) {
  TreapNode<T>* current = startNode;
  while (current && current->data != value) {
    current = (current->data > value) ? current->left : current->right;
    numNodesVisited += 1;
  }
  return current;
}

template<typename T>
bool Treap<T>::treapAdd(double value, TreapNode<T>* &current, TreapNode<T>* prev) {
  if (!current) {
    current = new TreapNode(value, prev);
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
bool Treap<T>::treapRemove(double value, TreapNode<T>* &current) {
  if (!current) return false;
  if (value > current->data) return treapRemove(value, current->right);
  if (value < current->data) return treapRemove(value, current->left);

  if (!current->left && !current->right) {
    delete current;
    current = nullptr;
  } else if (!current->left || !current->right) {
    TreapNode<T>* deletingNode = current;
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
void Treap<T>::leftRotate(TreapNode<T>* &node) {
  TreapNode<T> *parent = node->parent;
  TreapNode<T> *r = node->right;
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
void Treap<T>::rightRotate(TreapNode<T>* &node) {
  TreapNode<T> *parent = node->parent;
  TreapNode<T> *l = node->left;
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
void Treap<T>::cleanupMemory(TreapNode<T>* node) {
  if (!node) return;
  cleanupMemory(node->left);
  cleanupMemory(node->right);
  delete node;
}

template<typename T>
void Treap<T>::test(int numNodes) {
  using Treap = Treap<T>;
  Treap treap = Treap();
  std::vector<T> addedValues;

  std::ofstream data_file;
  clock_t tStart = clock();
  for (long i = 0; i < numNodes; i++) {
    // T value;
    // if (typeid(T) == typeid(int) || typeid(T) == typeid(long) || typeid(T) == typeid(long long unsigned))
    //   value = Random::get64Int(0, NUM_NODES);
    // if (typeid(T) == typeid(float) || typeid(T) == typeid(double))
    //   value = Random::getReal(0, NUM_NODES);
    T value = i;

    if (treap.add(value)) {
      addedValues.push_back(value);
    }
  }

  // treap.display();
  double initializationTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
  printf("Initialization time taken: %fs\n\n", initializationTime);
  std::cout << "Nodes added: " << addedValues.size() << std::endl << std::endl;

  data_file.open("results.txt", std::ios_base::app);
  data_file << "Number of nodes: " << addedValues.size() << std::endl;
  data_file << "Initialization time taken: " << initializationTime << "s" << std::endl;
  data_file.close();

  T findingValue = addedValues[addedValues.size() / 2];
  // std::vector<int> searchJumpSizes = {20, 100, 500, 1000, 2500, 5000, 7500, 10000, 25000, 50000};

  for (int j = 0; j < 10; j++) {
    int jumpSize = 20 * pow(2, j);
    int totalTime = 0; // In number of nodes visited
    int totalTimeBSFromRoot = 0; // In number of nodes visited
    for (T i = 0; i < addedValues.size(); i++) {
      std::cout << "Seaching for: " << findingValue << std::endl;

      TreapNode<T>* FSresult = treap.fingerSearch(findingValue);
      totalTime += treap.numNodesVisited;

      TreapNode<T>* BSresult = treap.search(findingValue);
      totalTimeBSFromRoot += treap.numNodesVisited;

      // if (FSresult != BSresult)
      //   std::cout << "Different Nodes Found: " << BSresult << " & " << FSresult << std::endl;
      int coin = Random::getInt(0, 1);
      if (coin) {
        findingValue += jumpSize;
        if (findingValue >= numNodes) {
          findingValue -= 2*jumpSize;
        }
      } else {
        findingValue -= jumpSize;
        if (findingValue < 0) {
          findingValue += 2*jumpSize;
        }
      }
    }
    data_file.open("results.txt", std::ios_base::app);
    data_file << "Jump size: " << jumpSize << std::endl;
    data_file << "Average running time FS: " << ((float)totalTime/(float)addedValues.size()) << std::endl;
    data_file << "Average running time BS: " << ((float)totalTimeBSFromRoot/(float)addedValues.size()) << std::endl;
    data_file.close();
  }
  data_file.open("results.txt", std::ios_base::app);
  data_file << std::endl << std::endl;
  data_file.close();
}

template class TreapNode<int>;
template class TreapNode<long>;
template class TreapNode<long long unsigned>;
template class TreapNode<float>;
template class TreapNode<double>;

template class Treap<int>;
template class Treap<long>;
template class Treap<long long unsigned>;
template class Treap<float>;
template class Treap<double>;