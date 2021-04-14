#include <random>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "../include/Skiplist.h"
#include "../include/Random.h"

template<class T>
typename Skiplist<T>::Node *Skiplist<T>::newNode(T x, int h) {
  Node *u = (Node *) malloc(sizeof(Node) + (h + 1) * sizeof(Node *));
  u->x = x;
  u->height = h;
//  u->next = new Skiplist<T>::Node*[h+1];
  return u;
}

template<class T>
void Skiplist<T>::deleteNode(Skiplist<T>::Node *u) {
  free(u);
}

template<class T>
typename Skiplist<T>::Node *Skiplist<T>::findPredNode(T x) {
  numNodesVisited = 0;
  Node *u = sentinel;
  int r = h;
  while (r >= 0) {
    numNodesVisited++;
    while (u->next[r] != nullptr && compare(u->next[r]->x, x) < 0) {
      numNodesVisited++;
      u = u->next[r]; // go right in list r
    }
    r--; // go down into list r-1
  }
  return u;
}

template<class T>
T Skiplist<T>::find(T x) {
  Node *u = findPredNode(x);
  return u->next[0] == nullptr ? null : u->next[0]->x;
}

template<class T>
bool Skiplist<T>::add(T x) {
  Node *u = sentinel;
  int r = h;
  int comp = 0;
  while (r >= 0) {
    while (u->next[r] != nullptr
           && (comp = compare(u->next[r]->x, x)) < 0)
      u = u->next[r];
    if (u->next[r] != nullptr && comp == 0)
      return false;
    stack[r--] = u;        // going down, store u
  }
  Node *w = newNode(x, pickHeight());
  while (h < w->height)
    stack[++h] = sentinel; // height increased
  for (int i = 0; i <= w->height; i++) {
    w->next[i] = stack[i]->next[i];
    if (w->next[i])
      w->next[i]->prev = w;
    w->prev = stack[i];
    stack[i]->next[i] = w;
  }
  n++;
  return true;
}

template<class T>
bool Skiplist<T>::remove(T x) {
  bool removed = false;
  Node *u = sentinel, *del;
  int r = h;
  int comp = 0;
  while (r >= 0) {
    while (u->next[r] != nullptr
           && (comp = compare(u->next[r]->x, x)) < 0) {
      u = u->next[r];
    }
    if (u->next[r] != nullptr && comp == 0) {
      removed = true;
      del = u->next[r];
      u->next[r] = u->next[r]->next[r];
      if (u == sentinel && u->next[r] == nullptr)
        h--; // skiplist height has gone down
    }
    r--;
  }
  if (removed) {
    delete del;
    n--;
  }
  return removed;
}

template<class T>
int Skiplist<T>::pickHeight() {
  int z = rand();
  int k = 0;
  int m = 1;
  while ((z & m) != 0) {
    k++;
    m <<= 1;
  }
  return k;
}

template<class T>
void Skiplist<T>::clear() {
  Node *u = sentinel->next[0];
  while (u != NULL) {
    Node *n = u->next[0];
    deleteNode(u);
    u = n;
  }
  memset(sentinel->next, '\0', sizeof(Node *) * h);
  h = 0;
  n = 0;
}

template<class T>
int Skiplist<T>::size() {
  return n;
}

template<class T>
inline
int Skiplist<T>::compare(T &x, T &y) {
  if (x < y) return -1;
  if (y < x) return 1;
  return 0;
}

template<class T>
T Skiplist<T>::fingerSearch(T x) {
  numNodesVisited = 0;
  int level = 1;
  Node* start;
  Node* linearSearchStart = finger[0];
  if (compare(finger[0]->x, x) == -1) {
    while (level <= h &&
            ((finger[level]->next[level] != nullptr
                  && compare(finger[level]->next[level]->x, x) == -1))) {
      std::cout << "Searching right" << std::endl;
      if (compare(finger[level]->x, x) == 0) {
        return x;
      }
      if (compare(linearSearchStart->x, x) == 0) {
        return x;
      }
      linearSearchStart = linearSearchStart->next[0];
      level++;
      numNodesVisited++;
    }
    start = finger[level]->next[level];
  } else {
    while (level  <= h &&
            (compare(finger[level]->x, x) >= 0
              || (finger[level]->next[level] != nullptr
                   && compare(finger[level]->next[level]->x, x) >= 0))) {
      std::cout << "Searching left" << std::endl;

      if (linearSearchStart != sentinel)
        std::cout << "current value: " << linearSearchStart->x << std::endl;

      if (compare(finger[level]->x, x) == 0) return x;

      if (linearSearchStart)
        linearSearchStart = linearSearchStart->prev;
      level++;
      numNodesVisited++;
    }
    if (level > h) {
      level = h;
      start = sentinel;
    } else {
      start = finger[level]->next[level];
    }
  }
  std::cout << "Searching down" << std::endl;
  for (int i = level; i >= 0; i--) {
    numNodesVisited++;
    while (start->next[i] != nullptr && compare(start->next[i]->x, x) < 0) {
      start = start->next[i];
      numNodesVisited++;
    }
    finger[i] = start;
  }
  std::cout << "Searching end" << std::endl;
  return start->next[0] == nullptr ? null : start->next[0]->x;
}

template<typename T>
void Skiplist<T>::test(int numNodes) {
  using List = Skiplist<T>;
  List skiplist = List();
  std::vector<T> addedValues;

  std::ofstream data_file;
  clock_t tStart = clock();
  for (long i = 0; i < numNodes; i++) {
    T value = i;

    if (skiplist.add(value)) {
      addedValues.push_back(value);
    }
  }

  double initializationTime = (double) (clock() - tStart) / CLOCKS_PER_SEC;
  printf("Initialization time taken: %fs\n\n", initializationTime);
  std::cout << "Nodes added: " << addedValues.size() << std::endl << std::endl;

  data_file.open("results.txt", std::ios_base::app);
  data_file << "Number of nodes: " << addedValues.size() << std::endl;
  data_file << "Initialization time taken: " << initializationTime << "s" << std::endl;
  data_file.close();

  T findingValue = addedValues[addedValues.size() / 2];
  // std::vector<int> searchJumpSizes = {20, 100, 500, 1000, 2500, 5000, 7500, 10000, 25000, 50000};

  for (int j = 0; j < 15; j++) {
    int jumpSize = 20 * pow(2, j);
    int totalTime = 0; // In number of nodes visited
    int totalTimeBSFromRoot = 0; // In number of nodes visited
    for (T i = 0; i < addedValues.size(); i++) {
      std::cout << "Seaching for: " << findingValue << std::endl;

      T FSresult = skiplist.fingerSearch(findingValue);
      totalTime += skiplist.numNodesVisited;

      T BSresult = skiplist.find(findingValue);
      totalTimeBSFromRoot += skiplist.numNodesVisited;

      // if (FSresult != BSresult)
      //   std::cout << "Different Nodes Found: " << BSresult << " & " << FSresult << std::endl;
      int coin = Random::getInt(0, 1);
      if (coin) {
        findingValue += jumpSize;
        if (findingValue >= numNodes) {
          findingValue -= 2 * jumpSize;
        }
      } else {
        findingValue -= jumpSize;
        if (findingValue < 0) {
          findingValue += 2 * jumpSize;
        }
      }
    }
    data_file.open("results.txt", std::ios_base::app);
    data_file << "Jump size: " << jumpSize << std::endl;
    data_file << "Average running time FS: " << ((float) totalTime / (float) addedValues.size()) << std::endl;
    data_file << "Average running time BS: " << ((float) totalTimeBSFromRoot / (float) addedValues.size()) << std::endl;
    data_file.close();
  }
  data_file.open("results.txt", std::ios_base::app);
  data_file << std::endl << std::endl;
  data_file.close();
}

template
class Skiplist<int>;

template
class Skiplist<long>;

template
class Skiplist<long long unsigned>;

template
class Skiplist<float>;

template
class Skiplist<double>;
