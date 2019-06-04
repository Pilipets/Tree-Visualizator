
#include "treerenderwidget.h"

TreeRenderWidget::TreeRenderWidget(QWidget *parent):
    QWidget (parent)
{
    this->scale = 1.0;
}

TreeRenderWidget::~TreeRenderWidget()
{
    delete  tree;
    delete drawer;
}

void TreeRenderWidget::setWorkingTree(BST *tree)
{
    if(this->tree)
        delete this->tree;
    this->tree = tree;
}

void TreeRenderWidget::setDrawer(BSTreeDrawer *drawer)
{
    if(this->drawer)
        delete this->drawer;
    this->drawer = drawer;
}

QSize TreeRenderWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize TreeRenderWidget::sizeHint() const
{
    return QSize(50, 50);
}

void TreeRenderWidget::callRepaint()
{
    if (this->tree->isEmpty())
        return;

    this->scale += 0.1;
    this->repaint();
    this->scale -= 0.1;
    this->repaint();
}

void TreeRenderWidget::autoSize()
{
    //QSize size(tree->getTotalX(), tree->getTotalY());
    //this->setMinimumSize(size);
    //this->resize(size);
}

void TreeRenderWidget::ZoomIn()
{
    if (this->tree->isEmpty())
        return;
    if(this->scale < 2.0){
        this->scale += 0.1;
        this->repaint();
    }
}

void TreeRenderWidget::ZoomOut()
{
    if (this->tree->isEmpty())
        return;
    if(this->scale > 0.2) {
        this->scale -= 0.1;
        this->repaint();
    }
}

void TreeRenderWidget::paintEvent(QPaintEvent *event)
{
    if (this->tree->isEmpty())
        return;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);
    QPen pen;
    pen.setColor(Qt::black);

    painter.setBrush(brush);
    painter.setPen(pen);

    drawer->draw(&painter, tree->getRoot(), this->scale);

    this->autoSize();
}
