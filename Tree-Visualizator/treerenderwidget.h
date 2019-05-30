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
    ~TreeRenderWidget();
    BST* getWorkingTree() const { return  tree; }
    void setWorkingTree(BST *tree);
    void setDrawer(BSTreeDrawer* drawer);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void callRepaint();
    void autoSize();
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double scale;
    BSTreeDrawer* drawer;
    BST *tree;
};

#endif // RENDERWIDGET_H
