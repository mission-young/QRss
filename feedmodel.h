#ifndef FEEDMODEL_H
#define FEEDMODEL_H

#include <QObject>
#include <QStandardItemModel>
class FeedModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit FeedModel(QObject *parent = nullptr);
    void creatHeader();
    void AddItem(QString name,QString link);
signals:

public slots:
};

#endif // FEEDMODEL_H
