#ifndef NEWSMODEL_H
#define NEWSMODEL_H

#include <QObject>
#include <QStandardItemModel>
class newsModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit newsModel(QObject *parent = nullptr);
    void addItem(QString title,QString link);
    void creatHeadr();
signals:

public slots:
};

#endif // NEWSMODEL_H
