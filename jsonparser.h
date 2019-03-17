#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItem>
#include <QStandardItemModel>

class JsonParser
{
public:
    JsonParser();
    static bool load(QString fileName,QStandardItemModel *model);
    static bool save(QString fileName,QStandardItemModel *model);
};

#endif // JSONPARSER_H
