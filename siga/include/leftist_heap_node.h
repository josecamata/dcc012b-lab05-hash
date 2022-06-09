#ifndef LEFTIST_HEAP_NODE_H__
#define LEFTIST_HEAP_NODE_H__


#include <iostream>

/*
 * 
 *  Classe template que representa um nó de uma arvore esquerdista.
 */

template <typename T>
class LeftistHeapNode {
    public:

    // Construtor
    LeftistHeapNode(const T&);
    LeftistHeapNode(const T&, LeftistHeapNode<T>*, LeftistHeapNode<T>*);


    LeftistHeapNode<T>* getLeftChild();
    LeftistHeapNode<T>* getRightChild();
    void setLeftChild(LeftistHeapNode<T>*);
    void setRightChild(LeftistHeapNode<T>*);
    
    T& getData();

    int  GetDist();
    void SetDist(int);
    
    ~LeftistHeapNode();
    private:
        T data;
        LeftistHeapNode<T>* left;
        LeftistHeapNode<T>* right;
        int dist; // null path length
         
};

template <typename T>
LeftistHeapNode<T>::LeftistHeapNode(const T& d) : data(d), left(nullptr), right(nullptr), dist(0) {
}

template <typename T>
LeftistHeapNode<T>::LeftistHeapNode(const T& d, LeftistHeapNode<T>* l, LeftistHeapNode<T>* r) : data(d), left(l), right(r), dist(0) {
}

template <typename T>
LeftistHeapNode<T>* LeftistHeapNode<T>::getLeftChild() {
    return left;
}

template <typename T>
LeftistHeapNode<T>* LeftistHeapNode<T>::getRightChild() {
    return right;
}

template<typename T>
void LeftistHeapNode<T>::setLeftChild(LeftistHeapNode<T>* l) {
    left = l;
}

template<typename T>
void LeftistHeapNode<T>::setRightChild(LeftistHeapNode<T>* r) {
    right = r;
}

template <typename T>
T& LeftistHeapNode<T>::getData() {
    return data;
}

template <typename T>
int LeftistHeapNode<T>::GetDist() {
    return dist;
}

template<typename T>
void LeftistHeapNode<T>::SetDist(int n) {
    dist = n;
}

template<typename T>
LeftistHeapNode<T>::~LeftistHeapNode() {

}


#endif /* LEFTIST_HEAP_NODE_H__ */
