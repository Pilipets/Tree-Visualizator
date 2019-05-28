#include "treefactory.h"

BST *TreeFactory::createTree(int type)
{
    BST* tree = nullptr;
    switch (type) {
    case 0:
        tree = new BST();
        break;
    case 1:
        tree = new SplayTree();
        break;
    }

    //Call some initialize methods on Tree

    return tree;
}
