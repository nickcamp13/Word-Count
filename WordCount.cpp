//##########################################################
// File: WordCount.cpp
// Author: Nicholas Campos
// Description: This file contains the class implementation
//			 for WordCount
// Date: April 9th, 2022
//##########################################################

#include "WordCount.h"

// ##########################################################
// @par Name
// WordCount
// @purpose
// creates an instance of a WordCount type with a given filename
// @param [in] :
// string fn - name of file to be read from
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
WordCount::WordCount(const string &fn) : words(new AVLTree<string> ("WORD NOT FOUND")), filename(fn) {}

// ##########################################################
// @par Name
// read
// @purpose
// reads words from a text document and adds them to an 
// AVL tree while keeping track of how many times a word appears
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// None
//###########################################################
void WordCount::read()
{
    ifstream file;
    string wordToAdd{};
    file.open(this->filename);

    if (file.is_open())
    {
	   while (!file.eof())
	   {
		  getline(file, wordToAdd, ' ');
		  wordToAdd.erase(remove_if(wordToAdd.begin(), wordToAdd.end(), ispunct), wordToAdd.end());
		  wordToAdd.erase(remove_if(wordToAdd.begin(), wordToAdd.end(), isblank), wordToAdd.end());
		  this->words->insert(wordToAdd);
	   }
    }
    else
    {
	   cout << "File failed to open" << endl;
    }
    file.close();
}

// ##########################################################
// @par Name
// display
// @purpose
// displays data from the AVLTree and the number of times each
// word appears in the text file
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
const void WordCount::display() const
{
    this->words->printTree();
}
