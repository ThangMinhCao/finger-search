#ifndef FINGER_SEARCH_TREAP_H
#define FINGER_SEARCH_TREAP_H

class Treap {

  public:
    struct Node {
      int data;
      float priority;
      Node *parent, *left, *right;
      Node(int value, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr);
    };

    Node * root;
    Treap() : root(nullptr) {};
    ~Treap();
    bool add(int value);
    bool remove(int value);
    void display() const;

  private:
    static void leftRotate(Node* &node);
    static void rightRotate(Node* &node);
    bool treapAdd(int value, Node* &current, Node* prev= nullptr);
    void cleanupMemory(Node * node);
};


#endif //FINGER_SEARCH_TREAP_H
