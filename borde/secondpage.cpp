#include "secondpage.h"
#include "ui_secondpage.h"

SecondPage::SecondPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondPage)
{
    ui->setupUi(this);
    //fan = new fsmpFan;
    light = new fsmpLight;
    timer = new QTimer;
    leds= new fsmpLeds;
    ledTimer = new QTimer;
    tempHumTimer = new QTimer;
    temp_hum = new fsmpTempHum;


    //配置
    //fan->setSpeed(255);//转速

    connect(timer,&QTimer::timeout,this,&SecondPage::timer_timeout);
    connect(ledTimer, &QTimer::timeout, this, &SecondPage::updateLEDS);
    connect(tempHumTimer, &QTimer::timeout, this, &SecondPage::updateTempHum);
}

SecondPage::~SecondPage()
{
    delete ui;
}
void SecondPage::timer_timeout(){
    double intensity = light->getValue();

    ui->label_2->setText(QString("Light Intensity:%1").arg(intensity));
}
void SecondPage::on_pushButton_clicked()
{
    this->hide();
}


//void SecondPage::on_pushButton_2_clicked()
//{
//    static int flag = 0;
//    if(flag == 0){
//        fan->start();
//        flag = 1;
//        ui->pushButton_2->setText("风扇关闭");
//    }else{
//        fan->stop();
//        flag = 0;
//        ui->pushButton_2->setText("风扇开启");
//    }
//}


void SecondPage::on_pushButton_3_clicked()
{
    timer->start(1000);
}


void SecondPage::updateLEDS()
{
    double intensity = light->getValue(); // 获取当前亮度值
    if (intensity < 20) {
        leds->on(fsmpLeds::LED1);
        leds->on(fsmpLeds::LED2);
    } else {
        leds->off(fsmpLeds::LED1);
        leds->off(fsmpLeds::LED2);
    }
}

void SecondPage::updateTempHum()
{
    //double temperature(void)                    提取温度
    //double humidity(void)                       提取湿度
    double tem = temp_hum->temperature();
    double humid = temp_hum->humidity();

    ui->label_3->setText(QString("温度:%1").arg(tem));
    ui->label_4->setText(QString("湿度:%1").arg(humid));
}
void SecondPage::on_pushButton_4_clicked()
{
    static bool isTorchOn = false; // 手电筒状态

    isTorchOn = !isTorchOn; // 切换状态
    if (isTorchOn) {
        ui->pushButton_4->setText("夜间手电筒关闭");
        ledTimer->start(1000); // 每秒检查一次
    } else {
        ui->pushButton_4->setText("夜间手电筒开启");
        leds->off(fsmpLeds::LED1); // 关闭 LED
        leds->off(fsmpLeds::LED2);
        ledTimer->stop(); // 停止定时器
    }
}


void SecondPage::on_pushButton_5_clicked()
{
    tempHumTimer->start();


}

