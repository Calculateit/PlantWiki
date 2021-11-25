#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QIdentityProxyModel>

#include "constants.h"

#include "hieritem.h"
#include "planthierarhy.h"

/*
 * Provides a shell between Planthierarhy original model
 * and QTreeView, where we don`t want to show all information
 * from the source.
 */

class proxyModel : public QIdentityProxyModel
{
    Q_OBJECT

public:
    proxyModel() {};
    int columnCount(const QModelIndex &parent) const override;

private:
    int returnValidColumnCount(int realCount) const;
};

#endif // PROXYMODEL_H
