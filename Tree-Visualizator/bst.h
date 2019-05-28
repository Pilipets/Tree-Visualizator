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
    int x;
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

    //bool deleteItem(int val);
    void draw(QPainter *painter, double scale);

private:
    QPainter *painter;
    Node *root;
    int yspace;
    int xspace;
    int nodeRadius;
    double scale;

    void recursiveDraw(Node *node);
    int getNodeLevel(Node *node);
    int getPxLocOfLeftTree(const Node *node);
    int getPxLocOfAncestor(const Node *node);
    void resetNodePosition(Node *node);
    Node* getLeftmostNode(Node *node) const;
};

#endif // BST_H
