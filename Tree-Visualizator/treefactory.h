#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "bst.h"
#include"splaytree.h"
class TreeFactory{
public:
    explicit TreeFactory() = delete;
    static Tree* createTree(int type);
};

#endif // TREEFACTORY_H
