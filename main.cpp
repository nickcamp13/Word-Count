//##################################################################
// File: main.cpp
// Author: Nicholas Campos
// Description: This file contains the main function of this project
// Date: April 9th, 2022
//##################################################################

#include <iostream>
#include <string>
#include "BinaryTree.h"
#include "WordCount.h"

using std::string;

int main() {
    WordCount testFile("WordCountTest.txt");
    testFile.read();
    testFile.display();

    return 0;
}
