#include "widget2.h"
#include "widget.h"
#include "ui_widget2.h"
#include "qglobal.h"
#include "cmd_queue.h"
#include "process_fun.h"
#include "hmi_driver.h"
Widget2::Widget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget2)
{
    ui->setupUi(this);
}

Widget2::~Widget2()
{
    delete ui;
}

void Widget2::on_MenuBt1_clicked()
{
    if(Widget::flag == 0)
    {
        Widget *first = new Widget;
        first->setGeometry(this->geometry());
        first->show();
    }
    this->close();
}

void Widget2::on_MenuBt2_clicked()
{
    uint8_t data[5] = {1,2,3,4,5};
   GraphChannelDataAdd_forAndroid( 0, 0, data, 5);
}
