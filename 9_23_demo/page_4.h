#ifndef PAGE_4_H
#define PAGE_4_H

#include <QWidget>

namespace Ui {
class page_4;
}

class page_4 : public QWidget
{
    Q_OBJECT

public:
    explicit page_4(QWidget *parent = nullptr);
    ~page_4();

signals:
    void my_turn_3();
    void my_turn_back();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::page_4 *ui;
};

#endif // PAGE_4_H
