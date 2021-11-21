#include "proxymodel.h"
#include "planthierarhy.h"

proxyModel::proxyModel() {}

ViewType proxyModel::getViewtype() const
{
    return viewtype;
}

void proxyModel::setViewtype(ViewType newViewtype){
    viewtype = newViewtype;
}

QVariant proxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    HierItem *item = static_cast<HierItem*>(index.internalPointer());

    int column = index.column();
    bool informationShouldBeShown = false;

    switch(viewtype){
    case (ViewType::list):
        if(column >= 2)
           informationShouldBeShown = true;
        break;
    case (ViewType::tree):
        if(column < 2)
           informationShouldBeShown = true;
        break;
    default:
        return QVariant();
    }
    if(item && informationShouldBeShown)
        return item->data(column);
    return QVariant();
}

int proxyModel::columnCount(const QModelIndex &parent) const
{
    qDebug()<<"proxyModel::columnCount";
    if (parent.isValid()){
        return returnValidColumnCount(static_cast<HierItem*>(parent.internalPointer())->columnCount());
    }
    return returnValidColumnCount(static_cast<PlantHierarhy*>(sourceModel())->getRootItem()->columnCount());
}

int proxyModel::returnValidColumnCount(int realCount) const
{
    int validCount;

    switch(viewtype){
    case (ViewType::list):
        validCount = (realCount > 2) ? 2 : realCount;
        qDebug()<<"list!" << validCount;
        break;
    case (ViewType::tree):
        validCount = (realCount <= 2) ? realCount : 2;
        qDebug()<<"tree!" << validCount;
        break;
    default:
        qDebug()<<"error!";
        return 0;
    }
    return validCount;
}
