#ifndef BST_H
#define BST_H

#include <QPainter>
#include "tree.h"
struct BSTNode : Node
{
    BSTNode(const int& val);
};


class BSTree : public Tree
{
public:
    BSTree() = default;
    ~BSTree() override = default;

    virtual bool insert(const int &val) override;
    virtual bool deleteItem(const int &val) override;
};

#endif // BST_H
