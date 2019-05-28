#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "bst.h"
#include"splaytree.h"
class TreeFactory{

public:
    static BST* createTree(int type);
};

#endif // TREEFACTORY_H
