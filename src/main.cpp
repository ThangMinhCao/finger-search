#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include "../include/Random.h"
#include "../include/Treap.h"
#include<unistd.h>

#define NUM_NODES 500000
// #define NUM_NODES 50000
using T = int;

int main() {
  using Treap = Treap<Node<T>>;

  Treap treap = Treap();
  T added = 0;

  std::ofstream data_file;
  clock_t tStart = clock();
  for (long i = 0; i < NUM_NODES; i++) {
    T value;
    if (typeid(T) == typeid(int) || typeid(T) == typeid(long) || typeid(T) == typeid(long long unsigned))
      value = Random::get64Int(0, NUM_NODES);
    if (typeid(T) == typeid(float) || typeid(T) == typeid(double))
      value = Random::getReal(0, NUM_NODES);

    if (treap.add(value)) added++;
    std::cout << "Added [" << i << "]: " << value << std::endl;
  }
  double initializationTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
  printf("Initialization time taken: %fs\n\n", initializationTime);
  printf("Nodes added: %ds\n\n", added);
  data_file.open("results.txt");
  data_file << "Number of nodes: " << added << std::endl;
  data_file << "Initialization time taken: " << initializationTime << "s" << std::endl;
  data_file.close();

  // For loop to search for random elements with amount = 1000 times of added nodes 
  double binarySearchTime = 0;
  double fingerSearchTime = 0;
  std::vector<T> indicesForSearches;
  T findingValue;
  for (T i = 0; i < added * 10; i++) {
    findingValue = Random::getReal(0, NUM_NODES);
    // std::cout << "Seaching for: " << findingValue << std::endl;

    tStart = clock();
    Node<T>* BSresult = treap.search(findingValue);
    double BStime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
    binarySearchTime += BStime;

    tStart = clock();
    Node<T>* FSresult = treap.fingerSearch(findingValue);
    double FStime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
    fingerSearchTime += FStime;


    if (FSresult != BSresult)
      std::cout << "Different Nodes Found: " << BSresult << " & " << FSresult << std::endl;
    // if (FSresult)
    //   std::cout << "Found: " << FSresult->data << std::endl;
  }

  printf("Binary search time taken: %fs\n", binarySearchTime);
  // Output for BinarySearch
  data_file.open("results.txt", std::ios_base::app);
  data_file << "Binary Search time taken: " << binarySearchTime << "s" << std::endl;
  data_file.close();

  // Output for FingerSearch
  printf("Finger search time taken: %fs\n\n", fingerSearchTime);
  data_file.open("results.txt", std::ios_base::app);
  data_file << "Finger Search time taken:  " << fingerSearchTime << "s" << std::endl << std::endl << std::endl;
  data_file.close();
  return 0;
}
