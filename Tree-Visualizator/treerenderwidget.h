#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QColor>
#include "treefactory.h"
#include "bstreedrawer.h"
class TreeRenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TreeRenderWidget(QWidget *parent = 0);
    BST* getWorkingTree() const { return  tree; }
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    BSTreeDrawer* drawer;
    BST *tree;
};

#endif // RENDERWIDGET_H
