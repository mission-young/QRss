#include "newsmodel.h"

newsModel::newsModel(QObject *parent) : QStandardItemModel(parent)
{

}

void newsModel::addItem(QString title,QString link)
{
    QStandardItem *titleitem=new QStandardItem(title);
    titleitem->setData(link);
    appendRow(titleitem);
}

void newsModel::creatHeadr()
{
    setHorizontalHeaderItem(0,new QStandardItem("文章标题"));
    // git test
}

