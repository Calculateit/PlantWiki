#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), IOworker(nullptr),
      hierarhyModel(nullptr), proxytreeModel(nullptr), elemView(nullptr)
{
    ui->setupUi(this);
    connect(this, &MainWindow::fileSet, this, &MainWindow::openAndShowHierarhy);//setting file -> load hierarhy and show it
    connect(ui->openFile, &QAction::triggered, this, &MainWindow::openFile);//press openFile btn -> show file choosing window

}

void MainWindow::openFile(){
    QString filename=QFileDialog::getOpenFileName(this, "Выберите файл иерархии",
                                       QDir::homePath(), "Json files (*.json);; Any file (*.*);; .");
    if(!filename.isEmpty())
        emit fileSet(filename);
}

void MainWindow::openAndShowHierarhy(const QString& filename){
    cleanPastHiearhy();
    hierarhyModel = new PlantHierarhy(this);
    IOworker = new jsonIOworker(this, filename);

    if(IOworker->loadDataFromFile(hierarhyModel)){
        proxytreeModel = new proxyModel();
        proxytreeModel->setSourceModel(hierarhyModel);
        ui->treeView->setModel(proxytreeModel);
        elemView = new ElementView(*hierarhyModel, ui->imageLabel, ui->descriptionLabel);
        makeFileActionsButtonsActive();

        connect(ui->treeView, &QAbstractItemView::pressed, this,
                &MainWindow::showElement);                                  //press row -> show element

        connect(ui->addRow, &QAction::triggered, this,
                &MainWindow::addRow);
        connect(ui->removeRow, &QAction::triggered, this,
                &MainWindow::removeRow);
        connect(ui->addChild, &QAction::triggered, this,
                &MainWindow::addChild);
        connect(ui->changeImage, &QAction::triggered, this,
                &MainWindow::changeElementImage);
        connect(ui->changeDescriprion, &QAction::triggered, this,
                &MainWindow::changeElementDescription);
        connect(ui->writeFile, &QAction::triggered, IOworker,
                &jsonIOworker::write);
    }
}

void MainWindow::makeFileActionsButtonsActive() const {
    ui->actionsMenu->setEnabled(true);
    ui->writeFile->setEnabled(true);
}

void MainWindow::cleanPastHiearhy(){
    ui->actionsMenu->setDisabled(true);
    ui->writeFile->setDisabled(true);
    QVector<QObject*> to_delete{IOworker, hierarhyModel, elemView, proxytreeModel};
    for(const auto & it: to_delete)
         if(it) delete it;
}

void MainWindow::addRow(){
    QModelIndex parent = ui->treeView->currentIndex().parent();

    int new_row = hierarhyModel->rowCount(parent);
    if(!hierarhyModel->insertRow(new_row, parent))
        errorFunc("Не получилось добавить строку", "Критическая ошибка работы программы.",
                  ErrorType::critical);
}

//void MainWindow::addColumn() const
//{
//    //qDebug()<<"addColumn inside";
//    QModelIndex index = ui->treeView->currentIndex();
//    //int realLastColumnIndex = hierarhyModel->columnCount(index);
//    //realLastColumnIndex = (realLastColumnIndex >= DEFINITION_COLUMNS_AMOUNT) ? realLastColumnIndex - DEFINITION_COLUMNS_AMOUNT : realLastColumnIndex;
//    //qDebug()<<"realLastColumnIndex= "<<realLastColumnIndex;
//    if(!hierarhyModel->insertColumn(hierarhyModel->columnCount(index), index)){
//        qDebug()<<"ERROR_COLUMN";
//    }
//}

void MainWindow::removeRow(){
    QModelIndex index = ui->treeView->currentIndex();
    if(!hierarhyModel->removeRow(index.row(), index.parent()))
        errorFunc("Не получилось удалить строку", "Критическая ошибка работы программы.",
                  ErrorType::critical);
}

void MainWindow::addChild(){
    QModelIndex index = ui->treeView->currentIndex();
    if(!hierarhyModel->insertRow(0, index)){
        errorFunc("Не получилось добавить потомка", "Критическая ошибка работы программы.",
                  ErrorType::critical);
    }
}

void MainWindow::changeElementDescription(){
    bool ok = false;
    const QString newInfo =QInputDialog::getMultiLineText(this, tr("Измените описание"),
                                                 tr("Введите новый текст:"), QString(), &ok);
    if (ok && !newInfo.isEmpty())
        elemView->setNewDescription(newInfo);
}

void MainWindow::changeElementImage(){
    const QString newPath =QFileDialog::getOpenFileName(this, tr("Выберите новую картинку"),
                                                         QDir::homePath(), "Any file (*.*);; .");
    qDebug()<<"imageSetEmit"<<newPath;
    if (!newPath.isEmpty())
        elemView->setNewImage(newPath);
}

void MainWindow::errorFunc(const QString &header, const QString &errorText, ErrorType type){
    switch (type) {
    case ErrorType::critical:
        QMessageBox::critical(this, header, errorText);
        break;
    case ErrorType::information:
        QMessageBox::information(this, header, errorText);
        break;
    case ErrorType::warning:
        QMessageBox::warning(this, header, errorText);
        break;
    default:
        return;
    }
}

void MainWindow::showElement(const QModelIndex& index) const {
    QVector<QModelIndex> indexes;
    for(int i : {2, 3}){
        indexes.append(hierarhyModel->sibling(index.row(), i, index));
    }
    elemView->updateElementView(indexes.at(1), indexes.at(0));
}

MainWindow::~MainWindow(){
    cleanPastHiearhy();
    delete ui;
}
