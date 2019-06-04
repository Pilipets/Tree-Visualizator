#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QColor>
#include "treefactory.h"
#include "treedrawer.h"
class TreeRenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TreeRenderWidget(QWidget *parent = 0);
    ~TreeRenderWidget();
    Tree* getWorkingTree() const { return  tree; }
    void setWorkingTree(Tree *tree);
    void setDrawer(TreeDrawer* drawer);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void callRepaint();
    void autoSize();
    void ZoomIn();
    void ZoomOut();
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double scale;
    TreeDrawer* drawer;
    Tree *tree;
};

#endif // RENDERWIDGET_H
