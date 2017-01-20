#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void connectToNet();
    void disconnectToNet();
    ~MainWindow();
public slots:
    void replyFinished(QNetworkReply *reply);
    void showFlow(QNetworkReply *reply);
private slots:
    void on_login_clicked();
    void on_logout_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QNetworkAccessManager *manager;
};

#endif // MAINWINDOW_H
