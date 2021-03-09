#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include "../include/Random.h"
#include "../include/Treap.h"
#include <unistd.h>
#include <cmath>

#define NUM_NODES 5000000

using T = int;

int main() {
  using Treap = Treap<T>;

  Treap treap = Treap();
  std::vector<T> addedValues;

  std::ofstream data_file;
  clock_t tStart = clock();
  for (long i = 0; i < NUM_NODES; i++) {
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

  for (int j = 0; j < 16; j++) {
    int jumpSize = 20 * pow(2, j);
    int totalTime = 0; // In number of nodes visited
    int totalTimeBSFromRoot = 0; // In number of nodes visited
    for (T i = 0; i < addedValues.size(); i++) {
      std::cout << "Seaching for: " << findingValue << std::endl;

      Node<T>* FSresult = treap.fingerSearch(findingValue);
      totalTime += treap.numNodesVisited;

      Node<T>* BSresult = treap.search(findingValue);
      totalTimeBSFromRoot += treap.numNodesVisited;

      // if (FSresult != BSresult)
      //   std::cout << "Different Nodes Found: " << BSresult << " & " << FSresult << std::endl;
      int coin = Random::getInt(0, 1);
      if (coin) {
        findingValue += jumpSize;
        if (findingValue >= NUM_NODES) {
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

  return 0;
}
