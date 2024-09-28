#ifndef SECONDPAGE_H
#define SECONDPAGE_H

#include <QWidget>

#include"fsmp_board/fsmpLed.h"
#include<fsmp_board/fsmpFan.h>
#include<fsmp_board/fsmpVibrator.h>
#include<fsmp_board/fsmpBeeper.h>
#include<fsmp_board/fsmpTempHum.h>
#include<fsmp_board/fsmpLight.h>

//MQTT Class
#include"qmqttclient.h"

//json
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>


//定时器
#include<QTimer>

namespace Ui {
class SecondPage;
}

class SecondPage : public QWidget
{
    Q_OBJECT

public:
    explicit SecondPage(QWidget *parent = nullptr);
    ~SecondPage();

private slots:
    void timer_timeout();
    void updateLEDS();
    void updateTempHum();
    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::SecondPage *ui;
//    fsmpFan * fan;
    fsmpLight* light;
    QTimer * timer;
    QTimer * ledTimer;
    QTimer * tempHumTimer;
    fsmpLeds * leds;
    fsmpTempHum * temp_hum;

};

#endif // SECONDPAGE_H
