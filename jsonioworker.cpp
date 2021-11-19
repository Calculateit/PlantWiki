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

    if (!file.open(QIODevice::ReadOnly)) {
        if(parent_window)
            QMessageBox::warning(parent_window, "Невозможно открыть файл", "Не получается открыть файл по указанному вами пути.");
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
            //qDebug()<<"rowCount="<<parent->rowCount(parent_index);
            parent->insertRows(parent->rowCount(parent_index), 1, parent_index);//append a row to parent
            int column=0;
            //QModelIndex parent_index_for_child = parent->addIndex(row, 0, parent_index);
            for(const auto & it: objects){
                //index = parent->index(row, column, parent_index);//получаем индекс ребёнка не работает, тк получаем индекс ребенка, которого ещё не создали
                index = parent->addIndex(row, column, parent_index);
                if(!parent->setData(index, obj[it].toString())){
                    //qDebug()<<"Data set!";
                    QMessageBox::warning(parent_window, "Невозможно считать содержимое файла", "Файл формата JSon содержит ошибку.");
                    return;
                }
                //qDebug()<<"row="<<row<<" column="<<column<<" "<<index<<", "<<obj[it].toString()<<" parent="<<parent_index<<"\n";
                ++column;
            }
            //qDebug()<<"children: ";
            if(obj["childs"].isArray())
                parseArray(obj["childs"].toArray(), parent->addIndex(row, 0, parent_index));
            //qDebug()<<"END children.\n";
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

bool jsonIOworker::write(){
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(parent_window, "Невозможно открыть файл", "Не получается открыть файл по указанному вами пути.");
        return false;
    }
    //file.write(QJsonDocument(Object).toJson());
    return false;
}
