#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    ui->setupUi(this);
}

void MainWindow::connectToNet()
{
    manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QByteArray post_data;

    post_data.append("action=login&");
    post_data.append("username="+ui->username->text()+"&");
    post_data.append("password="+ui->password->text()+"&");
    //post_data.append("ac_id=1");
    //ac_id=1
    post_data.append("ajax=1");

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
    request.setUrl(QUrl("https://ipgw.neu.edu.cn/srun_portal_pc.php?"));

    connect(manager, &QNetworkAccessManager::finished, this, replyFinished);
    manager->post(request,post_data);
}

void MainWindow::disconnectToNet()
{
    manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QByteArray post_data;

    post_data.append("action=logout&");
    post_data.append("username="+ui->username->text()+"&");
    post_data.append("password="+ui->password->text()+"&");
    //post_data.append("ac_id=1");
    post_data.append("ajax=1");

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
    request.setUrl(QUrl("https://ipgw.neu.edu.cn/srun_portal_pc.php?"));

    connect(manager, &QNetworkAccessManager::finished, this, replyFinished);
    manager->post(request,post_data);
}

void MainWindow::replyFinished(QNetworkReply *reply)
{

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray result = reply->readAll();
        qDebug() << QString(result);
        if(result.startsWith("login_ok"))
        {
            disconnect(manager, &QNetworkAccessManager::finished, this, replyFinished);
            QNetworkRequest request;
            QByteArray post_data;
            post_data.append("action=get_online_info");

            request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
            request.setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
            request.setUrl(QUrl("https://ipgw.neu.edu.cn/include/auth_action.php?"));

            manager->post(request,post_data);
            connect(manager, &QNetworkAccessManager::finished, this, showFlow);
        }
        else if(result.startsWith("E2620"))
        {
            ui->label->setText("<h3><font color='#EE3B3B'>You are already online.</font></h3>");
        }
        else if(result.startsWith("E2531"))
        {
            ui->label->setText("<h3><font color='#EE3B3B'>User not found.</font></h3>");
        }
        else if(result.startsWith("E2553"))
        {
            ui->label->setText("<h3><font color='#EE3B3B'>Password is error.</font></h3>");
        }
        else if(result.startsWith("\xE7\xBD"))
        {
            ui->label->setText(QString("<h3><font color='#EE3B3B'>The network has been disconnected!</font></h3>"));
        }
        else
        {
            ui->label->setText("<h3><font color='#EE3B3B'>Not Connected!</font></h3>");
        }
    }
}

void MainWindow::showFlow(QNetworkReply *reply)
{
    QByteArray result = reply->readAll();
    qDebug() << result;
    QStringList list = QString(result).split(",");
    QString Qflow = list[0];
    double flow = Qflow.toDouble()/(1000*1000);
    ui->label->setText(QString("<center><h3><font color='#EE3B3B'>The network has been connected</font></h3></center>\r\n"
                       "<center>Used Flow : %1M</center>"
                       "<center>Balance : "+list[2]+"yuan</center>").arg(flow));
}

void MainWindow::on_login_clicked()
{
    this->connectToNet();
}

void MainWindow::on_logout_clicked()
{
    this->disconnectToNet();
}

MainWindow::~MainWindow()
{
    delete ui;
}
