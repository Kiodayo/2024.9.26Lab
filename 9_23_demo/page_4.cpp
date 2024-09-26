#include "page_4.h"
#include "ui_page_4.h"

page_4::page_4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_4)
{
    ui->setupUi(this);

}

page_4::~page_4()
{
    delete ui;
}

void page_4::on_pushButton_clicked()
{
    this->hide();
    emit this->my_turn_3();
}


void page_4::on_pushButton_2_clicked()
{
    this->hide();
    emit this->my_turn_back();
}

