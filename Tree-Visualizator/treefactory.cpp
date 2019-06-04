#include "treefactory.h"

Tree *TreeFactory::createTree(int type)
{
    Tree* tree = nullptr;
    switch (type) {
    case 0:
        tree = new BSTree();
        break;
    case 1:
        tree = new SplayTree();
        break;
    }

    //Call some initialize methods on Tree

    return tree;
}
