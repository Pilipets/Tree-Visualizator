
#include "treerenderwidget.h"

TreeRenderWidget::TreeRenderWidget(QWidget *parent):
    QWidget (parent)
{
    this->scale = 1.0;
    this->nodeColor = Qt::red;
    this->backgroundColor = Qt::white;
    this->textColor = Qt::black;
}

void TreeRenderWidget::setWorkingTree(BST *tree)
{
    this->tree = tree;
}

void TreeRenderWidget::paintEvent(QPaintEvent *event)
{
    if (this->tree->isEmpty())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(this->nodeColor);
    brush.setStyle(Qt::SolidPattern);

    QPen pen;
    pen.setColor(this->textColor);

    painter.setBrush(brush);
    painter.setPen(pen);

    this->tree->draw(&painter, this->scale);
}
