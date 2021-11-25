#ifndef JSONIOWORKER_H
#define JSONIOWORKER_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCborValue>
#include <QQueue>
#include <QMessageBox>
#include <QModelIndex>

#include "hieritem.h"
#include "planthierarhy.h"

/*
 * IO actions class. Includes everything you need for file operations
 * (reading, writing JSon files) in context of the program.
 */

class jsonIOworker : public QObject
{
    Q_OBJECT
public:
    explicit jsonIOworker(QWidget *parent = nullptr, const QString& file = QString())
        : path(file), parent_window(parent) {}
    bool loadDataFromFile(PlantHierarhy* root = nullptr);
    bool write();

private:
    bool readFile();
    void parseAndPlaceData();
    void parseArray(const QJsonArray& jsonArray, const QModelIndex &parent_index);
    QJsonObject addChildrenIntoArray(HierItem* vertex);

    QWidget* parent_window;
    QString path;
    QJsonDocument jDoc;
    PlantHierarhy* parent;
};

#endif // JSONIOWORKER_H
