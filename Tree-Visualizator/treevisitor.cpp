
#include "treevisitor.h"
#include "bst.h"
#include "splaytree.h"
#include <QStack>
void GetTraversal::visit(BSTree *pTree)
{
    treeType = "Binary Search Tree";
    inOrderTraversal = getInOrderTraversal(pTree);
    preOrderTraversal = getPreOrderTraversal(pTree);
    postOrderTraversal = getPostOrderTraversal(pTree);
}

void GetTraversal::visit(SplayTree *pTree)
{
    treeType = "Splay Tree";
    inOrderTraversal = getInOrderTraversal(pTree);
    preOrderTraversal = getPreOrderTraversal(pTree);
    postOrderTraversal = getPostOrderTraversal(pTree);
}

QString GetTraversal::getPreOrderTraversal(Tree *tree) const
{
    QStack<Node*> stack;
    QString traversal;
    Node *root = tree->getRoot();
    while (true) {
        // Go to the left extreme insert all the elements to stack, add to string as encountered
        while (root != 0) {
            traversal.append(QString::number(root->data) + " ");
            stack.push(root);
            root = root->leftChild;
        }
        // check if Stack is empty, if yes, exit from everywhere
        if (stack.isEmpty()) {
            return traversal;
        }
        // pop the element from the stack, add the nodes at
        // the right to the Stack
        root = stack.pop();
        root = root->rightChild;
    }
}

QString GetTraversal::getInOrderTraversal(Tree *tree) const
{
    QStack<Node*> stack;
    QString traversal;
    Node *root = tree->getRoot();
    while (true) {
        // Go to the left extreme insert all the elements to stack
        while (root != 0) {
            stack.push(root);
            root = root->leftChild;
        }
        // check if Stack is empty, if yes, exit from everywhere
        if (stack.isEmpty()) {
            return traversal;
        }
        // pop the element from the stack , print it and add the nodes at
        // the right to the Stack
        root = stack.pop();
        traversal.append(QString::number(root->data) + " ");
        root = root->rightChild;
    }
}

QString GetTraversal::getPostOrderTraversal(Tree *tree) const
{
    if (tree->isEmpty())
            return QString("");
    QStack<Node*> stack1;
    QStack<Node*> stack2;
    QString traversal;
    Node *root = tree->getRoot();
    stack1.push(root);
    while (!stack1.isEmpty())
    {
        // Take out the root and insert into stack 2
        Node *temp = stack1.pop();
        stack2.push(temp);

        // now we have the root, push the left and right child of root into the first stack
        if (temp->leftChild != 0)
            stack1.push(temp->leftChild);
        if (temp->rightChild != 0)
            stack1.push(temp->rightChild);
    }

    while(!stack2.isEmpty())
        traversal.append(QString::number(stack2.pop()->data) + " ");

    return traversal;
}
