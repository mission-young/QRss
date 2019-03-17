#include "jsonparser.h"

JsonParser::JsonParser()
{

}

bool JsonParser::load(QString fileName, QStandardItemModel *model)
{
    QFile ipf(fileName);
    if(!ipf.open(QIODevice::ReadOnly)){
        qWarning("Couldn't open save file.");
        return false;
    }
    QByteArray indata=ipf.readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(indata);
    QJsonObject json=jdoc.object();
    if(model->rowCount()>0) model->removeRows(0,model->rowCount());
    const int rowCount=json["rowCount"].toInt();
    const int columnCount=json["columnCount"].toInt();
    QJsonArray data=json["data"].toArray();
    model->setRowCount(rowCount);
    model->setColumnCount(columnCount);
    for (int i = 0; i < rowCount; ++i) {
        QJsonArray row=data[i].toArray();
        for (int j = 0; j < columnCount; ++j) {
            QJsonArray column=row[j].toArray();
            model->setItem(i,j,new QStandardItem(column[0].toString()));
            model->item(i,j)->setData(column[1].toString(),Qt::UserRole+1);
            model->item(i,j)->setData(column[2].toInt(),Qt::TextAlignmentRole);
        }
    }
    return true;
}

bool JsonParser::save(QString fileName, QStandardItemModel *model)
{
    QFile opf(fileName);
    if(!opf.open(QIODevice::WriteOnly)){
        qWarning("Writing Failed!");
        return false;
    }
    QJsonObject json;
    json["rowCount"]=model->rowCount();
    json["columnCount"]=model->columnCount();
    QJsonArray data;
    for (int i = 0; i < model->rowCount(); ++i) {
        QJsonArray row;
        for (int j = 0; j < model->columnCount(); ++j) {
            QJsonArray column;
            column.append(QJsonValue(model->item(i,j)->text()));
            column.append(QJsonValue(model->item(i,j)->data(Qt::UserRole+1).toString()));
            column.append(QJsonValue(model->item(i,j)->data(Qt::TextAlignmentRole).toInt()));

            row.append(column);
        }
        data.append(row);
    }
    json["data"]=data;
    QJsonDocument jdoc(json);
    opf.write(jdoc.toJson());
    return true;
}
