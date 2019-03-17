#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addrsssource.h"
#include "feedmodel.h"
#include "newsmodel.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QXmlStreamReader>
#include <QWebEngineView>
#include "jsonparser.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void anarss();
    void error(QNetworkReply::NetworkError err);

    void on_tvNewsList_clicked(const QModelIndex &index);
    void on_btnDelete_clicked();

    void on_tvRes_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    QWebEngineView *webview;
private:
    Ui::MainWindow *ui;
    FeedModel *feedmodel;
    addRssSource rsswin;
    newsModel *newsmodel;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
};

#endif // MAINWINDOW_H
