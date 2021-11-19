#include "planthierarhy.h"

PlantHierarhy::PlantHierarhy(QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new HierItem({"Hier name", "Name", "Description", "Image path"});
    rootIndex = createIndex(0, 0, rootItem);
    //createIndex(0, 0, QModelIndex());
    emit dataChanged(rootIndex, rootIndex, QVector<int>() << Qt::EditRole);
    //setupModelData(data.split('\n'), rootItem);
}

void PlantHierarhy::setDataToView(const QVector<QVariant>& data, const int level){
    HierItem* parentItem = rootItem;
    if(!level)
        rootItem->appendChild(new HierItem(data));
    else
        while(level){
            createIndex(parentItem->row(), 0, parentItem);
        }
}

void PlantHierarhy::appendRootChildren(const QVector<QVariant>& data){
    rootItem->appendChild(new HierItem(data));
}

QModelIndex PlantHierarhy::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    HierItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<HierItem*>(parent.internalPointer());

    HierItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex PlantHierarhy::addIndex(int row, int column, const QModelIndex &parent) const
{
    HierItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<HierItem*>(parent.internalPointer());

    if (!hasIndex(row, column, parent))
        parentItem->addChild(row);

    HierItem *childItem = parentItem->child(row);
    if (childItem){
        //qDebug()<<"Normal!\n";
        return createIndex(row, column, childItem);
    }
    return QModelIndex();
}

QModelIndex PlantHierarhy::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();
    HierItem *childItem = static_cast<HierItem*>(index.internalPointer());
    HierItem *parentItem = childItem->parentItem();

    if (parentItem == nullptr){
        //qDebug()<<"ERROR parent()";
        return QModelIndex();
    }
    if(parentItem == rootItem)
        return rootIndex;

    return createIndex(parentItem->row(), 0, parentItem);
}

int PlantHierarhy::rowCount(const QModelIndex &parent) const
{
    HierItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<HierItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int PlantHierarhy::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<HierItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant PlantHierarhy::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    HierItem *item = static_cast<HierItem*>(index.internalPointer());
    //qDebug()<<"get_data "<<item<<" row= "<<index.row()<<" column= "<<index.column()<<" meaning:"<<item->data(index.column());
    if(item)
        return item->data(index.column());
    return QVariant();
}

bool PlantHierarhy::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role==Qt::EditRole && index.isValid() && data(index, role) != value) {
        HierItem *item = static_cast<HierItem*>(index.internalPointer());
        //qDebug()<<"inside setData() "<<item;
        if(item->setData(index.column(), value)){
            //qDebug()<<"data_changed";
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }
    //qDebug()<<"CRITICAL data_NOT_changed";
    return false;
}

Qt::ItemFlags PlantHierarhy::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractItemModel::flags(index)|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled;
}

bool PlantHierarhy::insertRows(int row, int count, const QModelIndex &parent)
{
    if (!parent.isValid())
        return false;
    HierItem *item = static_cast<HierItem*>(parent.internalPointer());
    beginInsertRows(parent, row, row + count - 1);
    for(int i = 0; i < count; ++i){
        item->addChild(row);
    }
    endInsertRows();
    return true;
}

bool PlantHierarhy::insertColumns(int column, int count, const QModelIndex &parent)
{
    if (!parent.isValid())
        return false;
    HierItem *item = static_cast<HierItem*>(parent.internalPointer());
    beginInsertColumns(parent, column, column + count - 1);
    for(int i = 0; i < count; ++i){
        item->addColumn(column);
    }
    endInsertColumns();
    return true;
}

bool PlantHierarhy::removeRows(int row, int count, const QModelIndex &parent)
{
    if (!parent.isValid())
        return false;
    HierItem *item = static_cast<HierItem*>(parent.internalPointer());
    beginRemoveRows(parent, row, row + count - 1);
    for(int i = 0; i < count; ++i){
        if(!item->removeChild(row))
            break;
    }
    endRemoveRows();
    return true;
}

bool PlantHierarhy::removeColumns(int column, int count, const QModelIndex &parent)
{
    if (!parent.isValid())
        return false;
    HierItem *item = static_cast<HierItem*>(parent.internalPointer());
    beginRemoveColumns(parent, column, column + count - 1);
    for(int i = 0; i < count; ++i){
        if(!item->removeColumn(column))
            break;
    }
    endRemoveColumns();
    return true;
}


void PlantHierarhy::test(){
    qDebug()<<rootItem->child(0)->child(0)->data(0).toString()<<" ";
    qDebug()<<rootItem->child(0)->child(0)->child(0)->data(0).toString()<<" ";
    HierItem* vertex = nullptr;
    int childs = rootItem->childCount();
    if(childs>0){
        for(int i=0; i<childs; ++i){
            vertex = rootItem->child(i);
            if(!vertex)  qDebug()<<"ERROR!\n";
            for(int j = 0; j < 4; ++j)
                qDebug()<<vertex->data(j).toString()<<" ";
        }
    }
}
////QVariant PlantHierarhy::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    //if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//           // return rootItem->data(section);

//    return QVariant();
//}

////bool PlantHierarhy::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}


//bool PlantHierarhy::hasChildren(const QModelIndex &parent) const
//{
//    if (!parent.isValid())
//        return false;
//    HierItem *parentItem = static_cast<HierItem*>(parent.internalPointer());
//    if(parentItem->childCount() > 0)
//        return true;
//    return false;
//}

/*/bool PlantHierarhy::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}*/

//void PlantHierarhy::fetchMore(const QModelIndex &parent)
//{
//    // FIXME: Implement me!
//}
