#include "elementview.h"

ElementView::ElementView(QAbstractItemModel& model, QLabel* image_label, QLabel* description_label)
    : model(model)
{
    labels.insert("image", image_label);
    labels.insert("description", description_label);
}

void ElementView::updateImage(){
    QString path = imagePath.data().toString();
    QPixmap pic(path), adaptedPic;
    if(!pic.isNull()){
        if(pic.height() > constants::ELEMENT_IMAGE_HEIGHT){
            adaptedPic = pic.scaledToHeight(constants::ELEMENT_IMAGE_HEIGHT);
        }
        else
            adaptedPic = pic;
        labels["image"]->setPixmap(adaptedPic);
    }
}

void ElementView::updateDescription(){
    QString new_description = description.data().toString();
    labels["description"]->setText(new_description);
}

void ElementView::updateElementView(const QModelIndex& image_index, const QModelIndex& description_index){

    if(description_index.column() == constants::DESCRIPTION_COLUMN_INDEX){
        description = description_index;
        updateDescription();
    }
    if(image_index.column()  == constants::IMAGE_COLUMN_INDEX){
        imagePath = image_index;
        updateImage();
    }
}

void ElementView::setNewImage(const QString& newPath){
    model.setData(imagePath, newPath);
    updateImage();
}

void ElementView::setNewDescription(const QString& newDescription){
    model.setData(description, newDescription);
    updateDescription();
}
