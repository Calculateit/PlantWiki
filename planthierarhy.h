#ifndef PLANTHIERARHY_H
#define PLANTHIERARHY_H

#include "hieritem.h"

#include <QAbstractItemModel>

/*
 * A model class. Responsible for the right data deployment in the memory.
 *  The atomary element is HierItem (i.e. a tree vertex pointer). The class
 *  provides a useful and essential interface for views in Qt and further
 *  working with data.
 */

class PlantHierarhy : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit PlantHierarhy(QObject *parent = nullptr);
    virtual ~PlantHierarhy() { delete rootItem; }

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex sibling(int row, int column, const QModelIndex &index) const override;


    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;

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

    HierItem *getRootItem() const { return rootItem; }

private:
    HierItem *rootItem;
    QModelIndex rootIndex;

};

#endif // PLANTHIERARHY_H
