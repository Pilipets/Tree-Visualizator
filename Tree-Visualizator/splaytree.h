#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "bst.h"

struct SplayNode: public Node{
    SplayNode(int val);
};

class SplayTree : public BST{
private:
    SplayNode *rightRotate(SplayNode *y);
    SplayNode *leftRotate(SplayNode *x);

    SplayNode *splay(SplayNode *root, const int &key);

    std::pair<bool, SplayNode*> insert(SplayNode *root, const int &key);
    //std::pair<bool, SplayNode*> delete_key(SplayNode *root, const int &key);
public:
    SplayTree();

    bool insert(const int &key) override;
};

#endif // SPLAYTREE_H
