#include "hieritem.h"

HierItem::HierItem(const QVector<QVariant> &data, HierItem *parent)
    : m_itemData(data), m_parentItem(parent)
{}

HierItem::~HierItem(){
    qDeleteAll(m_childItems);
}

void HierItem::appendChild(HierItem *item){
    if(item){
        m_childItems.append(item);
        item->m_parentItem = this;
    }
}

void HierItem::addChild(int row, HierItem* item){
    if(row >= 0){
        if(!item){
            item = new HierItem({});
            m_childItems.insert(row, item);
            item->m_parentItem = this;
        }
    }
}

bool HierItem::removeChild(int row){
    if(row >= 0 && childCount() > 0){
        m_childItems.removeAt(row);
        return true;
    }
    return false;
}

void HierItem::addColumn(int column, const QVariant& column_data){
    if(column >= 0)
        m_itemData.insert(column, column_data.toString());
}

bool HierItem::removeColumn(int column){
    if(column >= 0 && columnCount() > 0){
        m_itemData.removeAt(column);
        return true;
    }
    return false;
}

HierItem* HierItem::child(int row){
    //qDebug()<<"row= "<<row<<"elem_amount= "<<m_childItems.size();
    if (row < 0 || row >= m_childItems.size())
        return nullptr;

    return m_childItems.at(row);
}

int HierItem::childCount() const{
    return m_childItems.count();
}

int HierItem::columnCount() const{
    return m_itemData.count();
}

QVariant HierItem::data(int column) const{
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}

bool HierItem::setData(int column, const QVariant& value){
    if (column < 0)
        return false;
    if(column == m_itemData.size()){
        m_itemData.append(value.toString());
        return true;
    }
    if(column > m_itemData.size()){
        m_itemData.resize(column+1);
    }
    m_itemData.replace(column, value.toString());
    return true;
}

int HierItem::row() const{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<HierItem*>(this));

    return 0;
}

HierItem* HierItem::parentItem(){
    return m_parentItem;
}
