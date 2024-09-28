#ifndef BORDE_H
#define BORDE_H

#include <QWidget>

#include"fsmp_board/fsmpLed.h"
#include<fsmp_board/fsmpFan.h>
#include<fsmp_board/fsmpVibrator.h>
#include<fsmp_board/fsmpBeeper.h>
#include<fsmp_board/fsmpTempHum.h>

//MQTT Class
#include"qmqttclient.h"

//json
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>


//定时器
#include<QTimer>

#include"secondpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class borde; }
QT_END_NAMESPACE

class borde : public QWidget
{
    Q_OBJECT

public:
    borde(QWidget *parent = nullptr);
    ~borde();
    QMqttClient * client;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void timer_timeout();
    void connect_success();

    void recv_data_from_mqtt_server(QByteArray message,QMqttTopicName topic_name);

    void on_pushButton_6_clicked();

    void to_server(double i);

    void on_pushButton_7_clicked();

private:
    Ui::borde *ui;

    fsmpLeds * leds;
    fsmpFan * fan;
    fsmpVibrator * vibrator;
    fsmpBeeper * beeper;
    fsmpTempHum * temp_hum;
    QTimer * timer;

    QWidget* secondPage;




};
#endif // BORDE_H
