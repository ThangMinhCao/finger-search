#ifndef FINGER_SEARCH_TREAP_H
#define FINGER_SEARCH_TREAP_H

#include "../include/Random.h"
template<typename T>
class TreapNode {
  public:
    T data;
    double priority;
    TreapNode *parent, *left, *right, *leftParent, *rightParent;
    TreapNode(double value, TreapNode* parent=nullptr, TreapNode* left=nullptr,TreapNode* right=nullptr,
          TreapNode* leftParent=nullptr, TreapNode* rightParent= nullptr) {
      this->data = value;
      this->parent = parent;
      this->left = left;
      this->right = right;
      this->leftParent = leftParent;
      this->rightParent = rightParent;
      priority = Random::getReal(0, 1);
    };
};

/**
 * Treap data structure: A randomized Binary Search Tree which is a
 * combination of Binary Search Tree and Heap (Min-heap)
 * Important Extension: Finger Search with extra pointers
 *
 * Operation supported: add, remove, search
 */
template<typename T>
class Treap {
  public:
    Treap() : root(nullptr), numNodesVisited(0) {};
    ~Treap();
    bool add(T value);
    bool remove(T value);
    void display(bool showPriority=false);
    TreapNode<T>* search(T value);
    TreapNode<T>* fingerSearch(T value);
    void printTotalNodesVisited();
    int numNodesVisited;
    static void test(int numNodes);

  private:
    TreapNode<T>* root;
    TreapNode<T>* finger;
    static void leftRotate(TreapNode<T>* &node);
    static void rightRotate(TreapNode<T>* &node);
    bool treapAdd(double value, TreapNode<T>* &current, TreapNode<T>* prev= nullptr);
    bool treapRemove(double value, TreapNode<T>* &current);
    void cleanupMemory(TreapNode<T>* node);
    static TreapNode<T>* binarySearch(double value, TreapNode<T>* startNode, int& numNodesVisited);
};


#endif //FINGER_SEARCH_TREAP_H
