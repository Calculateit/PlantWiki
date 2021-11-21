#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hierarhyModel = new PlantHierarhy(this);

    IOworker = new jsonIOworker(this, "/home/user/Test");

    if(IOworker->loadDataFromFile(hierarhyModel)){

        proxytreeModel = new proxyModel();
        proxytreeModel->setViewtype(ViewType::tree);
        proxytreeModel->setSourceModel(hierarhyModel);
        ui->treeView->setModel(proxytreeModel);
        elemView = new ElementView(*hierarhyModel, ui->imageLabel, ui->descriptionLabel);

        connect(ui->treeView, &QAbstractItemView::pressed, this,
                &MainWindow::showElement);
        connect(ui->treeView, &QAbstractItemView::pressed, elemView, &ElementView::testSlot);
    }

    //ui->treeView->show();

    //hierarhyModel->test();
    //ui->listView->show();

}

void MainWindow::showElement(const QModelIndex& index) const
{
    QVector<QModelIndex> indexes;
    for(int i : {2, 3}){
        indexes.append(hierarhyModel->sibling(index.row(), i, index));
    }
    elemView->updateElementView(indexes.at(0), indexes.at(1));
}

MainWindow::~MainWindow(){
    delete IOworker;
    delete hierarhyModel;
    delete elemView;
    delete proxytreeModel;
    delete ui;
}
