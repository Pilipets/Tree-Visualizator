#include "treedrawer.h"

void TreeDrawer::draw(QPainter* painter, Node* tree, double scale)
{
    this->painter = painter;
    this->scale = scale;
    if(tree == 0)
        return;
    // Set properties of the painter for drawing the tree
    painter->setFont(QFont("Times", 12 * scale, QFont::Normal));

    // Set variables for drawing the tree
    this->nodeRadius = 20 * scale;
    this->xspace = nodeRadius;
    this->yspace = nodeRadius * 5;

    // Before drawing, must make sure that all nodes have x = 0 since in recursiveDraw() we check value of x on some nodes.
    xShift.clear();
    resetNodePosition(tree);

    // first node drawn (leftmost node) needs to have a static, predefined
    // location for the rest of the tree to be based off.
    Node *leftmost = getLeftmostNode(tree);
    xShift[leftmost] = nodeRadius * 2;

    // Draw the tree
    this->recursiveDraw(tree);

    return;
}

int TreeDrawer::getNodeLevel(Node *node)
{
    int level = 1;
    Node *current = node;

    while(current->parent != 0){
        current = current->parent;
        ++level;
    }
    return level;
}

int TreeDrawer::getPxLocOfLeftTree(Node *node)
{
    if(node->rightChild == 0){
        return xShift[node];
    }
    return getPxLocOfLeftTree(node->rightChild);
}

int TreeDrawer::getPxLocOfAncestor(Node *node)
{
    // All ancestor's node->x will be 0 unless it has already been drawn -
    // find the ancestor who's x != 0
    Node *currentNode = node->parent;

    while(xShift[currentNode] == 0)
        currentNode = currentNode->parent;

    return xShift[currentNode];
}

Node *TreeDrawer::getLeftmostNode(Node *node) const
{
    if (node->leftChild == 0)
        return node;
    return getLeftmostNode(node->leftChild);
}

void TreeDrawer::recursiveDraw(Node *node)
{
    // Base case
    if (node == 0)
        return;

    // Draw left subtree
    this->recursiveDraw(node->leftChild);

    // Set the y position of the node based off of the level of the node and the nodeRadius
    int level = getNodeLevel(node);
    int y = level * nodeRadius * 2 + yspace * (level-1);

    // if there is a left child, we need to draw this parent relative to it
    if (node->leftChild != 0)
    {
        xShift[node] = getPxLocOfLeftTree(node->leftChild) + nodeRadius + xspace;

        // Draw line to left child
        painter->drawLine(QPoint(xShift[node], y + nodeRadius),
                          QPoint(xShift[node->leftChild] + 2,((level + 1)* nodeRadius * 2 + yspace * level) - nodeRadius));
    }

    // in case of a node without a left child that is not the leftmost in the tree
    // - rules out root of tree (would be leftmost)
    // - must be the right child of some ancestor (parent, grandparent, etc..)
    // - must draw relative to first ancestor where x != 0
    else if (xShift[node] == 0)
        xShift[node] = getPxLocOfAncestor(node) + nodeRadius + xspace;

    // Draw the node
    painter->drawEllipse(QPoint(xShift[node], y),nodeRadius,nodeRadius);

    // Adjust the text horizontally depending on how many digits are in it
    int textAdjuster;
    if(std::abs(node->data) < 10)
        textAdjuster = 4;
    else if (std::abs(node->data) < 100)
        textAdjuster = 7;
    else if (std::abs(node->data) < 1000)
        textAdjuster = 12;
    else
        textAdjuster = 16;

    painter->drawText(QPoint(xShift[node]-(textAdjuster*scale), y+(5*scale)), QString::number(node->data));

    // Draw the right subtree
    this->recursiveDraw(node->rightChild);

    // Draw the line to the right child (if applicable).
    // Must be done after recursively drawing right child, otherwise x values will still be 0.
    if (node->rightChild != 0)
        painter->drawLine(QPoint(xShift[node], y + nodeRadius), QPoint(xShift[node->rightChild] - 2,((level + 1)* nodeRadius * 2 + yspace * level) - nodeRadius));
}

void TreeDrawer::resetNodePosition(Node *node)
{
    if (node == 0)
        return;
    resetNodePosition(node->leftChild);
    xShift[node] = 0;
    resetNodePosition(node->rightChild);
}

TreeDrawer::TreeDrawer()
{
}
