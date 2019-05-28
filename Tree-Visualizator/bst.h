#ifndef BST_H
#define BST_H

#include <QPainter>

class Node
{
    friend class BST;
public:
    Node(const int& val);
private:
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
    bool insert(const int &val);

    bool deleteItem(int val);
    void draw(QPainter *painter, double scale);
};

#endif // BST_H
