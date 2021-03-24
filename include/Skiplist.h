#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <cstring>
#include <vector>

template<class T>
class Skiplist {
  private:
    T null;
    struct Node {
      T x;
      int height;     // length of next
      Node *next[];
    };
    Node *sentinel;
    Node** finger;
    int h;
    int n;
    Node** stack;

    Node *newNode(T x, int h);
    void deleteNode(Node *u);
    Node* findPredNode(T x);
    int compare(T &x, T &y);

  public:
    Skiplist();
    ~Skiplist();
    T find(T x);
    T fingerSearch(T x);
    bool add(T x);
    bool remove(T x);
    int pickHeight();
    void clear();
    int size();
    static void test(int numNodes);
    int numNodesVisited;
};

template<class T>
Skiplist<T>::Skiplist() {
  null = (T)NULL;
  n = 0;
  sentinel = newNode(null, sizeof(int)*8);
  memset(sentinel->next, '\0', sizeof(Node*)*sentinel->height);
  stack = (Node**)new Node*[sentinel->height];
  finger = (Node**)new Node*[sentinel->height];
  for (int i =  0; i < sentinel->height; i++) {
    finger[i] = sentinel;
  }
  h = 0;
  numNodesVisited = 0;
}

template<class T>
Skiplist<T>::~Skiplist() {
	clear();
	deleteNode(sentinel);
	delete[] stack;
}

#endif