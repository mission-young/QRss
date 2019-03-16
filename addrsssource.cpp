#include "addrsssource.h"
#include "ui_addrsssource.h"

addRssSource::addRssSource(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRssSource)
{
    ui->setupUi(this);
}

addRssSource::~addRssSource()
{
    delete ui;
}

QString addRssSource::name()
{
    return ui->lename->text();
}

QString addRssSource::link()
{
    return ui->lelink->text();
}

void addRssSource::clearcnt()
{
    ui->lename->clear();
    ui->lelink->clear();
    ui->lename->setFocus();
}


