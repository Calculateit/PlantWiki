#ifndef HIERITEM_H
#define HIERITEM_H

#include <QVariant>

/*
 * Class of a hierarhy tree item. Every child includes
 * root pointer, massive of childs pointers and finally its own data.
 */

class HierItem
{
public:
    explicit HierItem(const QVector<QVariant> &data, HierItem *parentItem = nullptr);
    virtual ~HierItem();

    void appendChild(HierItem *child);
    void addChild(int row, HierItem* data = nullptr);
    bool removeChild(int row);

    void appendColumn(const QVariant& item);
    void addColumn(int column, const QVariant& column_data = QVariant());
    bool removeColumn(int column);

    HierItem *child(int row);
    int childCount() const;
    int columnCount() const;

    QVariant data(int column) const;
    bool setData(int column, const QVariant& value);

    int row() const;
    HierItem* parentItem();

private:
    QVector<QVariant> m_itemData;

    HierItem *m_parentItem;
    QVector<HierItem*> m_childItems;
};

#endif // HIERITEM_H
