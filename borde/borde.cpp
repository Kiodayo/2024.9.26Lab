#include "borde.h"
#include "ui_borde.h"
#include"qmqttclient.h"

borde::borde(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::borde)
{
    ui->setupUi(this);

    leds = new fsmpLeds;
    fan = new fsmpFan;
    vibrator = new fsmpVibrator;
    beeper = new fsmpBeeper;
    temp_hum = new fsmpTempHum;

    timer = new QTimer;

    client = new QMqttClient;
    //配置
    fan->setSpeed(255);//转速
    vibrator->setParameter();
    beeper->setRate();

    //配置mqttclient
    client->setHostname("mqtt.yyzlab.com.cn");
    client->setPort(1883);

    connect(timer,&QTimer::timeout,this,&borde::timer_timeout);
    connect(client,&QMqttClient::connected,this,&borde::connect_success);

    connect(client,&QMqttClient::messageReceived,this,&borde::recv_data_from_mqtt_server);

    //连接元宇宙平台
    client->connectToHost();

}

borde::~borde()
{
    delete ui;
}

void borde::connect_success(){

    //连接成功
    qDebug()<<"connect success";

    //硬件订阅 （发布号）
    client->subscribe(QMqttTopicFilter("1727168812506/AIOTSIM2Device"));
}

void borde::recv_data_from_mqtt_server(QByteArray message,QMqttTopicName topic_name){

    QJsonDocument doc = QJsonDocument::fromJson(message);
    qDebug()<<message;
    if(doc.isObject()){
        QJsonObject obj = doc.object();
        if(obj.contains("doorLock")){
            QJsonValue val = obj.value("doorLock");
            qDebug()<<val;

            bool on = val.toBool();
            if(on){
                vibrator->start();
            }else{
                vibrator->stop();
            }
        }
    }
}

void borde::timer_timeout(){
    double tem = temp_hum->temperature();
    double hum = temp_hum->humidity();

    ui->label->setText(QString("温度:%1").arg(tem));
    ui->label_2->setText(QString("湿度:%1").arg(hum));
}


void borde::on_pushButton_clicked()
{
    static int flag = 0;
    if(flag == 0){
        fan->start();
        flag = 1;
        ui->pushButton->setText("风扇关闭");
    }else{
        fan->stop();
        flag = 0;
        ui->pushButton->setText("风扇开启");
    }
}


void borde::on_pushButton_2_clicked()
{
    static int flag = 0;
    if(flag == 0){
        beeper->start();
        flag = 1;
        ui->pushButton_2->setText("蜂鸣器关闭");
    }else{
        beeper->stop();
        flag = 0;
        ui->pushButton_2->setText("蜂鸣器开启");
    }
}


void borde::on_pushButton_3_clicked()
{
    static int flag = 0;
    if(flag == 0){
        vibrator->start();
        flag = 1;
        ui->pushButton_3->setText("马达关闭");
    }else{
        vibrator->stop();
        flag = 0;
        ui->pushButton_3->setText("马达开启");
    }
}


void borde::on_pushButton_4_clicked()
{
    static int flag = 0;
    if(flag == 0){
        leds->on(fsmpLeds::LED1);
        leds->on(fsmpLeds::LED2);
        flag = 1;
        ui->pushButton_4->setText("灯光关闭");
    }else{
        leds->off(fsmpLeds::LED1);
        leds->off(fsmpLeds::LED2);
        flag = 0;
        ui->pushButton_4->setText("灯光开启");
    }
}


void borde::on_pushButton_5_clicked()
{
  timer->start(1000);

}

