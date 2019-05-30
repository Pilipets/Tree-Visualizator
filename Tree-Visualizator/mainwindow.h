#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bst.h"
#include "bstreememento.h"
#include "renderwidgetbuilder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void connectActions();

    //void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent* event);
private slots:
    void insertClicked();
    void deleteClicked();

    void SaveMenuClicked() const;
    void LoadMenuClicked() const;
    void ResetMenuClicked() const;
    void ExitMenuClicked();
    void newBSTreeOptionClicked();
    void newSplayTreeOptionClicked();

private:
    BST* curTree;
    TreeWidgetDirector* simpleTreeDirector;
    TreeWidgetDirector* splayTreeDirector;

};

#endif // MAINWINDOW_H
