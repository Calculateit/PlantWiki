#include "elementview.h"

ElementView::ElementView(QAbstractItemModel& model, QLabel* image_label, QLabel* decription_label)
    : model(model)
{
    labels.insert("image", image_label);
    labels.insert("description", decription_label);
}

void ElementView::updateImage(){                                    //CHANGE!!!
    if(0==1){
        QString path = imagePath.data().toString();
        QPixmap pic(path);
        labels["image"]->setPixmap(pic);
    }
    //
        labels["image"]->setText(imagePath.data().toString());
    //
}

void ElementView::updateDescription(){
    QString new_description = description.data().toString();
    labels["description"]->setText(new_description);
}

void ElementView::updateElementView(const QModelIndex& image_index, const QModelIndex& decription_index){
    qDebug()<<image_index;
    if(image_index.column() == 2){//QModelIndex& image_index, QModelIndex& decription_index
        imagePath = image_index;
        updateImage();
    }
    if(decription_index.column() == 3){
        description = decription_index;
        updateDescription();
    }
}

void ElementView::testSlot(const QModelIndex& index){
    qDebug()<<index;
}
