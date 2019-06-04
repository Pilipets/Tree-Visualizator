#ifndef TREEVISITOR_H
#define TREEVISITOR_H

#include<QString>
class BSTree;
class SplayTree;
class Tree;

class TreeVisitor {
public:
  virtual void visit(BSTree *pTree) = 0;
  virtual void visit(SplayTree *pTree) = 0;
  virtual ~TreeVisitor() = default;
};

class GetTraversal : public TreeVisitor{
    public:
    QString treeType;
    QString preOrderTraversal;
    QString inOrderTraversal;
    QString postOrderTraversal;
public:
    void visit(BSTree *pTree) override;
    void visit(SplayTree* pTree) override;
private:
    QString getPreOrderTraversal(Tree* tree) const;
    QString getInOrderTraversal(Tree* tree) const;
    QString getPostOrderTraversal(Tree* tree) const;
};

#endif // TREEVISITOR_H

