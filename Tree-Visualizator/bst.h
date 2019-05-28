#ifndef BST_H
#define BST_H

#include <QPainter>
#include "bstreememento.h"

struct Node
{
    Node(const int& val);
    int data;
    Node *leftChild;
    Node *rightChild;
    Node *parent;
};


class BST
{
private:
    QString getPreOrderTraversal() const;
public:
    BST();
    virtual ~BST();
    bool isEmpty() const;
    Node* getRoot() const{ return root;}

    virtual bool insert(const int &val);

    virtual bool deleteItem(int val);

    BSTreeMemento* createMemento();
protected:
    Node *root;
};

#endif // BST_H
