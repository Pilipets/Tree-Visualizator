#ifndef BST_H
#define BST_H

#include <QPainter>

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
public:
    BST();
    virtual ~BST();
    bool isEmpty() const;
    Node* getRoot() const{ return root;}

    virtual bool insert(const int &val);

    virtual bool deleteItem(int val);

protected:
    Node *root;
};

#endif // BST_H
