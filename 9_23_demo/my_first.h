#ifndef MY_FIRST_H
#define MY_FIRST_H

#include <QWidget>

#include<QDebug>

#include<QImage>
#include<QPixmap>
//网络请求管理工具
#include<QNetworkAccessManager>
//网络请求类
#include<QNetworkRequest>

#include<QNetworkReply>

//json
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>

#include<QBuffer>
#include<QByteArray>
#include<QJsonArray>

#include<QMessageBox>

#include"baidu_voice.h"

//摄像头类
#include<QCamera>
//摄像头取景类
#include<QCameraViewfinder>
//摄像头抓拍器类
#include<QCameraImageCapture>

#include "my_next.h"

QT_BEGIN_NAMESPACE
namespace Ui { class my_first; }
QT_END_NAMESPACE

class my_first : public QWidget
{
    Q_OBJECT

public:
    my_first(QWidget *parent = nullptr);
    ~my_first();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void get_my_next_num(QString str);

    void on_pushButton_3_clicked();

    void recv_data_from_imagecapture(int id,QImage image);

    void get_access_token(QString ak,QString sk);

    void recv_data_from_network(QNetworkReply * my_reply);

    void on_pushButton_4_pressed();

    void on_pushButton_4_released();

    void recv_data_from_baidu_voice(QString data);

private:
    Ui::my_first *ui;
    QCamera * my_camera;
    QCameraViewfinder * my_camera_viewfinder;
    QCameraImageCapture * my_camera_image_capture;

    my_next * next;

    QNetworkAccessManager * my_network_access_manager;

    QString access_token;

    baidu_voice * my_voice;


};
#endif // MY_FIRST_H
