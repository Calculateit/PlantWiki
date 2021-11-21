#ifndef ELEMENTVIEW_H
#define ELEMENTVIEW_H

#include <QObject>
#include <QAbstractItemModel>
#include <QLabel>
#include <QHash>

#include "hieritem.h"

class ElementView : public QObject
{
    Q_OBJECT
public:
    explicit ElementView(QAbstractItemModel& model, QLabel* image_label, QLabel* decription_label);
    void updateImage();
    void updateDescription();

public slots:
    void updateElementView(const QModelIndex& image_index, const QModelIndex& decription_index);
    void testSlot(const QModelIndex& index);

private:
    QModelIndex imagePath;
    QModelIndex description;
    QAbstractItemModel& model;
    QHash<QString, QLabel*> labels;
};

#endif // ELEMENTVIEW_H
