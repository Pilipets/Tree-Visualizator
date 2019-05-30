#ifndef RENDERWIDGETBUILDER_H
#define RENDERWIDGETBUILDER_H

#include "treerenderwidget.h"
#include "treefactory.h"
class BSTreeRenderWidgetBuilder{
public:
    BSTreeRenderWidgetBuilder(){}
    virtual ~BSTreeRenderWidgetBuilder() {}

    virtual void buildTree(TreeRenderWidget* widget) { widget->setWorkingTree(TreeFactory::createTree(0));}
    virtual void buildDrawer(TreeRenderWidget* widget)  {widget->setDrawer(new BSTreeDrawer());}

};

class SplayTreeRenderWidgetBuilder : public BSTreeRenderWidgetBuilder{
public:
    SplayTreeRenderWidgetBuilder() : BSTreeRenderWidgetBuilder(){}
    ~SplayTreeRenderWidgetBuilder() override{}

    void buildTree(TreeRenderWidget* widget) override {widget->setWorkingTree(TreeFactory::createTree(1));}
    void buildDrawer(TreeRenderWidget* widget) override {widget->setDrawer(new BSTreeDrawer());}
};

class TreeWidgetDirector{
private:
    BSTreeRenderWidgetBuilder* builder;
public:
    TreeWidgetDirector(BSTreeRenderWidgetBuilder* builder) : builder(builder){}
    ~TreeWidgetDirector(){ delete builder; }

    void ConstructRenderWindow(TreeRenderWidget* widget)
    {
        builder->buildTree(widget);
        builder->buildDrawer(widget);
    }
};

#endif // RENDERWIDGETBUILDER_H
