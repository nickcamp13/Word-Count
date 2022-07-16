//#######################################################
// File: BinaryTree.h
// Author: Nicholas Campos
// Description: This file contains the Node structure and
//			 BinaryTree template class
// Date: April 9th, 2022
//#######################################################

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>

using std::cout;
using std::endl;

template<class T>
struct Node
{
    T element;
    Node<T> *left{};
    Node<T> *right{};
};

template<class T>
class BinaryTree
{
private:
    Node<T> *root{};

    bool contains(T data, Node<T> *r);
    T findMin(Node<T> *r);
    T findMax(Node<T> *r);
    void insert(T data, Node<T> *&r);
    void remove(T data, Node<T> *&r);
    void printTree(Node<T> *r);

public:
    BinaryTree();
    bool isEmpty();
    bool contains(T data);
    T findMin();
    T findMax();
    void insert(T data);
    void remove(T data);
    void printTree();
};

#endif

// ##########################################################
// @par Name
// contains
// @purpose
// determines if passed data exists within the Binary Tree
// @param [in] :
// T data - data to be searched for
// Node<T> *r - address of root node the method searches from
// @return
// bool
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
bool BinaryTree<T>::contains(T data, Node<T> *r)
{
    if (r == nullptr)
	   return false;
    else if (data < r->element)
	   return this->contains(data, r->left);
    else if (data > r->element)
	   return this->contains(data, r->right);
    else
	   return true;
}

// ##########################################################
// @par Name
// findMin
// @purpose
// finds the minimum value within the binary tree
// @param [in] :
// Node<T> *r - address of root node the method searches from
// @return
// T
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
T BinaryTree<T>::findMin(Node<T> *r)
{
    if (r->left == nullptr)
	   return r->element;
    else
	   return findMin(r->left);
}

// ##########################################################
// @par Name
// findMax
// @purpose
// finds the maximum value within the binary tree
// @param [in] :
// Node<T> *r - address of root node the method searches from
// @return
// T
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
T BinaryTree<T>::findMax(Node<T> *r)
{
    if (r->right == nullptr)
	   return r->element;
    else
	   return findMax(r->right);
}

// ##########################################################
// @par Name
// insert
// @purpose
// inserts data into a binary tree
// @param [in] :
// T data - data to be entered into the binary tree
// Node<T> *r - address of root node where the method attempts
//			 to insert the passed data
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void BinaryTree<T>::insert(T data, Node<T> *&r)
{
    if (r == nullptr)
    {
	   r = new Node<T>;
	   r->element = data;
	   r->left = nullptr;
	   r->right = nullptr;
    }
    else if (data < r->element)
	   insert(data, r->left);
    else if (data > r->element)
	   insert(data, r->right);

    return;
}

// ##########################################################
// @par Name
// remove
// @purpose
// removes data from a binary tree
// @param [in] :
// T data - data to be removed from the binary tree
// Node<T> *r - address of root node where the method attempts
//			 to remove the passed data
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void BinaryTree<T>::remove(T data, Node<T> *&r)
{
    if (this->isEmpty())
	   return;
    if (data < r->element)
	   this->remove(data, r->left);
    else if (data > r->element)
	   this->remove(data, r->right);
    else if (r->left != nullptr && r->right != nullptr)
    {
	   r->element = findMin(r->right);
	   remove(r->element, r->right);
    }
    else
    {
	   Node<T> *oldNode = r;
	   r = (r->left != nullptr) ? r->left : r->right;
	   delete oldNode;
    }
}

// ##########################################################
// @par Name
// printTree
// @purpose
// displays the data from the Binary Tree to the console
// @param [in] :
// Node<T> *r - address of root node where the method displays
//			 its element
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void BinaryTree<T>::printTree(Node<T> *r)
{
    if (r != nullptr)
    {
	   cout << r->element << endl;
	   this->printTree(r->left);
	   this->printTree(r->right);
    }
}

// ##########################################################
// @par Name
// BinaryTree (default constructor)
// @purpose
// sets the root of a newly created Binary Tree to null
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
BinaryTree<T>::BinaryTree() : root(nullptr)
{
}

// ##########################################################
// @par Name
// isEmpty
// @purpose
// determines if the BinaryTree is empty or not
// @param [in] :
// None
// @return
// bool
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
bool BinaryTree<T>::isEmpty()
{
    return this->root == nullptr;
}

// ##########################################################
// @par Name
// contains
// @purpose
// determines if passed data exists within the BinaryTree
// @param [in] :
// T data - data to be entered into the binary tree
// @return
// bool
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
bool BinaryTree<T>::contains(T data)
{
    return this->contains(data, this->root);
}

// ##########################################################
// @par Name
// findMin
// @purpose
// public access to find the minimum value of a binary tree
// @param [in] :
// None
// @return
// T
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
T BinaryTree<T>::findMin()
{
    return this->findMin(this->root);
}

// ##########################################################
// @par Name
// findMax
// @purpose
// public access to find the maximum value of a binary tree
// @param [in] :
// None
// @return
// T
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
T BinaryTree<T>::findMax()
{
    return this->findMax(this->root);
}

// ################################################
// @par Name
// insert
// @purpose
// public access to insert data into a binary tree
// @param [in] :
// T data - data to be entered into the binary tree
// @return
// None
// @par References
// None
// @par Notes
// None
//#################################################
template<class T>
void BinaryTree<T>::insert(T data)
{
    this->insert(data, this->root);
}

// ##########################################################
// @par Name
// insert
// @purpose
// public access to remove data from a binary tree
// @param [in] :
// T data - data to be removed from the binary tree
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void BinaryTree<T>::remove(T data)
{
    this->remove(data, this->root);
}

// ##########################################################
// @par Name
// printTree
// @purpose
// public access to display the data from the Binary Tree
// to the console
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void BinaryTree<T>::printTree()
{
    this->printTree(this->root);
}
