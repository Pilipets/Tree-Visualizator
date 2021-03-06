#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextStream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include "propertieswindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    prop = new PropertiesWindow();

    bsTreeDirector = new TreeWidgetDirector(new BSTreeRenderWidgetBuilder);
    splayTreeDirector = new TreeWidgetDirector(new SplayTreeRenderWidgetBuilder);

    splayTreeDirector->ConstructRenderWindow(ui->renderArea);

    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(ui->insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(ui->propButton, &QPushButton::clicked, this, &MainWindow::PropertiesButtonClicked);

    connectActions();
    // Create default save directory
    QString directory = QDir::currentPath() + "/TreeVisualizer";
    if (!QDir(directory).exists())
        QDir().mkdir(directory);
}

MainWindow::~MainWindow()
{
    disconnect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    disconnect(ui->insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    disconnect(ui->propButton, &QPushButton::clicked, this, &MainWindow::PropertiesButtonClicked);
    delete ui;

    delete bsTreeDirector;
    delete  splayTreeDirector;
    delete prop;

}

void MainWindow::connectActions()
{
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::SaveMenuClicked);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::LoadMenuClicked);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::ExitMenuClicked);
    connect(ui->actionBST, &QAction::triggered, this, &MainWindow::newBSTreeOptionClicked);
    connect(ui->actionSplay_Tree, &QAction::triggered, this, &MainWindow::newSplayTreeOptionClicked);
    connect(ui->actionReset, &QAction::triggered, this, &MainWindow::ResetMenuClicked);
}

void MainWindow::disconnectActions()
{
    disconnect(ui->actionSave, &QAction::triggered, this, &MainWindow::SaveMenuClicked);
    disconnect(ui->actionLoad, &QAction::triggered, this, &MainWindow::LoadMenuClicked);
    disconnect(ui->actionExit, &QAction::triggered, this, &MainWindow::ExitMenuClicked);
    disconnect(ui->actionBST, &QAction::triggered, this, &MainWindow::newBSTreeOptionClicked);
    disconnect(ui->actionSplay_Tree, &QAction::triggered, this, &MainWindow::newSplayTreeOptionClicked);
    disconnect(ui->actionReset, &QAction::triggered, this, &MainWindow::ResetMenuClicked);
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    prop->closeWindow(); // close property window
    event->setAccepted(true); // set whether to close application or not
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    ui->renderArea->callRepaint();
}

void MainWindow::insertClicked()
{
    curTree = ui->renderArea->getWorkingTree();

    QString values = ui->insertTxtBox->text();
    QStringList valueList = values.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QStringListIterator iterator(valueList);

    while (iterator.hasNext())
    {
        int val = iterator.next().toInt();
        if(!curTree->insert(val))
            this->ui->statusBar->showMessage("Value " + QString::number(val) + " already exists in tree.");
        else
            this->ui->statusBar->showMessage("Value " + QString::number(val) + " inserted.");
    }
    ui->renderArea->repaint();
    ui->insertTxtBox->setText("");
}

void MainWindow::deleteClicked()
{
    curTree = ui->renderArea->getWorkingTree();

    QString values = ui->deleteTxtBox->text();
    QStringList valueList = values.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QStringListIterator iterator(valueList);

    while (iterator.hasNext())
    {
        int val = iterator.next().toInt();
        if(!curTree->deleteItem(val))
            this->ui->statusBar->showMessage("Value " + QString::number(val) + " is not in tree.");
        else
            this->ui->statusBar->showMessage("Value " + QString::number(val) + " deleted.");
    }
    ui->renderArea->repaint();
    ui->deleteTxtBox->setText("");
}

void MainWindow::PropertiesButtonClicked()
{
    prop->show();
    prop->update(this->curTree);
}

void MainWindow::SaveMenuClicked() const
{
    QString fileName = QFileDialog::getSaveFileName(const_cast<MainWindow*>(this), tr("Save File"),
                                                   QDir::currentPath() + "/TreeVisualizer",
                                 tr("Text files (*.txt);;Images (*.png *.jpg)"));

    if (QFileInfo(fileName).suffix() == "txt")
    {
        TreeMemento state = curTree->createMemento();
        if(!state.writeToFile(fileName))
        {
            ui->statusBar->showMessage("Unable to open file at" + fileName);
            return;
        }
        ui->statusBar->showMessage("Tree was successfully saved to " + fileName);
    }

    // if not txt, save as image
    else if(!ui->renderArea->grab().save(fileName))
    {
        ui->statusBar->showMessage("Error: image was not saved!");
    }
    else{
        ui->statusBar->showMessage("Image was successfully saved.");
    }
}

void MainWindow::LoadMenuClicked() const
{
    QString fileName = QFileDialog::getOpenFileName(const_cast<MainWindow*>(this), tr("Open File"),
                                 QDir::currentPath() + "/TreeVisualizer",
                                 tr("Text files (*.txt)"));
    curTree->clear();

    TreeMemento state;
    if(!state.readFromFile(fileName))
    {
        ui->statusBar->showMessage("Could not open file!");
    }
    else {
        curTree->clear();
        curTree->setMemento(state);
    }

    ui->renderArea->repaint();

    ui->statusBar->showMessage("File successfully opened!");
}

void MainWindow::ResetMenuClicked() const
{
    ui->statusBar->showMessage("Reset tree.");
    curTree->clear();
    ui->renderArea->repaint();
}

void MainWindow::ExitMenuClicked()
{
    this->close();
}

void MainWindow::newBSTreeOptionClicked()
{
    bsTreeDirector->ConstructRenderWindow(ui->renderArea);
    ui->renderArea->repaint();
    ui->statusBar->showMessage("New BST was created");
}

void MainWindow::newSplayTreeOptionClicked()
{
    splayTreeDirector->ConstructRenderWindow(ui->renderArea);
    ui->renderArea->repaint();
    ui->statusBar->showMessage("New Splay Tree was created");
}

void MainWindow::on_btnZoomIn_clicked()
{
    ui->renderArea->ZoomIn();
    ui->statusBar->showMessage("Window was extended");
}

void MainWindow::on_btnZoomOut_clicked()
{
    ui->renderArea->ZoomOut();
    ui->statusBar->showMessage("Window was narrowed");
}
