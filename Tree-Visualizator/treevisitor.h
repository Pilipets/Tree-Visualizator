#ifndef TREEVISITOR_H
#define TREEVISITOR_H

#include "bst.h"
#include "splaytree.h"

class TreeVisitor {
public:
  virtual void visit(BSTree *pTree) = 0;
  virtual void visit(SplayTree *pTree) = 0;
  virtual ~TreeVisitor() = default;
};

class Element {
public:
  virtual void accept(TreeVisitor &v) = 0;

  virtual ~Element() = default;
};

#endif // TREEVISITOR_H

