#include "jsonioworker.h"

bool jsonIOworker::loadDataFromFile(PlantHierarhy* root){
    if(readFile() && root){
        parent=root;
        parseAndPlaceData();
        return true;
    }
    return false;
}

bool jsonIOworker::readFile(){
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)){
        if(parent_window)
            QMessageBox::critical(parent_window, "Невозможно открыть файл", "Не получается открыть файл по указанному вами пути.");
        return false;
    }

    jDoc = QJsonDocument::fromJson(file.readAll());
    return true;
}

void jsonIOworker::parseArray(const QJsonArray& jsonArray, const QModelIndex &parent_index){
    int row = 0;
    QModelIndex index;
    QVector<QString> objects{"hier_name", "name", "description", "image"};

    for(const auto& value: jsonArray){
        if (value.isObject()){
            QJsonObject obj = value.toObject();
            parent->insertRows(parent->rowCount(parent_index), 1, parent_index);            //append a row to parent
            int column=0;
            for(const auto & it: objects){
                index = parent->addIndex(row, column, parent_index);
                if(!parent->setData(index, obj[it].toString())){
                    QMessageBox::warning(parent_window, "Невозможно считать содержимое файла", "Файл формата JSon содержит ошибку.");
                    return;
                }
                ++column;
            }
            if(obj["childs"].isArray())
                parseArray(obj["childs"].toArray(), parent->addIndex(row, 0, parent_index));
            ++row;
        }
    }
}

void jsonIOworker::parseAndPlaceData(){
    if (jDoc.isObject()){
        QJsonObject json = jDoc.object();
        QJsonArray jsonArray;

        if(json["childs"].isArray()){
            jsonArray = json["childs"].toArray();
            parseArray(jsonArray, parent->getRootIndex());
        }
    }
}

QJsonObject jsonIOworker::addChildrenIntoArray(HierItem* vertex){
    QJsonArray array;
    QJsonObject obj;
    int i = 0;                                                                  //fields index
    QQueue<HierItem*> children;

    for(int j = 0; j < (vertex->childCount()); ++j)
        children.append(vertex->child(j));                                      //add children to queue

    while(!children.isEmpty()){
        array.append(
                    addChildrenIntoArray(children.dequeue())                    //get child element and add it into array
                                                );
    }
    if(vertex != parent->getRootItem()){
        for(const auto & it: {"hier_name", "name", "description", "image"})
            obj[it]=vertex->data(i++).toString();                               //fulfiil data fields
    }
    obj["childs"]=array;
    return obj;
}

bool jsonIOworker::write(){
    QFile file(path+"EXPERIMENTAL");

    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(parent_window, "Невозможно открыть файл", "Не получается открыть файл по указанному вами пути.");
        return false;
    }

    file.write(QJsonDocument(addChildrenIntoArray(parent->getRootItem())).toJson());
    return false;
}
