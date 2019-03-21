#include "newsmodel.h"
#include <QDebug>
newsModel::newsModel(QObject *parent) : QStandardItemModel(parent)
{

}

void newsModel::addItem(QString title,QString link)
{
    QList<QStandardItem*> list;
    QStandardItem *star = new QStandardItem(QIcon(":/images/starOff.png"),"");
    star->setData(false,Qt::UserRole+1);
    QStandardItem *titleitem=new QStandardItem(title);
    titleitem->setData(link);
    list<<star<<titleitem;
    appendRow(list);
}

void newsModel::creatHeadr()
{
    setHorizontalHeaderItem(0,new QStandardItem(QIcon(":/images/starOff.png"),""));
    setHorizontalHeaderItem(1,new QStandardItem("文章标题"));
}

void newsModel::starOnOff(const QModelIndex &index)
{

    //调用setItem会删除原先的item,造成原属性丢失。
    //void QStandardItemModel::setItem(int row, int column, QStandardItem *item)
    //Sets the item for the given row and column to item.
    //The model takes ownership of the item. If necessary, the row count and column count are
    //increased to fit the item. The previous item at the given location (if there was one) is deleted.
    if(this->data(index,Qt::UserRole+1).toBool()){
        //this->setItem(index.row(),index.column(),new QStandardItem(QIcon(":/images/starOff.png"),""));
        this->setData(index,false,Qt::UserRole+1);
        this->setData(index,QIcon(":/images/starOff.png"),Qt::DecorationRole);
    }else{
        //this->setItem(index.row(),index.column(),new QStandardItem(QIcon(":/images/starOn.png"),""));
        this->setData(index,true,Qt::UserRole+1);
        this->setData(index,QIcon(":/images/starOn.png"),Qt::DecorationRole);
    }
}

