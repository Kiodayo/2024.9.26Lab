#ifndef BAIDU_VOICE_H
#define BAIDU_VOICE_H

#include <QObject>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QFile>
#include <QFileDialog>
#include <QBuffer>
#include <QList>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <QMessageBox>

class baidu_voice : public QObject
{
    Q_OBJECT
public:
    explicit baidu_voice(QObject *parent = nullptr);

    baidu_voice(QString,QString);

signals:
    void readyresult(QString);
public slots:
    void start();

    void stop();

private slots:
    void get_access_token(QString,QString);

    void recv_data_from_network(QNetworkReply *);

private:
    QString access_token;
    QNetworkAccessManager * access_manager;
    QList <QAudioDeviceInfo> audios;
    QAudioInput * audio_input;
    QBuffer * my_buffer;
};

#endif // BAIDU_VOICE_H
