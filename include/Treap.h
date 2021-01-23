#ifndef FINGER_SEARCH_TREAP_H
#define FINGER_SEARCH_TREAP_H

class Treap {
  struct Node {
    int value;
    float priority;
    Node *parent, *left, *right;
    Node(int value, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr);
  };

  public:
    Treap() : root(nullptr) {};
    ~Treap();
    bool add(int value);
    bool remove(int value);
    Node * root;

  private:
    void leftRotate(Node * node);
    void rightRotate(Node * node);
    bool treapAdd(int value, Node* &current, Node* prev= nullptr);
    void cleanupMemory(Node * node);
};


#endif //FINGER_SEARCH_TREAP_H
