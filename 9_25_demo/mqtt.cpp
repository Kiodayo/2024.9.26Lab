#include "mqtt.h"
#include "ui_mqtt.h"

mqtt::mqtt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mqtt)
{
    ui->setupUi(this);

    my_mqtt_client = new QMqttClient;

    connect(my_mqtt_client,&QMqttClient::connected,this,&mqtt::connect_success);

    connect(my_mqtt_client,&QMqttClient::messageReceived,this,&mqtt::recv_data_from_mqtt_server);
}

mqtt::~mqtt()
{
    delete ui;

}
void mqtt::connect_success()
{
    qDebug()<<"connect success";
    QMessageBox::about(this,"","connect success");

    //当连接完成才进行订阅动作
    my_mqtt_client->subscribe(QMqttTopicFilter("1727170420157/AIOTSIM2APP"));

}

void mqtt::recv_data_from_mqtt_server(QByteArray message,QMqttTopicName topic_name)
{
    qDebug()<<topic_name;
    qDebug()<<message;

    //json解析
    QJsonDocument doc = QJsonDocument::fromJson(message);
    qDebug()<<doc;
    if(doc.isObject()){
        QJsonObject obj = doc.object();
        qDebug()<<obj;
        if(obj.contains("hum")){
            QJsonValue val = obj.value("hum");
            qDebug()<<val;
        }
    }
}


void mqtt::on_pushButton_clicked()
{
    QString ip =  ui->lineEdit->text();
    QString port = ui->lineEdit_2->text();

    //关联ip地址和端口号
    my_mqtt_client->setHostname(ip);
    my_mqtt_client->setPort(port.toInt());
    my_mqtt_client->connectToHost();
    qDebug()<<"connet...";
    int port_i = port.toInt();
    qDebug()<<port_i;
    qDebug()<<ip;
}


void mqtt::on_pushButton_2_clicked()
{
    static int flag = 0;
    if(flag == 0){
    QString message = "{\"doorLock\":true,\"id\":0}";
    //发布--mqtt服务器发送开门信息
    my_mqtt_client->publish(QMqttTopicName("1727170420157/APP2AIOTSIM"),message.toLatin1());
    ui->pushButton_2->setText("关门");
    flag = 1;
    }else{
        QString message = "{\"doorLock\":false,\"id\":0}";
        //发布--mqtt服务器发送开门信息
        my_mqtt_client->publish(QMqttTopicName("1727170420157/APP2AIOTSIM"),message.toLatin1());
        ui->pushButton_2->setText("开门");
        flag = 0;
    }


}
