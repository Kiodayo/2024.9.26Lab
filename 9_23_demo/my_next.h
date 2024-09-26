#ifndef MY_NEXT_H
#define MY_NEXT_H

#include <QWidget>

#include"page_3.h"
#include"page_4.h"

namespace Ui {
class my_next;
}

class my_next : public QWidget
{
    Q_OBJECT

public:
    explicit my_next(QWidget *parent = nullptr);
    ~my_next();

signals:
    void my_back();

    void my_back_send_num(QString str);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::my_next *ui;
    page_3 * page3;
    page_4 * page4;
};

#endif // MY_NEXT_H
