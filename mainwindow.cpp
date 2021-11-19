#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hierarhyModel = new PlantHierarhy(this);
    IOworker = new jsonIOworker(this, "/home/user/Test");


    if(IOworker->loadDataFromFile(hierarhyModel))
        ui->treeView->setModel(hierarhyModel);
    //ui->treeView->show();
    //ui->listView->setModel(hierarhyModel);
    //hierarhyModel->test();
    //ui->listView->show();

}

MainWindow::~MainWindow()
{
    delete IOworker;
    delete hierarhyModel;
    delete ui;
}
