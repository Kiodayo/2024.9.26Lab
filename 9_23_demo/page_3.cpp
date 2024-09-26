#include "page_3.h"
#include "ui_page_3.h"

page_3::page_3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_3)
{
    ui->setupUi(this);


}
page_3::~page_3()
{
    delete ui;
}

void page_3::on_pushButton_clicked()
{
    this->hide();
    emit this->my_turn_4();
}


void page_3::on_pushButton_2_clicked()
{
    this->hide();
    emit this->my_turn_next();
}

