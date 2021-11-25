#include "proxymodel.h"
#include "planthierarhy.h"

int proxyModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return returnValidColumnCount(static_cast<HierItem*>(parent.internalPointer())->columnCount());
    return returnValidColumnCount(static_cast<PlantHierarhy*>(sourceModel())->getRootItem()->columnCount());
}

int proxyModel::returnValidColumnCount(int realCount) const {
    if(realCount >= 4)
        return (realCount - 2);
    return realCount;
}
