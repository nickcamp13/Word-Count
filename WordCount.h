//##########################################################
// File: WordCount.h
// Author: Nicholas Campos
// Description: This file contains the class definition for
//			 WordCount
// Date: April 9th, 2022
//##########################################################

#ifndef WORDCOUNT_H
#define WORDCOUNT_H
#include "AVLTree.h"
#include <string>
#include <fstream>
#include <algorithm>

using std::string;
using std::ifstream;
using std::remove_if;

class WordCount
{
private:
    AVLTree<string> *words;
    string filename;

public:
    WordCount(const string &fn);

    void read();
    const void display() const;
};

#endif
