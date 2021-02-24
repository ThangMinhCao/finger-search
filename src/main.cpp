#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include "../include/Random.h"
#include "../include/Treap.h"
#include<unistd.h>

// #define NUM_NODES 5000000
#define NUM_NODES 50000

using T = int;

int main() {
  using Treap = Treap<Node<T>>;

  Treap treap = Treap();
  std::vector<T> addedValues;
  T added = 0;

  std::ofstream data_file;
  clock_t tStart = clock();
  for (long i = 0; i < NUM_NODES; i++) {
    T value;
    if (typeid(T) == typeid(int) || typeid(T) == typeid(long) || typeid(T) == typeid(long long unsigned))
      value = Random::get64Int(0, NUM_NODES);
    if (typeid(T) == typeid(float) || typeid(T) == typeid(double))
      value = Random::getReal(0, NUM_NODES);

    if (treap.add(value)) {
      added++;
      addedValues.push_back(value);
    }
    // std::cout << "Added [" << i << "]: " << value << std::endl;
  }

  // treap.display();
  double initializationTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
  printf("Initialization time taken: %fs\n\n", initializationTime);
  printf("Nodes added: %d\n\n", added);
  // data_file.open("results.txt");
  data_file.open("results.txt", std::ios_base::app);
  data_file << "Number of nodes: " << added << std::endl;
  data_file << "Initialization time taken: " << initializationTime << "s" << std::endl;
  data_file.close();

  // treap.finger = treap.search(addedValues[Random::getInt(0, added)]);
  treap.finger = treap.root->left;

  T findingValue;
  int timesFingerSearchFaster = 0;
  // for (T i = 0; i < 1; i++) {
  for (T i = 0; i < addedValues.size(); i++) {
    // findingValue = Random::getInt(0, NUM_NODES);
    findingValue = addedValues[i];
    int binarySearchNodes = 0;
    int fingerSearchNodes = 0;
    std::cout << "Seaching for: " << findingValue << std::endl;

    tStart = clock();
    Node<T>* BSresult = treap.search(findingValue);
    double binarySearchTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
    binarySearchNodes = treap.numNodesVisited;

    tStart = clock();
    Node<T>* FSresult = treap.fingerSearch(findingValue);
    double fingerSearchTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
    fingerSearchNodes = treap.numNodesVisited;
    if (fingerSearchNodes < binarySearchNodes)
      timesFingerSearchFaster++;

    std::cout << "Finger: " << treap.finger->data << std::endl;
    std::cout << "Time :[BS|FS] " << binarySearchNodes << "|" << fingerSearchNodes << std::endl;

    if (FSresult) {
      std::cout << "Result: " << FSresult->data << std::endl;
    }
    if (FSresult != BSresult)
      std::cout << "Different Nodes Found: " << BSresult << " & " << FSresult << std::endl;
    // usleep(3 * 1000000);
  }

  std::cout << "Total search times: " << addedValues.size() << std::endl;
  std::cout << "# times Finger Search is faster: " << timesFingerSearchFaster << std::endl;

  // // treap.printTotalNodesVisited();
  // printf("Binary search time taken: %fs\n", binarySearchTime);
  // // Output for BinarySearch
  // data_file.open("results.txt", std::ios_base::app);
  // data_file << "Binary Search time taken: " << binarySearchTime << "s" << std::endl;
  // data_file.close();

  // // Output for FingerSearch
  // printf("Finger search time taken: %fs\n\n", fingerSearchTime);
  // data_file.open("results.txt", std::ios_base::app);
  // data_file << "Finger Search time taken:  " << fingerSearchTime << "s" << std::endl << std::endl << std::endl;
  // data_file.close();
  return 0;
}
