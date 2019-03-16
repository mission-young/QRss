#ifndef ADDRSSSOURCE_H
#define ADDRSSSOURCE_H

#include <QDialog>

namespace Ui {
class addRssSource;
}

class addRssSource : public QDialog
{
    Q_OBJECT

public:
    explicit addRssSource(QWidget *parent = nullptr);
    ~addRssSource();
    QString name();
    QString link();
    void clearcnt();
private slots:


private:
    Ui::addRssSource *ui;
};

#endif // ADDRSSSOURCE_H
