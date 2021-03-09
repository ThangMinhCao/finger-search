#ifndef FINGER_SEARCH_TREAP_H
#define FINGER_SEARCH_TREAP_H

#include "../include/Random.h"
template<typename T>
class Node {
  public:
    T data;
    double priority;
    Node *parent, *left, *right, *leftParent, *rightParent;
    Node(double value, Node* parent=nullptr, Node* left=nullptr,Node* right=nullptr,
          Node* leftParent=nullptr, Node* rightParent= nullptr) {
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
    Node<T>* search(T value);
    Node<T>* fingerSearch(T value);
    void printTotalNodesVisited();
    int numNodesVisited;

  private:
    Node<T>* root;
    Node<T>* finger;
    static void leftRotate(Node<T>* &node);
    static void rightRotate(Node<T>* &node);
    bool treapAdd(double value, Node<T>* &current, Node<T>* prev= nullptr);
    bool treapRemove(double value, Node<T>* &current);
    void cleanupMemory(Node<T>* node);
    static Node<T>* binarySearch(double value, Node<T>* startNode, int& numNodesVisited);
};


#endif //FINGER_SEARCH_TREAP_H
