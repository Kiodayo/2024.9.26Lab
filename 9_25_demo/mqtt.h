#ifndef MQTT_H
#define MQTT_H

#include <QMainWindow>

#include"qmqttclient.h"
#include<QMessageBox>
#include<qmqtttopicname.h>
#include<qmqtttopicfilter.h>
#include<QByteArray>

//json
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>

#include<QBuffer>
#include<QByteArray>
#include<QJsonArray>


QT_BEGIN_NAMESPACE
namespace Ui { class mqtt; }
QT_END_NAMESPACE

class mqtt : public QMainWindow
{
    Q_OBJECT

public:
    mqtt(QWidget *parent = nullptr);
    ~mqtt();

private slots:
    void on_pushButton_clicked();
    void connect_success();

    void on_pushButton_2_clicked();
    void recv_data_from_mqtt_server(QByteArray message,QMqttTopicName topic_name);

private:
    Ui::mqtt *ui;

   QMqttClient * my_mqtt_client;
};
#endif // MQTT_H
