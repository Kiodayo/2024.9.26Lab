#include "my_first.h"
#include "ui_my_first.h"


//构造函数，界面创建时调用
my_first::my_first(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::my_first)
{
    ui->setupUi(this);

    //
    QString api_key = "Sf0EX1ZgZ9LtpuinqhjhjHjR";
    QString secret_key = "hRJ9z0tHaAHNCLkVNMnwCSVl4cLhxuuB";

    QString api_key_voice = "";
    QString secret_key_voice = "";

    //创建摄像对象
    my_camera = new QCamera;
    my_camera_viewfinder = new QCameraViewfinder(ui->label);
    //抓拍器对象
    my_camera_image_capture = new QCameraImageCapture(my_camera);
    //创建界面对象
    next = new my_next;

    //配置
    my_camera->setViewfinder(my_camera_viewfinder);
    my_camera_viewfinder->setMinimumSize(ui->label->size());
    //配置抓拍器相关
    my_camera->setCaptureMode(QCamera::CaptureStillImage);
    my_camera_image_capture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);


    my_network_access_manager = new QNetworkAccessManager;


    //
    my_voice = new baidu_voice(api_key_voice,secret_key_voice);

    //关联信号与槽，谁产生什么信号由谁的方法进行相应
    connect(next,&my_next::my_back,this,&my_first::show);
    connect(next,&my_next::my_back_send_num,this,&my_first::get_my_next_num);

    connect(my_camera_image_capture,&QCameraImageCapture::imageCaptured,this,&my_first::recv_data_from_imagecapture);

    connect(my_network_access_manager,&QNetworkAccessManager::finished,this,&my_first::recv_data_from_network);
    connect(my_voice,&baidu_voice::readyresult,this,&my_first::recv_data_from_baidu_voice);

    get_access_token(api_key,secret_key);
}


//析构函数，界面退出时调用
my_first::~my_first()
{
    delete ui;
}

 void my_first::get_my_next_num(QString str)
 {
     this->show();
     ui->lineEdit_2->setText(str);
 }

 //抓拍到图像后封装网络请求包实现人脸识别
 void my_first::recv_data_from_imagecapture(int id,QImage image){
//     qDebug()<<id;
//     //qimage没办法直接显示在label标签上，只能用qpixmap转换
//     QPixmap pixmap = QPixmap::fromImage(image);
//     ui->label_2->setPixmap(pixmap);

     QByteArray byte_array;

     QBuffer buffer(&byte_array);
     buffer.open(QIODevice::ReadWrite);
     image.save(&buffer,"jpeg");
     buffer.close();

    QString url =QString("https://aip.baidubce.com/rest/2.0/face/v3/search?access_token=%1").arg(access_token);
    QNetworkRequest my_request(url);
    //设置请求头
    my_request.setHeader(QNetworkRequest::ContentTypeHeader,"");
    //封装请求body
    QJsonObject obj;
    obj.insert("image",QString(byte_array.toBase64()));
    obj.insert("image_type",QString("BASE64"));
    obj.insert("group_id_list",QString("group"));
    //发起网络请求
    my_network_access_manager->post(my_request,QJsonDocument(obj).toJson());



 }


 void my_first::get_access_token(QString ak,QString sk){

     //封装网络请求包

//     QString url = QString("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=Sf0EX1ZgZ9LtpuinqhjhjHjR&client_secret=hRJ9z0tHaAHNCLkVNMnwCSVl4cLhxuuB").arg(ak,sk);
     QString url = QString("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2").arg(ak,sk);
     QNetworkRequest my_request(url);
     //网络请求
     my_network_access_manager->get(my_request);
 }

 void my_first::recv_data_from_network(QNetworkReply * my_reply){

     QByteArray byte_array =  my_reply->readAll();
     qDebug()<<byte_array;
     //json解析
     QJsonDocument doc = QJsonDocument::fromJson(byte_array);
     qDebug()<<doc;
     if(doc.isObject()){
         //
         QJsonObject obj = doc.object();
         qDebug()<<"-------------------";
         qDebug()<<obj;
         if(obj.contains("access_token")){
             QJsonValue val =obj.value("access_token");
             qDebug()<<val;
             access_token = val.toString();

         }else if(obj.contains("error_msg")){
             QJsonValue val = obj.value("error_msg");
             QString str = val.toString();
             if(str == "SUCCESS"){
                 if(obj.contains("result")){
                                 val = obj.value("result");
                                 obj = val.toObject();
                                 if(obj.contains("user_list")){
                                     val = obj.value("user_list");
                                     qDebug()<<val;

                                     QJsonArray array = val.toArray();
                                     array.at(0);
                                     qDebug()<<array.at(0);
                                     obj = array.at(0).toObject();
                                     if(obj.contains("score")){
                                         val = obj.value("score");
                                         qDebug()<<val;
                                         double score = val.toDouble();
                                         if(score > 80.0){
                                             QMessageBox::about(this,"标题","识别成功");
                                         }
                                     }

                                 }
             }

             }else{
                 QMessageBox::warning(this,"标题","识别失败");
             }
         }
     }

 }


void my_first::on_pushButton_clicked()
{
    static int flag = 0;
    qDebug()<<"按键1点击";
    //当按键1点击在行编辑器上设置一段文本内容
   if(flag == 0){
       my_camera->start();
    ui->lineEdit->setText("摄像头打开成功");
    ui->pushButton->setText("暂停摄像头");

    // ui->pushButton->setStyleSheet(); //设置样式表

    flag = 1;
   }else if(flag == 1){
       my_camera->stop();
    ui->pushButton->setText("开启摄像头");
    flag = 0;
   }
}


void my_first::on_pushButton_2_clicked()
{
    //当按键2点击读取行编辑器内容
   QString str = ui->lineEdit_2->text();
   qDebug()<<str;
   //下一个界面显示
   next->show();
   //隐藏当前界面
    this->hide();
}


void my_first::on_pushButton_3_clicked()
{
    //抓拍器拍摄图像
    my_camera_image_capture->capture();
}


void my_first::on_pushButton_4_pressed()
{
    //按键按下说话
    my_voice->start();

}


void my_first::on_pushButton_4_released()
{
    //按键松开识别
    my_voice->stop();
}

void my_first::recv_data_from_baidu_voice(QString data){

          if(data == "识别"){
              my_camera_image_capture->capture();
          }
}
