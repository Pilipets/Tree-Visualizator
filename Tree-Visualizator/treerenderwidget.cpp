
#include "treerenderwidget.h"

TreeRenderWidget::TreeRenderWidget(QWidget *parent):
    QWidget (parent)
{
    this->tree = TreeFactory::createTree(1);
    this->drawer = new BSTreeDrawer();
}

void TreeRenderWidget::paintEvent(QPaintEvent *event)
{
    if (this->tree->isEmpty())
        return;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    QPen pen;
    pen.setColor(Qt::black);

    painter.setBrush(brush);
    painter.setPen(pen);

    drawer->draw(&painter, tree->getRoot());
}
