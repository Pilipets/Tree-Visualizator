#include "splaytree.h"


SplayNode *SplayTree::rightRotate(SplayNode *y)
{
    SplayNode *x = static_cast<SplayNode*>(y->leftChild);
    y->leftChild = x->rightChild;
    if(x->rightChild) x->rightChild->parent = y;

    x->rightChild = y;
    x->parent = y->parent;
    if(y) y->parent = x;
    return x;
}

SplayNode *SplayTree::leftRotate(SplayNode *x)
{
    SplayNode *y = static_cast<SplayNode*>(x->rightChild);
    x->rightChild = y->leftChild;
    if(y->leftChild) y->leftChild->parent = x;

    y->leftChild = x;
    y->parent = x->parent;
    if(x) x->parent = y;
    return y;
}

SplayNode *SplayTree::splay(SplayNode *tree, const int &key)
{
    // Base cases: root is NULL or key is present at root
    if (tree == nullptr || tree->data == key)
        return tree;

    // Key lies in left subtree
    if (tree->data > key)
    {
        // Key is not in tree, we are done
        if (tree->leftChild == nullptr)
            return tree;

        // Zig-Zig (Left Left)
        if (tree->leftChild->data > key)
        {
            // First recursively bring the key as root of left-left
            tree->leftChild->leftChild = splay(static_cast<SplayNode*>(tree->leftChild->leftChild), key);

            // Do first rotation for root, second rotation is done after else
            tree = rightRotate(tree);
        }
        else if (tree->leftChild->data < key) // Zag-Zig (Left Right)
        {
            // First recursively bring the key as root of left-right
            tree->leftChild->rightChild = splay(static_cast<SplayNode*>(tree->leftChild->rightChild), key);

            // Do first rotation for tree->left
            if (tree->leftChild->rightChild != nullptr){
                tree->leftChild = leftRotate(static_cast<SplayNode*>(tree->leftChild));
            }
        }

        // Do second rotation for root
        return (tree->leftChild == nullptr) ? tree : rightRotate(tree);
    }
        else // Key lies in right subtree
        {
            // Key is not in tree, we are done
            if (tree->rightChild == nullptr) return tree;

            // Zig-Zag (Right Left)
            if (tree->rightChild->data > key)
            {
                // Bring the key as root of right-left
                tree->rightChild->leftChild = splay(static_cast<SplayNode*>(tree->rightChild->leftChild), key);

                // Do first rotation for root->right
                if (tree->rightChild->leftChild != nullptr)
                    tree->rightChild = rightRotate(static_cast<SplayNode*>(tree->rightChild));
            }
            else if (tree->rightChild->data < key)// Zag-Zag (Right Right)
            {
                // Bring the key as root of right-right and do first rotation
                tree->rightChild->rightChild = splay(static_cast<SplayNode*>(tree->rightChild->rightChild), key);
                tree = leftRotate(tree);
            }

            // Do second rotation for root
            return (tree->rightChild == nullptr) ? tree : leftRotate(tree);
        }
}

std::pair<bool, SplayNode*> SplayTree::insert(SplayNode *tree, const int &key)
{
    // Simple Case: If tree is empty
    if (tree == nullptr)
        return std::make_pair(true, new SplayNode(key));

    // Bring the closest leaf node to root
    tree = splay(tree, key);

    // If key is already present, then return
    if (tree->data == key) return std::make_pair(false,tree);

    // Otherwise allocate memory for new node
    SplayNode *newnode = new SplayNode(key);

    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    if (tree->data > key)
    {
        newnode->rightChild = tree;
        tree->parent = newnode;

        newnode->leftChild = tree->leftChild;
        if(tree->leftChild) tree->leftChild->parent = newnode;
        tree->leftChild = nullptr;
    }

    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    //left child of root is smaller that key, otherwise left child would stay in root
    else
    {
        newnode->leftChild = tree;
        tree->parent = newnode;

        newnode->rightChild = tree->rightChild;
        if(tree->rightChild) tree->rightChild->parent = newnode;
        tree->rightChild = NULL;
    }

    return std::make_pair(true, newnode); // newnode becomes new root
}

std::pair<bool, SplayNode *> SplayTree::deleteItem(SplayNode *tree, const int &key)
{
    if (!tree)
        return std::make_pair(false,nullptr);

     // Splay the given key
     tree = splay(tree, key);

     // If key is not present, then
     // return root
     if (key != tree->data)
         return std::make_pair(false,tree);

     // If key is present
     // If left child of root does not exist
     // make root->right as root
     SplayNode *temp;
     if (!tree->leftChild)
     {
         temp = tree;
         if(tree->rightChild) tree->rightChild->parent = temp->parent;
         tree = static_cast<SplayNode*>(tree->rightChild);
     }

     // Else if left child exits
     else
     {
         temp = tree;

         /*Note: Since key == root->key,
         so after Splay(root->left_child, key),
         the tree we get will have no right child tree
         and maximum node in left subtree will get splayed*/
         // New root
         tree = splay(static_cast<SplayNode*>(tree->leftChild), key);
         tree->parent = temp->parent;

         // Make right child of previous root  as
         // new root's right child
         tree->rightChild = temp->rightChild;
         if(temp->rightChild) temp->rightChild->parent = tree;
     }

     // free the previous root node, that is,
     // the node containing the key
     delete temp;

     // return root of the new Splay Tree
     return std::make_pair(true,tree);
}

SplayTree::SplayTree() : BST()
{

}

bool SplayTree::insert(const int &key)
{
    auto insertionResult = insert(static_cast<SplayNode*>(root), key);
    root = insertionResult.second;
    return insertionResult.first;
}

bool SplayTree::deleteItem(int val)
{
    auto deletionResult = deleteItem(static_cast<SplayNode*>(root), val);
    root = deletionResult.second;
    return deletionResult.first;
}

SplayNode::SplayNode(int val) : Node(val)
{

}
