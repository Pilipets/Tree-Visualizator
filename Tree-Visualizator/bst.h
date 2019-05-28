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
    ~BST();
    bool isEmpty() const;
    Node* getRoot() const{ return root;}
    bool insert(const int &val);

    bool deleteItem(int val);

private:
    Node *root;
};

#endif // BST_H
