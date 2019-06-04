#ifndef RENDERWIDGETBUILDER_H
#define RENDERWIDGETBUILDER_H

#include "treerenderwidget.h"
#include "treefactory.h"
class TreeRenderWidgetBuilder{
public:
    TreeRenderWidgetBuilder() = default;
    virtual ~TreeRenderWidgetBuilder() = default;

    virtual void buildTree(TreeRenderWidget* widget) = 0;
    virtual void buildDrawer(TreeRenderWidget* widget) = 0;

};

class BSTreeRenderWidgetBuilder : public TreeRenderWidgetBuilder{
public:
    BSTreeRenderWidgetBuilder() = default;
    ~BSTreeRenderWidgetBuilder() override = default;

    void buildTree(TreeRenderWidget* widget) override { widget->setWorkingTree(TreeFactory::createTree(0));}
    void buildDrawer(TreeRenderWidget* widget) override {widget->setDrawer(new TreeDrawer());}
};

class SplayTreeRenderWidgetBuilder : public TreeRenderWidgetBuilder{
public:
    SplayTreeRenderWidgetBuilder() = default;
    ~SplayTreeRenderWidgetBuilder() override = default;

    void buildTree(TreeRenderWidget* widget) override {widget->setWorkingTree(TreeFactory::createTree(1));}
    void buildDrawer(TreeRenderWidget* widget) override {widget->setDrawer(new TreeDrawer());}
};

class TreeWidgetDirector{
private:
    TreeRenderWidgetBuilder* builder;
public:
    TreeWidgetDirector(TreeRenderWidgetBuilder* builder) : builder(builder){}
    ~TreeWidgetDirector(){ delete builder; }

    void ConstructRenderWindow(TreeRenderWidget* widget)
    {
        builder->buildTree(widget);
        builder->buildDrawer(widget);
    }
};

#endif // RENDERWIDGETBUILDER_H
