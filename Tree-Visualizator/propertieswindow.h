#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include "treevisitor.h"
#include "tree.h"
class PropertiesWindow : public QMainWindow
{
    QWidget *centralWidget;
public:
    explicit PropertiesWindow(QWidget *parent = nullptr);
    ~PropertiesWindow();
    void show();
    void closeWindow();
    void update(Tree *tree);
private:
    QVBoxLayout *labelLayout;
    QLabel *typeLabel;
    QLineEdit *typeValue;
    QVBoxLayout *textAreaLayout;

    QHBoxLayout *containerLayout;
    QVBoxLayout *mainLayout;
    QTextEdit *inOrderTraversal;
    QTextEdit *preOrderTraversal;
    QTextEdit *postOrderTraversal;
};

#endif // PROPERTIESWINDOW_H
