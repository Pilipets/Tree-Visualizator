
#include "bst.h"

BST::BST(): root(0)
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

Node::Node(const int &val):
    data(val), leftChild(0), rightChild(0), parent(0)
{

}
