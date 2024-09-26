#ifndef PAGE_3_H
#define PAGE_3_H

#include <QWidget>

namespace Ui {
class page_3;
}

class page_3 : public QWidget
{
    Q_OBJECT

public:
    explicit page_3(QWidget *parent = nullptr);
    ~page_3();

signals:
    void my_turn_4();
    void my_turn_next();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::page_3 *ui;
};

#endif // PAGE_3_H
