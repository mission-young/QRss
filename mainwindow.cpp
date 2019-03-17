#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopServices>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    feedmodel=new FeedModel(this);
    ui->tvRes->setModel(feedmodel);
    feedmodel->creatHeader();
    ui->tvRes->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    int width=ui->tvRes->columnWidth(0)+ui->tvRes->columnWidth(1);
    ui->tvRes->setColumnWidth(0,int(0.4*width));


    newsmodel=new newsModel(this);
    ui->tvNewsList->setModel(newsmodel);
    newsmodel->creatHeadr();
    ui->tvNewsList->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    manager=new QNetworkAccessManager(this);

    webview=new QWebEngineView(this);
    ui->weblayout->addWidget(webview);

    JsonParser::load("feedmodel.json",feedmodel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    if(rsswin.exec()==QDialog::Accepted){
        feedmodel->AddItem(rsswin.name(),rsswin.link());
        rsswin.clearcnt();
        JsonParser::save("feedmodel.json",feedmodel);
    }

}


void MainWindow::anarss()
{

    QByteArray cnt=reply->readAll();
    QXmlStreamReader xmlstream;
    xmlstream.addData(cnt);
    QString titleStr,linkStr,currentTag;
    while (!xmlstream.atEnd()) {
        xmlstream.readNext();
        if(xmlstream.isStartElement()){
            if(xmlstream.name()=="item"){
                titleStr.clear();
                linkStr.clear();
            }
            currentTag=xmlstream.name().toString();
        }else if(xmlstream.isEndElement()){
            if(xmlstream.name()=="item"){
                newsmodel->addItem(titleStr,linkStr);
                titleStr.clear();
                linkStr.clear();
            }
        }else if(xmlstream.isCharacters()&&!xmlstream.isWhitespace()){
            if(currentTag == "title"){
                titleStr += xmlstream.text().toString();
            }else if(currentTag == "link"){
                linkStr += xmlstream.text().toString();
            }
        }
    }

}

void MainWindow::error(QNetworkReply::NetworkError err)
{
    qDebug()<<"error";
    Q_UNUSED(err);
}

void MainWindow::on_tvNewsList_clicked(const QModelIndex &index)
{
    webview->load(QUrl(newsmodel->data(index,Qt::UserRole+1).toString()));
    webview->showNormal();
}

void MainWindow::on_btnDelete_clicked()
{   ui->tvRes->selectionModel()->currentIndex().row();
    int row=ui->tvRes->currentIndex().row();
    feedmodel->removeRow(row);
    JsonParser::save("feedmodel.json",feedmodel);
}

void MainWindow::on_tvRes_doubleClicked(const QModelIndex &index)
{
    QNetworkRequest request;
    request.setUrl(QUrl(feedmodel->item(index.row(),1)->data().toString()));
    request.setRawHeader("User-Agent","MyOwnBrowser 1.0");

    reply=manager->get(request);
    connect(reply,SIGNAL(readyRead()),this,SLOT(anarss()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
            this,SLOT(error(QNetworkReply::NetworkError)));
}

void MainWindow::on_pushButton_clicked()
{
    newsmodel->removeRows(0,newsmodel->rowCount());
}
