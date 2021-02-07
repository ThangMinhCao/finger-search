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
template<class Node>
class Treap {
  public:
    Treap() : root(nullptr) {};
    ~Treap();
    bool add(double value);
    bool remove(double value);
    void display(bool showPriority=false);
    Node* search(double value);
    Node* fingerSearch(double value);

  private:
    Node* root;
    Node* finger;
    static void leftRotate(Node* &node);
    static void rightRotate(Node* &node);
    bool treapAdd(double value, Node* &current, Node* prev= nullptr);
    bool treapRemove(double value, Node* &current);
    void cleanupMemory(Node* node);
    static Node* binarySearch(double value, Node* startNode, int& numNodesVisited);
};


#endif //FINGER_SEARCH_TREAP_H
