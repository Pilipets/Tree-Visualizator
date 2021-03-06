#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tree.h"
#include "treememento.h"
#include "renderwidgetbuilder.h"
#include "propertieswindow.h"
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
    void disconnectActions();

    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent* event);
private slots:
    void insertClicked();
    void deleteClicked();

    void PropertiesButtonClicked();
    void SaveMenuClicked() const;
    void LoadMenuClicked() const;
    void ResetMenuClicked() const;
    void ExitMenuClicked();
    void newBSTreeOptionClicked();
    void newSplayTreeOptionClicked();

    void on_btnZoomIn_clicked();

    void on_btnZoomOut_clicked();

private:
    Tree* curTree;
    TreeWidgetDirector* bsTreeDirector;
    TreeWidgetDirector* splayTreeDirector;
    PropertiesWindow *prop;

};

#endif // MAINWINDOW_H
