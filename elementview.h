#ifndef ELEMENTVIEW_H
#define ELEMENTVIEW_H

#include <QObject>
#include <QAbstractItemModel>
#include <QLabel>
#include <QHash>
#include <QDir>

#include "constants.h"
#include "hieritem.h"

/*
 * Class of view area, which was placed on the right side of window.
 * Includes 2 indexes to a data model`s information needed for the element,
 * a model ref and 2 labels, where info contains.
 */

class ElementView : public QObject
{
    Q_OBJECT
public:
    explicit ElementView(QAbstractItemModel& model, QLabel* image_label, QLabel* description_label);
    void updateImage();
    void updateDescription();

    void setNewImage(const QString&);
    void setNewDescription(const QString&);
public slots:
    void updateElementView(const QModelIndex& image_index, const QModelIndex& description_index);

private:
    QModelIndex imagePath;
    QModelIndex description;
    QAbstractItemModel& model;
    QHash<QString, QLabel*> labels;
};

#endif // ELEMENTVIEW_H
