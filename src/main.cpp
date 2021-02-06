#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include "../include/Random.h"
#include "../include/Treap.h"

int main() {
  std::cout << "hello" << std::endl;
  Treap treap = Treap();
  int added = 0;

  std::ofstream data_file;
  for (long i = 0; i < 50000000; i++) {
    double value = Random::getReal(0, 50000000);
  // for (long i = 0; i < 800; i++) {
  //   long value = Random::get64Int(0, 900);
    if (treap.add(value)) added++;
    std::cout << "Added [" << i << "]: " << value << std::endl;
  }
  clock_t tStart = clock();

  double initializationTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;
  printf("Initialization time taken: %fs\n\n", initializationTime);

  double binarySearchTime = 0;
  double fingerSearchTime = 0;
  std::vector<int> indicesForSearches;
  double findingValue;
  for (int i = 0; i < added * 10; i++) {
    tStart = clock();
    findingValue = Random::getReal(0, 50000);
    Treap::Node* BSresult = treap.search(findingValue);
    binarySearchTime += (double)(clock() - tStart)/CLOCKS_PER_SEC;

    tStart = clock();
    Treap::Node* FSresult = treap.fingerSearch(findingValue);
    // if (FSresult)
    //   std::cout << FSresult->data << std::endl;
    fingerSearchTime += (double)(clock() - tStart)/CLOCKS_PER_SEC;
  }
  
  // Binary Search timer
  // for (int i = 0; i < indicesForSearches.size(); i++) {
  //   treap.search(addedNumbers[indicesForSearches[i]]);
  // }

  printf("Binary search time taken: %fs\n", binarySearchTime);
  // Output for BinarySearch
  data_file.open("results.txt", std::ios_base::app);
  data_file << "Number of nodes: " << added << std::endl;
  data_file << "Initialization time taken: " << initializationTime << "s\n";
  data_file << "\nBinary Search time taken: " << binarySearchTime << "s\n";
  data_file.close();

  // Finger Search timer
  std::cout << std::endl;
  // tStart = clock();
  // for (int i = 0; i < indicesForSearches.size(); i++) {
  //   treap.search(addedNumbers[indicesForSearches[i]]);
  // }
  // double fingerSearchTime = (double)(clock() - tStart)/CLOCKS_PER_SEC;

  // Output for FingerSearch
  printf("Finger search time taken: %fs\n", fingerSearchTime);
  data_file.open("results.txt", std::ios_base::app);
  data_file << "\nFinger Search time taken:  " << fingerSearchTime << "s\n";
  data_file.close();
  return 0;
}
