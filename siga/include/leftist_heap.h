#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include <iostream>
#include <string>

#include "leftist_heap_node.h"



template<typename T>
class LeftistHeap {
    public:
        /**
         * @brief Constroi uma nova heap esquerdista vazia.
         * 
         */
        LeftistHeap();
        LeftistHeap(bool (*compare)(T&, T&));

        void Insert(T); // Insere chave na heap
        T&   FindMax(); // Seleciona o maior elemento da heap
        T    RemoveMax(); // Remove o maior elemento da heap
        void Merge(LeftistHeap<T>&); // Intercala duas heaps esquerdistas
        void Print(); // Imprime a heap
        bool isEmpty(); // Verifica se a heap está vazia
        bool isLeftistHeap(); // Verifica se a heap é uma heap esquerdista

        ~LeftistHeap();
    private:
        void SwapChildren(LeftistHeapNode<T>* node);
        void DeallocateMemory(LeftistHeapNode<T>*);
        void print(LeftistHeapNode<T>* node, const std::string& prefix, bool isLeft, std::ostream& out);
        int  ComputeDist(LeftistHeapNode<T>*);
        LeftistHeapNode<T>* merge(LeftistHeapNode<T>* left, LeftistHeapNode<T>* right);    
        bool checkLeftistHeap(LeftistHeapNode<T>* node);
        


        bool (*_compare)(T&, T&); 

        LeftistHeapNode<T>* root;
};

/*
 *  Funções auxiliares
 */

template<typename T>
bool compare_function(T& a, T& b)
{
    return a < b;
}


template<typename T>
void LeftistHeap<T>::SwapChildren(LeftistHeapNode<T>* node)
{
    LeftistHeapNode<T>* temp = node->getLeftChild();
    node->setLeftChild(node->getRightChild());
    node->setRightChild(temp);
}

template<typename T>
int LeftistHeap<T>::ComputeDist(LeftistHeapNode<T>* node)
{
    if (node == nullptr)
        return -1;
    else
        return 1 + std::min(ComputeDist(node->getLeftChild()), ComputeDist(node->getRightChild()));
}

template<typename T>
LeftistHeapNode<T>* LeftistHeap<T>::merge(LeftistHeapNode<T>* A, LeftistHeapNode<T>* B)
{
    if (A == nullptr)
        return B;
    if (B == nullptr)
        return A;
    if (_compare(A->getData(),B->getData()))
    {
        LeftistHeapNode<T>* temp = A;
        A = B; 
        B = temp;
    }
    A->setRightChild(merge(A->getRightChild(), B));
    if (ComputeDist(A->getRightChild()) > ComputeDist(A->getLeftChild()))
        SwapChildren(A);
    if(A->getRightChild() == nullptr)
        A->SetDist(1);
    else
        A->SetDist(A->getRightChild()->GetDist() + 1);
    return A;
}

template <typename T>
bool LeftistHeap<T>::checkLeftistHeap(LeftistHeapNode<T>* node)
{
    if (node == nullptr)
        return true;

    int distL = ComputeDist(node->getLeftChild());
    int distR = ComputeDist(node->getRightChild());
    if(node->getLeftChild()) 
        if(this->_compare(node->getData(), node->getLeftChild()->getData())
            return false;
    if(node->getRightChild())
        if(this->_compare(node->getData(), node->getRightChild()->getData())
            return false;
    if( distL < distR)
        return false;
    
    return checkLeftistHeap(node->getLeftChild()) && checkLeftistHeap(node->getRightChild());

}

template<typename T>
LeftistHeap<T>::LeftistHeap() : root(nullptr) {
    this->_compare = compare_function;
}

template<typename T>
LeftistHeap<T>::LeftistHeap(bool (*compare)(T&, T&)) : root(nullptr) {
    this->_compare = compare;
}

template<typename T>
void LeftistHeap<T>::Insert(T data) 
{
    LeftistHeapNode<T>* new_node = new LeftistHeapNode<T>(data);
    root = merge(root, new_node);
}

template<typename T>
T LeftistHeap<T>::RemoveMax()
{
    if (root == nullptr)
        throw std::runtime_error("Heap is empty");
    T max = root->getData();
    LeftistHeapNode<T>* new_root = merge(root->getLeftChild(), root->getRightChild());
    delete root;
    root = new_root;
    return max;
}

template<typename T>
T& LeftistHeap<T>::FindMax()
{
    if (root == nullptr)
        throw std::runtime_error("Heap is empty");
    return root->getData();
}

template<typename T>
void LeftistHeap<T>::Merge(LeftistHeap<T>& other)
{
    if(this == &other)
        return;
    root = merge(root, other.root);
    other.root = nullptr;
}

template<typename T>
LeftistHeap<T>::~LeftistHeap()
{
    DeallocateMemory(root);
}

template<typename T>
void LeftistHeap<T>::DeallocateMemory(LeftistHeapNode<T>* node)
{
    if(node == nullptr)
        return;
    DeallocateMemory(node->getLeftChild());
    DeallocateMemory(node->getRightChild());
    delete node;
}

template<typename T>
void LeftistHeap<T>::print(LeftistHeapNode<T>* node, const std::string& prefix, bool isLeft, std::ostream& out)
{
    if(node == nullptr)
        return;
    
    out << prefix;
    out << (isLeft ? "├──" : "└──" );

    // print the value of the node
    out <<"["<<node->getData()<<","<<node->GetDist()<<"]" << std::endl;

    print(node->getLeftChild() , prefix + (isLeft ? "│   " : "    "), true, out);
    print(node->getRightChild(), prefix + (isLeft ? "│   " : "    "), false, out);
}

template<typename T>
void LeftistHeap<T>::Print()
{
    print(root, "", false,  std::cout);
    std::cout << std::endl;
}

template<typename T>
bool LeftistHeap<T>::isEmpty()
{
    return root == nullptr;
}


template<typename T>
bool LeftistHeap<T>::isLeftistHeap()
{
    return checkLeftistHeap(root);
}

#endif
