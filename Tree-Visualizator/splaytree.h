#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "tree.h"

struct SplayNode: public Node{
    SplayNode(const int &val);
};

class SplayTree : public Tree{
private:
    SplayNode *rightRotate(SplayNode *y);
    SplayNode *leftRotate(SplayNode *x);

    SplayNode *splay(SplayNode *root, const int &key);

    std::pair<bool, SplayNode*> insert(SplayNode *root, const int &key);
    std::pair<bool, SplayNode *> deleteItem(SplayNode *root, const int &key);
public:
    SplayTree() = default;
    ~SplayTree() override = default;

    bool insert(const int &key) override;
    bool deleteItem(const int &val) override;
    void accept(TreeVisitor &v) override;
};

#endif // SPLAYTREE_H
