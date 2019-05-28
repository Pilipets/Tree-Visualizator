#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curTree = ui->renderArea->getWorkingTree();
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(ui->insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertClicked() const
{

    QString value = ui->insertTxtBox->text();
    int val = value.toInt();

    if(!this->curTree->insert(val))
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " already exists in tree.");
     else
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " inserted.");

    ui->renderArea->repaint();
    ui->insertTxtBox->setText("");
}

void MainWindow::deleteClicked() const
{
    QString value = ui->deleteTxtBox->text();
    int val = value.toInt();

    if(!this->curTree->deleteItem(value.toInt()))
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " is not in tree...");
    else
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " deleted.");

    ui->renderArea->repaint();
    ui->deleteTxtBox->setText("");
}
