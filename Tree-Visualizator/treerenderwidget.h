#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QColor>
#include "bst.h"

class TreeRenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TreeRenderWidget(QWidget *parent = 0);
    void setWorkingTree(BST* tree);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    BST *tree;
    QColor backgroundColor;
    QColor nodeColor;
    QColor textColor;
    double scale;
};

#endif // RENDERWIDGET_H
