#ifndef BSTREEDRAWER_H
#define BSTREEDRAWER_H

#include <QPainter>
#include<QWidget>
#include "tree.h"
#include<unordered_map>
class TreeDrawer{
public:
    TreeDrawer();
    void draw(QPainter* painter, Node* tree, double scale);

private:
    int getNodeLevel(Node *node);
    int getPxLocOfLeftTree(Node *node);
    int getPxLocOfAncestor(Node *node);
    Node *getLeftmostNode(Node *node) const;
    void recursiveDraw(Node *node);
    void resetNodePosition(Node *node);

private:
    QPainter *painter;
    int yspace;
    int xspace;
    int nodeRadius;
    double scale;

    std::unordered_map<Node*, int> xShift;
};

#endif // BSTREEDRAWER_H
