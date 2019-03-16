#include "feedmodel.h"

FeedModel::FeedModel(QObject *parent) : QStandardItemModel(parent)
{

}

void FeedModel::creatHeader()
{
    setHorizontalHeaderItem(0,new QStandardItem("名称"));
    setHorizontalHeaderItem(1,new QStandardItem("链接"));
}

void FeedModel::AddItem(QString name, QString link)
{
    QList<QStandardItem*> list;
    QStandardItem *nameitem = new QStandardItem(name);
    nameitem->setData(name);
    QStandardItem *linkitem = new QStandardItem(link);
    linkitem->setData(link);
    list<<nameitem<<linkitem;
    appendRow(list);
}
