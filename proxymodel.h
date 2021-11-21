#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QIdentityProxyModel>

#include "hieritem.h"

enum ViewType{
    tree,
    list
};

class proxyModel : public QIdentityProxyModel
{
    Q_OBJECT

public:
    QVariant data(const QModelIndex &index, int role) const override;
    int columnCount(const QModelIndex &parent) const override;
    void setViewtype(ViewType newViewtype);
    ViewType getViewtype() const;
    proxyModel();
private:
    int returnValidColumnCount(int realCount) const;

    ViewType viewtype;
};

#endif // PROXYMODEL_H
