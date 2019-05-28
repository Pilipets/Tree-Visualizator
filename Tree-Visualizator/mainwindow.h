#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bst.h"
#include "bstreememento.h"
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
private slots:
    void insertClicked() const;
    void deleteClicked() const;

    void SaveMenuClicked() const;

private:
    BST* curTree;
    HistoryManager* stateObserver;
};

#endif // MAINWINDOW_H
