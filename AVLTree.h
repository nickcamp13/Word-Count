//##########################################################
// File: AVLTree.h
// Author: Nicholas Campos
// Description: This file contains the AVLNode structure and
//			 AVLTree template class
// Date: April 9th, 2022
//##########################################################

#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>
using std::cout;
using std::endl;

template<class T>
struct AVLNode
{
    T element;
    AVLNode<T> *left{};
    AVLNode<T> *right{};
    int height;
    int wordCount;
};

template<class T>
class AVLTree
{
private:
    AVLNode<T> *root{};
    const T ITEM_NOT_FOUND;

    bool contains(T data, AVLNode<T> *r);

    void insert(const T &data, AVLNode<T> *&r) const;
    void remove(T data, AVLNode<T> *&r) const;
    void printTree(AVLNode<T> *r) const;
    void makeEmpty(AVLNode<T> *&r) const;

    AVLNode<T> *findMin(AVLNode<T> *r) const;
    AVLNode<T> *findMax(AVLNode<T> *r) const;
    AVLNode<T> *find(const T &data, AVLNode<T> *r) const;
    const T &elementAt(AVLNode<T> *r) const;

    AVLNode<T> *clone(AVLNode<T> *r) const;

    // TREE MANIPULATIONS
    int height(AVLNode<T> *r) const;
    int max(int lht, int rht) const;

    void rotateLeft(AVLNode<T> *&n) const;
    void rotateRight(AVLNode<T> *&n) const;
    void doubleRotateLeft(AVLNode<T> *&n) const;
    void doubleRoatateRight(AVLNode<T> *&n) const;

public:
    explicit AVLTree(const T &notFound);
    AVLTree(const AVLTree<T> &tree);

    bool isEmpty() const;
    bool contains(T data) const;

    void insert(const T &data);
    void remove(const T &data);
    void printTree() const;
    void makeEmpty();

    const T &findMin() const;
    const T &findMax() const;
    const T &find(const T &data) const;

    const AVLTree<T> &operator=(const AVLTree<T> &tree);

    ~AVLTree();

};

#endif

// ##########################################################
// @par Name
// AVLTree
// @purpose
// sets the value to return when an item is not found for one
// of the find methods and sets the value of its root to null
// @param [in] :
// None
// @return
// None
// @par References
// const T &notFound - value to represent when an item is not
//				    found
// @par Notes
// None
//###########################################################
template<class T>
AVLTree<T>::AVLTree(const T &notFound) : ITEM_NOT_FOUND(notFound), root(nullptr) {}

// ##########################################################
// @par Name
// AVLTree
// @purpose
// sets the value to return when an item is not found for one
// of the find methods and sets the value of its root to null
// @param [in] :
// None
// @return
// None
// @par References
// const AVLTree &tree - copies an already existing tree to a
//					newly created tree
// @par Notes
// None
//###########################################################
template<class T>
AVLTree<T>::AVLTree(const AVLTree<T> &tree) : ITEM_NOT_FOUND(tree.ITEM_NOT_FOUND), root(tree.root)
{
    *this = tree;
}

// ##########################################################
// @par Name
// isEmpty
// @purpose
// determines if the AVLTree is empty or not
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
bool AVLTree<T>::isEmpty() const
{
    return this->root == nullptr;
}

// ##########################################################
// @par Name
// contains
// @purpose
// public access to determine if passed data exists within the AVLTree
// @param [in] :
// T data - data to be searched for
// @return
// bool
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
bool AVLTree<T>::contains(T data) const
{
    return this->contains(data, this->root);
}

// ################################################
// @par Name
// insert
// @purpose
// public access to insert data into an AVLtree
// @param [in] :
// T data - data to be entered into the AVL tree
// @return
// None
// @par References
// None
// @par Notes
// None
//#################################################
template<class T>
void AVLTree<T>::insert(const T &data)
{
    insert(data, this->root);
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
void AVLTree<T>::remove(const T &data)
{
    remove(data, this->root);
}

// ##########################################################
// @par Name
// ~AVLTree
// @purpose
// destructor
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
AVLTree<T>::~AVLTree()
{
    makeEmpty();
}

// ##########################################################
// @par Name
// contains
// @purpose
// determines if passed data exists within the AVL Tree
// @param [in] :
// T data - data to be searched for
// AVLNode<T> *r - address of root node the method searches from
// @return
// bool
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
bool AVLTree<T>::contains(T data, AVLNode<T> *r)
{
    if (r == nullptr)
	   return false;
    else if (data < r->element)
	   return contains(data, r->left);
    else if (data > r->element)
	   return contains(data, r->right);
    else
	   return true;
}

// ##########################################################
// @par Name
// insert
// @purpose
// inserts data into a AVL tree
// @param [in] :
// T data - data to be entered into the AVL tree
// AVLNode<T> *r - address of root node where the method attempts
//			 to insert the passed data
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void AVLTree<T>::insert(const T &data, AVLNode<T> *&r) const
{
    if (r == nullptr)
    {
	   AVLNode<T> *newNode = new AVLNode<T>;
	   newNode->element = data;
	   newNode->left = nullptr;
	   newNode->right = nullptr;  
	   newNode->wordCount = 1;
	   r = newNode;
    }
    else if (data < r->element)
    {
	   insert(data, r->left);
	   if (height(r->left) - height(r->right) == 2)
	   {
		  if (data < r->left->element)
			 rotateRight(r);
		  else
			 doubleRotateLeft(r);
	   }
    }
    else if (data > r->element)
    {
	   insert(data, r->right);
	   if (height(r->right) - height(r->left) == 2)
	   {
		  if (data > r->right->element)
			 rotateLeft(r);
		  else
			 doubleRoatateRight(r);
	   }
    }
    else
    {
	   r->wordCount++;
    }

    if (r != nullptr)
	   r->height = max(height(r->left), height(r->right)) + 1;
}

// ##########################################################
// @par Name
// remove
// @purpose
// removes data from a AVL tree
// @param [in] :
// T data - data to be removed from the AVL tree
// AVLNode<T> *r - address of root node where the method attempts
//			 to remove the passed data
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void AVLTree<T>::remove(T data, AVLNode<T> *&r) const
{
    if (r == nullptr)
	   return;
    else if (data < r->element)
    {
	   remove(data, r->left);
	   if (height(r->right) - height(r->left) > 1)
	   {
		  if (height(r->right->right) >= height(r->right->left))
			 rotateLeft(r);
		  else
			 doubleRoatateRight(r);
	   }
    }
    else if (data > r->element)
    {
	   remove(data, r->right);
	   if (height(r->left) - height(r->right) > 1)
	   {
		  if (height(r->left->left) >= height(r->left->right))
			 rotateRight(r);
		  else
			 doubleRotateLeft(r);
	   }
    }
    else
    {
	   if (r->left == nullptr || r->right == nullptr)
	   {
		  AVLNode<T> *temp = r->left ? r->left : r->right;
		  if (temp == nullptr)
		  {
			 temp = r;
			 r = nullptr;
		  }
		  else
			 *r = *temp;
		  delete temp;
	   }
	   else
	   {
		  AVLNode<T> *temp = findMin(r->right);
		  r->element = temp->element;
		  remove(temp->element, r->right);
	   }

	   if (r != nullptr)
		  r->height = max(height(r->left), height(r->right)) + 1;
    }
}

// ##########################################################
// @par Name
// printTree
// @purpose
// displays the data from the AVL Tree to the console
// @param [in] :
// AVLNode<T> *r - address of root node where the method displays
//			 its element
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void AVLTree<T>::printTree(AVLNode<T> *r) const
{
    if (r != nullptr)
    {
	   cout << r->element << " - " << r->wordCount << endl;
	   this->printTree(r->left);
	   this->printTree(r->right);
    }
}

// ##########################################################
// @par Name
// makeEmpty
// @purpose
// deletes memory from an AVLTree
// @param [in] :
// AVLNode<T> *r - address of root node where the method deletes
//			 memory
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void AVLTree<T>::makeEmpty(AVLNode<T> *&r) const
{
    if (r != nullptr)
    {
	   makeEmpty(r->left);
	   makeEmpty(r->right);
	   delete r;
    }
    r = nullptr;
}

// ##########################################################
// @par Name
// findMin
// @purpose
// finds the minimum value of a AVL tree
// @param [in] :
// AVLNode<T> *r - address of root node where the method searches
//				for the minimum value of the tree
// @return
// *AVLNode<T>
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
AVLNode<T> *AVLTree<T>::findMin(AVLNode<T> *r) const
{
    if (r == nullptr)
	   return r;
    while (r->left != nullptr)
	   r = r->left;
    return r;
}

// ##########################################################
// @par Name
// findMax
// @purpose
// finds the maximum value of a AVL tree
// @param [in] :
// AVLNode<T> *r - address of root node where the method searches
//				for the maximum value of the tree
// @return
// *AVLNode<T>
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
AVLNode<T> *AVLTree<T>::findMax(AVLNode<T> *r) const
{
    if (r == nullptr)
	   return r;
    while (r->right != nullptr)
	   r = r->right;
    return r;
}

// ##########################################################
// @par Name
// find
// @purpose
// finds data in an AVL Tree
// @param [in] :
// T data - data to be searched for
// AVLNode<T> *r - address of root node where the method searches
//				for the passed value
// @return
// *AVLNode<T>
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
AVLNode<T> *AVLTree<T>::find(const T &data, AVLNode<T> *r) const
{
    while (r != nullptr)
    {
	   if (data < r->element)
		  r = r->left;
	   else if (data > r->element)
		  r = r->right;
	   else
		  return r;
    }
    return nullptr;
}

// ##########################################################
// @par Name
// elementAt
// @purpose
// get the element of a node 
// @param [in] :
// AVLNode<T> *r - address of node to get element of
// @return
// *AVLNode<T>
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
const T &AVLTree<T>::elementAt(AVLNode<T> *r) const
{
    if (r == nullptr)
	   return ITEM_NOT_FOUND;
    else
	   return r->element;
}

// ##########################################################
// @par Name
// clone
// @purpose
// clones a subtree
// @param [in] :
// AVLNode<T> *r - address of root node to clone
// @return
// *AVLNode<T>
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
AVLNode<T> *AVLTree<T>::clone(AVLNode<T> *r) const
{
    if (r == nullptr)
	   return nullptr;
    else
    {
	   AVLNode<T> *newNode{};
	   newNode->element = r->element;
	   newNode->left = clone(r->left);
	   newNode->right = clone(r->right);
	   newNode->height = r->height;
	   return newNode;
    }
}

// ##########################################################
// @par Name
// height
// @purpose
// gets the height of a node
// @param [in] :
// AVLNode<T> *r - address of desired node's height
// @return
// *AVLNode<T>
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
int AVLTree<T>::height(AVLNode<T> *r) const
{
    return r == nullptr ? -1 : r->height;
}

// ##########################################################
// @par Name
// max
// @purpose
// finds the maximum tree length from a root node
// @param [in] :
// int lht - length from left child
// int rht - length from right child
// @return
// int
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
int AVLTree<T>::max(int lht, int rht) const
{
    return lht > rht ? lht : rht;
}

// ##########################################################
// @par Name
// rotateLeft
// @purpose
// Rotates binary tree node with right child
// @param [in] :
// AVLNode<T> *r - address of node to be rotated
// @return
// none
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void AVLTree<T>::rotateLeft(AVLNode<T> *&n) const
{
    AVLNode<T> *p = n->right;
    n->right = p->left;
    p->left = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    p->height = max(height(p->right), n->height) + 1;
    n = p;
}

// ##########################################################
// @par Name
// rotateRight
// @purpose
// Rotates binary tree node with left child
// @param [in] :
// AVLNode<T> *r - address of node to be rotated
// @return
// none
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void AVLTree<T>::rotateRight(AVLNode<T> *&n) const
{
    AVLNode<T> *p = n->left;
    n->left = p->right;
    p->right = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    p->height = max(height(p->left), n->height) + 1;
    n = p;
}

// ##########################################################
// @par Name
// doubleRotateLeft
// @purpose
// double Rotates binary tree node with left heavy children
// @param [in] :
// AVLNode<T> *r - address of node to be rotated
// @return
// none
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void AVLTree<T>::doubleRotateLeft(AVLNode<T> *&n) const
{
    rotateLeft(n->left);
    rotateRight(n);
}

// ##########################################################
// @par Name
// doubleRotateRight
// @purpose
// double Rotates binary tree node with right heavy children
// @param [in] :
// AVLNode<T> *r - address of node to be rotated
// @return
// none
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
void AVLTree<T>::doubleRoatateRight(AVLNode<T> *&n) const
{
    rotateRight(n->right);
    rotateLeft(n);
}

// ##########################################################
// @par Name
// printTree
// @purpose
// public access to display the data from the AVL Tree
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
void AVLTree<T>::printTree() const
{
    this->printTree(this->root);
}

// ##########################################################
// @par Name
// makeEmpty
// @purpose
// public access to delete memory from an AVLTree
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
void AVLTree<T>::makeEmpty()
{
    makeEmpty(this->root);
}

// ##########################################################
// @par Name
// findMin
// @purpose
// public access to find the minimum value within the AVL tree
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
const T &AVLTree<T>::findMin() const
{
    return elementAt(findMin(this->root));
}

// ##########################################################
// @par Name
// findMax
// @purpose
// public access to find the maximum value within the AVL tree
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
const T &AVLTree<T>::findMax() const
{
    return elementAt(findMax(this->root));
}

// ##########################################################
// @par Name
// find
// @purpose
// public access to find data in an AVL Tree
// @param [in] :
// T data - data to be searched for
// @return
// T
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
const T &AVLTree<T>::find(const T &data) const
{
    return elementAt(find(data, this->root));
}

// ##########################################################
// @par Name
// operator=
// @purpose
// used to clone an existing tree to another tree
// @param [in] :
// AVLTree<T> &tree - tree to be cloned
// @return
// AVLTree<T>
// @par References
// None
// @par Notes
// None
//###########################################################
template<class T>
const AVLTree<T> &AVLTree<T>::operator=(const AVLTree<T> &tree)
{
    if (this != &tree)
    {
	   makeEmpty();
	   this->root = clone(tree.root);
    }
    return *this;
}
