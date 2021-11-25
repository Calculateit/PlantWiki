#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include "constants.h"

#include "jsonioworker.h"
#include "planthierarhy.h"
#include "proxymodel.h"
#include "elementview.h"

/*
 * Main window class. Provides visual interface for every operation in program.
 * Contains a lot of WYSIWYG methods, sends signals according to the users
 * actions.
 */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum ErrorType{
    information,
    warning,
    critical
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void fileSet(const QString& filename);

private:
    void openFile();
    void showElement(const QModelIndex& index) const;
    void openAndShowHierarhy(const QString& filename);
    void makeFileActionsButtonsActive() const;
    void cleanPastHiearhy();

    //hierarhy actions:
    void addRow();
    void removeRow();
    void addChild();

    void changeElementDescription();
    void changeElementImage();

    void errorFunc(const QString& header, const QString& errorText, ErrorType type);

    Ui::MainWindow *ui;
    jsonIOworker* IOworker;
    PlantHierarhy* hierarhyModel;
    proxyModel* proxytreeModel;
    ElementView* elemView;
};
#endif // MAINWINDOW_H
