#include "my_next.h"
#include "ui_my_next.h"

my_next::my_next(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::my_next)
{
    ui->setupUi(this);

    page3 = new page_3;
    page4 = new page_4;

    connect(page3,&page_3::my_turn_4,page4,&page_4::show);
    connect(page4,&page_4::my_turn_3,page3,&page_4::show);
    connect(page3,&page_3::my_turn_next,this,&my_next::show);
    connect(page4,&page_4::my_turn_back,this,&my_next::show);
}

my_next::~my_next()
{
    delete ui;
}

void my_next::on_pushButton_clicked()
{
    //当前界面隐藏
    this->hide();
    //触发返回信号
    emit this->my_back();
}


void my_next::on_pushButton_2_clicked()
{
    page3->show();
}


void my_next::on_pushButton_3_clicked()
{
    page4->show();
}


void my_next::on_pushButton_4_clicked()
{
    this->hide();
    QString str = ui->lineEdit->text();
    emit this->my_back_send_num(str);
}

