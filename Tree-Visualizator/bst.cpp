
#include "bst.h"

BST::BST(): root(0),scale(1.0)
{

}

BST::~BST()
{
    this->root = 0;
}

bool BST::isEmpty() const
{
    return root == 0;
}

bool BST::insert(const int &item)
{
    Node *newNode = new Node(item);

    if (this->isEmpty())
    {
        this->root = newNode;
        return true;
    }

    Node *currentNode = root;
    Node *trailCurrentNode = root;

    while (currentNode != 0)
    {
        if (currentNode->data < item)
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->rightChild;
        }
        else if (currentNode->data > item)
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->leftChild;
        }
        else
        {
            return false;
        }
    }

    if (trailCurrentNode->data < item)
        trailCurrentNode->rightChild = newNode;
    else
        trailCurrentNode->leftChild = newNode;

    newNode->parent = trailCurrentNode;

    return true;
}

void BST::draw(QPainter *painter, double scale)
{
    if(this->root == 0)
        return;
    // Set properties of the painter for drawing the tree
    this->painter = painter;
    this->painter->setFont(QFont("Times", 12 * scale, QFont::Normal));

    // Set variables for drawing the tree
    this->scale = scale;
    this->nodeRadius = 20 * scale;
    this->xspace = nodeRadius;
    this->yspace = nodeRadius * 5;

    // Before drawing, must make sure that all nodes have x = 0 since in recursiveDraw() we check value of x on some nodes.
    resetNodePosition(root);

    // first node drawn (leftmost node) needs to have a static, predefined
    // location for the rest of the tree to be based off.
    Node *leftmost = getLeftmostNode(root);
    leftmost->x = nodeRadius * 2;

    // Draw the tree
    this->recursiveDraw(root);

    return;
}

void BST::recursiveDraw(Node *node)
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
        node->x = getPxLocOfLeftTree(node->leftChild) + nodeRadius + xspace;

        // Draw line to left child
        painter->drawLine(QPoint(node->x, y + nodeRadius), QPoint(node->leftChild->x + 2,((level + 1)* nodeRadius * 2 + yspace * level) - nodeRadius));
    }

    // in case of a node without a left child that is not the leftmost in the tree
    // - rules out root of tree (would be leftmost)
    // - must be the right child of some ancestor (parent, grandparent, etc..)
    // - must draw relative to first ancestor where x != 0
    else if (node->x == 0)
        node->x = getPxLocOfAncestor(node) + nodeRadius + xspace;

    // Draw the node
    painter->drawEllipse(QPoint(node->x, y),nodeRadius,nodeRadius);

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

    painter->drawText(QPoint(node->x-(textAdjuster*scale), y+(5*scale)), QString::number(node->data));

    // Draw the right subtree
    this->recursiveDraw(node->rightChild);

    // Draw the line to the right child (if applicable).
    // Must be done after recursively drawing right child, otherwise x values will still be 0.
    if (node->rightChild != 0)
        painter->drawLine(QPoint(node->x, y + nodeRadius), QPoint(node->rightChild->x - 2,((level + 1)* nodeRadius * 2 + yspace * level) - nodeRadius));

    return;
}

int BST::getNodeLevel(Node *node)
{
    int level = 1;
    Node *current = node;

    while(current->parent != 0){
        current = current->parent;
        ++level;
    }
    return level;
}

int BST::getPxLocOfLeftTree(const Node *node)
{
    if(node->rightChild == 0){
        return node->x;
    }
    return getPxLocOfLeftTree(node->rightChild);
}

int BST::getPxLocOfAncestor(const Node *node)
{
    // All ancestor's node->x will be 0 unless it has already been drawn -
    // find the ancestor who's x != 0
    Node *currentNode = node->parent;

    while(currentNode->x == 0)
        currentNode = currentNode->parent;

    return currentNode->x;
}

void BST::resetNodePosition(Node *node)
{
    if (node == 0)
        return;
    resetNodePosition(node->leftChild);
    node->x = 0;
    resetNodePosition(node->rightChild);
}

Node *BST::getLeftmostNode(Node *node) const
{
    if (node->leftChild == 0)
        return node;
    return getLeftmostNode(node->leftChild);
}

Node::Node(const int &val):
    data(val), x(0), leftChild(0), rightChild(0), parent(0)
{

}
