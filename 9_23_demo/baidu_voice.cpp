#include "baidu_voice.h"

baidu_voice::baidu_voice(QObject *parent) : QObject(parent)
{

}

baidu_voice::baidu_voice(QString api_key, QString secret_key)
{
    access_manager = new QNetworkAccessManager;
    connect(access_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(recv_data_from_network(QNetworkReply*)));
    //准备语音输入设备
    audios = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    //检测是否存在设备
    if(audios.isEmpty()){
        qDebug()<<"没有声音输入设备";
        //QMessageBox::warning(this,"提示","声音设备打开有误");
    }else{
        QAudioFormat format;
        format.setSampleRate(16000);//采样频率
        format.setChannelCount(1);//采样声道
        format.setSampleSize(16);//采样深度
        format.setSampleType(QAudioFormat::SignedInt);//采样数据格式
        format.setByteOrder(QAudioFormat::LittleEndian);//小端字节序
        format.setCodec("audio/pcm");//采样格式
        audio_input = new QAudioInput(audios.at(0),format);
    }

    get_access_token(api_key,secret_key);


}

void baidu_voice::get_access_token(QString api,QString secret)
{
    QString url = QString("http://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&").arg(api,secret);
    QNetworkRequest my_request(url);

    access_manager->get(my_request);
}

void baidu_voice::recv_data_from_network(QNetworkReply * my_reply)
{
    QByteArray byte_array = my_reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(byte_array);
    QJsonObject obj = doc.object();
    if(obj.contains("access_token")){
        QJsonValue val = obj.value("access_token");
        access_token = val.toString();
        qDebug()<<access_token;
    }else if(obj.contains("result")){
        QJsonValue val = obj.value("result");
        if(val.isArray()){
            QJsonArray array = val.toArray();
            QString str = array.at(0).toString();
            qDebug()<<str;
            emit this->readyresult(str);
        }
    }
}

void baidu_voice::start()
{
    my_buffer = new QBuffer;
    my_buffer->open(QIODevice::ReadWrite);

    audio_input->start(my_buffer);
}

void baidu_voice::stop()
{
    audio_input->stop();
    QByteArray array = my_buffer->data();
    my_buffer->close();

    QJsonObject obj;
    obj.insert("format","pcm");//采样格式
    obj.insert("rate",16000);//采样频率
    obj.insert("channel",1);//采样声道
    obj.insert("cuid","baidu_workshop");
    obj.insert("token",access_token);//鉴权编码
    obj.insert("dev_pic",1537);//1837四川话
    obj.insert("speech",QString(array.toBase64()));//语音数据
    obj.insert("len",array.size());//语音长度

    //创建网络请求
    QString url = QString("http://vop.baidu.com/server_api");
    QNetworkRequest my_request(url);
    my_request.setHeader(QNetworkRequest::ContentTypeHeader,"Content-Type:application/json");
    //发起网络请求
    access_manager->post(my_request,QJsonDocument(obj).toJson());
}
