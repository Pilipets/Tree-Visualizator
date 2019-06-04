#include "bst.h"
#include<QStack>

bool BSTree::insert(const int &item)
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

bool BSTree::deleteItem(const int &item)
{
    if (this->isEmpty())
        return false;

    bool found = false;
    Node *currentNode = root;
    Node *trailCurrentNode = root;

    while (!found && currentNode != 0)
    {
        if (currentNode->data == item)
            found = true;
        else if (currentNode->data < item)
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->rightChild;
        }
        else
        {
            trailCurrentNode = currentNode;
            currentNode = currentNode->leftChild;
        }
    }

    if (!found)
        return found;

    if (currentNode->leftChild == 0 && currentNode->rightChild == 0)
    {
        if (currentNode == root)
        {
            delete root;
            root = 0;
        }
        else if (trailCurrentNode->data < item)
        {
            delete trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = 0;
        }
        else
        {
            delete trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = 0;
        }
        return found;
    }

    // NO LEFT, YES RIGHT
    if (currentNode->leftChild == 0 && currentNode->rightChild != 0)
    {
        // ROOT WITH RIGHT
        if (currentNode == root)
        {
            Node *tempPtr = root;
            root->rightChild->parent = 0;
            root = root->rightChild;
            delete tempPtr;
            return found;
        }

        if (trailCurrentNode->data < item)
        {
            Node *tempPtr = trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = currentNode->rightChild;
            currentNode->rightChild->parent = trailCurrentNode;
            delete tempPtr;
        }
        else
        {
            Node *tempPtr = trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = currentNode->rightChild;
            currentNode->rightChild->parent = trailCurrentNode;
            delete tempPtr;
        }

        return found;
    }
    // LEFT CHILD, NO RIGHT CHILD
    if (currentNode->leftChild != 0 && currentNode->rightChild == 0)
    {
        // Root with left child
        if (currentNode == root)
        {
            Node *tempPtr = root;
            root = root->leftChild;
            root->parent = 0;
            delete tempPtr;
        }
        if (trailCurrentNode->data < item)
        {
            Node *tempPtr = trailCurrentNode->rightChild;
            trailCurrentNode->rightChild = currentNode->leftChild;
            currentNode->leftChild->parent = trailCurrentNode;
            delete tempPtr;
        }
        else
        {
            Node *tempPtr = trailCurrentNode->leftChild;
            trailCurrentNode->leftChild = currentNode->leftChild;
            currentNode->leftChild->parent = trailCurrentNode;
            delete tempPtr;
        }
        return found;
    }

    //if the node has both children
    //find the succesor of the node to be deleted, replace the value and delete the succesor
    if (currentNode->leftChild != 0 && currentNode->rightChild != 0)
    {
        //if the leftchildren of the node we want to delete is a leaf, it means the children itself is the succesor
        Node *ptr = currentNode;
        trailCurrentNode = currentNode;
        ptr = ptr->leftChild;
        if(ptr->rightChild==NULL)
        {
            if(ptr->leftChild==NULL)
            {
                currentNode->data=ptr->data;
                currentNode->leftChild=NULL;
                delete ptr;
            }
            else
            {
               currentNode->data=ptr->data;
               currentNode->leftChild=ptr->leftChild;
               ptr->leftChild->parent=currentNode;
               delete ptr;

            }
        }
        else
            {
            //else we look for the succesor in the subtree

            while (ptr->rightChild!=0)
               ptr=ptr->rightChild;
            trailCurrentNode=ptr->parent;
            trailCurrentNode->rightChild=NULL;
            currentNode->data=ptr->data;
            delete ptr;
            }
   }
    return found;
}

void BSTree::accept(TreeVisitor &v)
{
    v.visit(this);
}

BSTNode::BSTNode(const int &val) : Node(val){}
