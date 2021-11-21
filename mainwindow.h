#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "jsonioworker.h"
#include "planthierarhy.h"
#include "proxymodel.h"
#include "elementview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showElement(const QModelIndex& index) const;

    Ui::MainWindow *ui;
    jsonIOworker* IOworker;
    PlantHierarhy* hierarhyModel;
    proxyModel* proxytreeModel;
    ElementView* elemView;
};
#endif // MAINWINDOW_H
