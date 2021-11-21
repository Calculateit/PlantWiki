#ifndef PLANTHIERARHY_H
#define PLANTHIERARHY_H

#include "hieritem.h"

#include <QAbstractItemModel>

class PlantHierarhy : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit PlantHierarhy(QObject *parent = nullptr);
    virtual ~PlantHierarhy() { delete rootItem; }

    // Header:
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex sibling(int row, int column, const QModelIndex &index) const override;


    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;

//    // Fetch data dynamically:
//    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

//    bool canFetchMore(const QModelIndex &parent) const override;
//    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    QModelIndex addIndex(int row, int column, const QModelIndex &parent) const;
    QModelIndex getRootIndex() const { return rootIndex; }

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    QVector<QModelIndex*> getFullData(const QModelIndex &index) const;

    void test();

    HierItem *getRootItem() const;

private:
    HierItem *rootItem;
    QModelIndex rootIndex;

};

#endif // PLANTHIERARHY_H
