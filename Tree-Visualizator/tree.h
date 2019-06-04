#ifndef TREE_H
#define TREE_H

#include "treememento.h"
#include "treevisitor.h"

struct Node
{
    Node(const int& val);
    int data;
    Node *leftChild;
    Node *rightChild;
    Node *parent;
};

class Tree
{
private:
    void recursiveDeleteNodes(const Node *node);
    QString getPreOrderTraversal() const;
public:
    Tree();
    virtual ~Tree();
    bool isEmpty() const {return root == 0;}
    Node* getRoot() const{ return root;}

    virtual bool insert(const int &val) = 0;
    virtual bool deleteItem(const int &val) = 0;

    TreeMemento createMemento();
    void setMemento(const TreeMemento& state);
    virtual void accept(TreeVisitor &v) = 0;
    void clear();
protected:
    Node *root;
};

#endif // TREE_H
