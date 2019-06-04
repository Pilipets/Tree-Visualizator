
#include "tree.h"
#include<QStack>
#include<QString>

Node::Node(const int& val): data(val), leftChild(0), rightChild(0), parent(0){}

void Tree::recursiveDeleteNodes(const Node *node)
{
    if (node == 0)
        return;
    recursiveDeleteNodes(node->leftChild);
    recursiveDeleteNodes(node->rightChild);
    delete node;
}

QString Tree::getPreOrderTraversal() const
{
    QStack<Node*> stack;
    QString traversal;
    Node *tmp = this->root;
    while (true) {
        // Go to the left extreme insert all the elements to stack, add to string as encountered
        while (tmp != 0) {
            traversal.append(QString::number(tmp->data) + " ");
            stack.push(tmp);
            tmp = tmp->leftChild;
        }
        // check if Stack is empty, if yes, exit from everywhere
        if (stack.isEmpty()) {
            return traversal;
        }
        // pop the element from the stack, add the nodes at
        // the right to the Stack
        tmp = stack.pop();
        tmp = tmp->rightChild;
    }
}

Tree::Tree() : root(0){}

Tree::~Tree()
{
    this->clear();
    this->root = 0;
}

TreeMemento Tree::createMemento()
{
    TreeMemento state;
    state.setTraversal(this->getPreOrderTraversal());
    return state;
}

void Tree::setMemento(const TreeMemento &state)
{
    this->clear();
    //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList query = state.getTraversal().split(QRegExp("(\\ )"), QString::SkipEmptyParts);

    for(QString& item: query){
        this->insert(item.toInt());
    }
}

void Tree::clear()
{
    recursiveDeleteNodes(root);
    root = 0;
}
