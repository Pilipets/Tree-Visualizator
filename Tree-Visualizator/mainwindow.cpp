#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    tree = new BST();
    ui->setupUi(this);

    //connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(ui->insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    ui->renderArea->setWorkingTree(tree);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertClicked() const
{
    QString values = ui->insertTxtBox->text();
    int val = values.toInt();

    if(!this->tree->insert(val))
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " already exists in tree.");
     else
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " inserted.");

    ui->renderArea->repaint();
    ui->insertTxtBox->setText("");
}
