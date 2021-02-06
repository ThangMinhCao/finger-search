#ifndef FINGER_SEARCH_TREAP_H
#define FINGER_SEARCH_TREAP_H

/**
 * Treap data structure: A randomized Binary Search Tree which is a
 * combination of Binary Search Tree and Heap (Min-heap)
 * Important Extension: Finger Search with extra pointers
 *
 * Operation supported: add, remove, search
 */
class Treap {
  public:
    struct Node {
      double data;
      float priority;
      Node *parent, *left, *right, *leftParent, *rightParent;
      Node(double value, Node* parent=nullptr, Node* left=nullptr,Node* right=nullptr,
            Node* leftParent=nullptr, Node* rightParent= nullptr);
    };

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
    static Node* binarySearch(double value, Node* startNode);
};


#endif //FINGER_SEARCH_TREAP_H
