#include "widget.h"
#include "widget2.h"
#include "ui_widget.h"
#include "QNetworkInterface"
#include "QString"
#include "qglobal.h"
#include "cmd_queue.h"
#include "process_fun.h"
#include "hmi_driver.h"



quint16 Widget::port;
int Widget::flag = 0;
QHostAddress Widget::address;
int Widget::net_flag = 0;
QTcpServer *Widget::tcpServer = new QTcpServer;
QTcpSocket *Widget::tcpSocket = new QTcpSocket;
//QLineSeries *Widget::line1 = new QLineSeries;
QLineSeries *Widget::line2 = new QLineSeries;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    line1 = new QLineSeries();

//    chart = new QChart();
    chart2 = new QChart();

    ui->lineEdit_IP->clear();



    QList<QString> strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
     //获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&ipAddressesList.at(i).toIPv4Address())
           {
               strIpAddress.append(ipAddressesList.at(i).toString());
              // break;
           }
     }


      //如果没有找到，则以本地IP地址为IP
     if(strIpAddress.isEmpty())strIpAddress.append(QHostAddress(QHostAddress::LocalHost).toString());
     ui->lineEdit_IP->addItems(strIpAddress);






    //设置坐标轴
//    chart->addSeries(line1);
//    chart->setTheme(QChart::ChartThemeQt);
    chart2->addSeries(line2);
    chart2->setTheme(QChart::ChartThemeQt);

//    line1->setName("频域波形");
    line2->setName("时域波形");
//    line1->setColor(Qt::blue);
    line2->setColor(Qt::red);
//    QValueAxis *axisX = new QValueAxis;
//    QValueAxis *axisY = new QValueAxis;

    QValueAxis *axisX2 = new QValueAxis;
    QValueAxis *axisY2 = new QValueAxis;

//    axisX->setRange(0,400);
//    axisY->setRange(0,255);
//    axisX->setGridLineVisible(true);
//    axisX->setGridLineColor(Qt::black);
//    axisX->setMinorTickCount(1);
//    axisX->setMinorGridLineColor(Qt::black);
//    axisX->setMinorGridLineVisible(true);
//    axisX->setLabelsVisible(false); //设置刻度是否显示
//    axisY->setGridLineVisible(true);
//    axisY->setGridLineColor(Qt::black);
//    axisY->setMinorTickCount(1);
//    axisY->setMinorGridLineColor(Qt::black);
//    axisY->setMinorGridLineVisible(true);
//    axisY->setLabelsVisible(false); //设置刻度是否显示

//    axisX->setLabelFormat("%.0f");
//    axisX->setLabelsAngle(45);
//    axisX->setLabelsColor(Qt::blue);
//    axisY->setLabelFormat("%.0f");
//    axisY->setLabelsAngle(45);
//    axisY->setLabelsColor(Qt::blue);

    axisX2->setLabelFormat("%.0f");
    axisX2->setLabelsAngle(45);
    axisX2->setLabelsColor(Qt::blue);
    axisY2->setLabelFormat("%.0f");
    axisY2->setLabelsAngle(45);
    axisY2->setLabelsColor(Qt::blue);


    axisX2->setRange(0,200);
    axisY2->setRange(0,255);
    axisX2->setGridLineVisible(true);
    axisX2->setGridLineColor(Qt::black);
    axisX2->setMinorTickCount(1);
    axisX2->setMinorGridLineColor(Qt::black);
    axisX2->setMinorGridLineVisible(true);
    axisX2->setLabelsVisible(false); //设置刻度是否显示
    axisY2->setGridLineVisible(true);
    axisY2->setGridLineColor(Qt::black);
    axisY2->setMinorTickCount(1);
    axisY2->setMinorGridLineColor(Qt::black);
    axisY2->setMinorGridLineVisible(true);
    axisY2->setLabelsVisible(false); //设置刻度是否显示

//    chart->addAxis(axisX,Qt::AlignBottom);
//    chart->addAxis(axisY,Qt::AlignLeft);
//    chart->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界全部为0
//    chart->setMargins(QMargins(0, 0, 0, 0));//设置内边界全部为0
//    chart->setBackgroundRoundness(0);//设置背景区域无圆角

    chart2->addAxis(axisX2,Qt::AlignBottom);
    chart2->addAxis(axisY2,Qt::AlignLeft);
    chart2->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界全部为0
    chart2->setMargins(QMargins(0, 0, 0, 0));//设置内边界全部为0
    chart2->setBackgroundRoundness(0);//设置背景区域无圆角

//    line1->attachAxis(axisX);
//    line1->attachAxis(axisY);

    line2->attachAxis(axisX2);
    line2->attachAxis(axisY2);

//    ui->widget->setChart(chart);
    ui->widget_2->setChart(chart2);
    ui->lineEdit_Port->setText(QString::number(port,10));
    flag = 1;


}

Widget::~Widget()
{
    delete ui;
}

bool isIpAddr(const QString &ip)
{
    QRegExp rx2("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    if(rx2.exactMatch(ip))
    {
        return true;
    }
    return false;
}

//void Widget::updatedata(float input)
//{
//    static int i=0;
//    static QVector<QPointF> data=line1->pointsVector();
//    if(input<0)input = 0;
//    if(input>255)input = 255;
//    if(i<512)
//    {
//        data.append(QPointF(i,input));
//        i++;
//        line1->replace(data);
//    }
//    else
//    {
//        QVector<QPointF> data2;
//        for(int j = 0;j<511;j++)
//        {
//            data2.append(QPointF(j,data.at(j+1).y()));
//        }
//        data2.append(QPointF(511,input));
//        data = data2;
//        line1->replace(data);
//    }

//}
void Widget::updatedata2(float input)
{
    static int i2=0;
    static QVector<QPointF> data0=line2->pointsVector();
    if(input<0)input = 0;
    if(input>255)input = 255;
    if(i2<1024)
    {
        data0.append(QPointF(i2,input));
        i2++;
        line2->replace(data0);
    }
    else
    {
        QVector<QPointF> data2;
        for(int j = 0;j<1023;j++)
        {
            data2.append(QPointF(j,data0.at(j+1).y()));
        }
        data2.append(QPointF(1023,input));
        data0 = data2;
        line2->replace(data0);
    }

}
void Widget::updatedata3(uint8_t* input,int index,Ui::Widget *dis)
{
    QByteArray qstr;
    int i = 0;
    for(i;i<sizeof(input);i++)
    {
        qstr.append(input[i]);
    }
    QString str = QString(qstr);
    qDebug()<<str;
    switch(index)
    {
        case 1:
        {
            dis->lineEdit->setText(str);
            break;
        }
        case 2:
        {
            dis->lineEdit_2->setText(str);
            break;
        }
        case 3:
        {
            dis->lineEdit_3->setText(str);
            break;
        }
        case 4:
        {
            dis->lineEdit_4->setText(str);
            break;
        }
        case 5:
        {
            dis->lineEdit_5->setText(str);
            break;
        }
        case 6:
        {
           dis->lineEdit_6->setText(str+"%");
            break;
        }
    }
}
void Widget::on_pushButton_Open_clicked()
{
    if(net_flag == 0)
    {
        if(ui->lineEdit_IP->currentText() != "")
        {
            QString str = ui->lineEdit_IP->currentText();
            if(isIpAddr(str))
            {
                address.setAddress(str);
                if(ui->lineEdit_Port->text() != "")
                {
                    port = ui->lineEdit_Port->text().toUInt();
                    net_flag = 1;
                    tcpServer->listen(address,port);
                    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(TCPnewconnect_slot()));
                    ui->label_show->setText("正在连接...");
                }
                else
                {
                    QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("端口号不能为空"),QMessageBox::Ok | QMessageBox::Ok);
                }
            }
            else
            {
                QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("IP不合法"),QMessageBox::Ok | QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("IP不能为空"),QMessageBox::Ok | QMessageBox::Ok);
        }
    }
}

void Widget::on_pushButton_Close_clicked()
{
    if(net_flag == 1)
    {
        tcpSocket->close();
        tcpServer->close();
        disconnect(tcpServer,SIGNAL(newConnection()),this,SLOT(TCPnewconnect_slot()));
        disconnect(tcpSocket,SIGNAL(readyRead()),this,SLOT(TCPreadyread_slot()));
        net_flag = 0;
    }
     ui->label_show->setText("连接已关闭");
}
void Widget::TCPnewconnect_slot()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(TCPreadyread_slot()));
    ui->label_show->setText("网络已连接");
}
extern uint8_t  cmd_buffer[A_CMD_MAX_SIZE];
static uint16_t  size = 0;
void Widget::TCPreadyread_slot()
{
  //updatedata();
    uint16_t  size = 0;



    QByteArray temp1;
    QByteArray temp2;
    int iterationCount = 0; // 用于计数循环迭代次数

    do {
        temp2 = temp1;
        temp1 = tcpSocket->readAll();
        iterationCount++;

        qDebug() << "Iteration:" << iterationCount;
        qDebug() << "Data read in this iteration:" << temp2;

    } while (!temp1.isEmpty());

        qDebug() << "temp2 len is:" << temp2.length();


        // 将QByteArray转换为QString
        QString dataStr = QString::fromUtf8(temp2);

        // 使用split函数按逗号拆分字符串，得到QStringList
        QStringList strList = dataStr.split(',');

        // 创建一个整型数组，用于存储拆分后的数字
        QList<int> dataArray;

        // 遍历QStringList，将每个字符串转换为整数并存储到dataArray中
        for (const QString& str : strList) {
            bool ok;
            int number = str.toInt(&ok);
            if (ok) {
                dataArray.append(number);
            }
        }

        // 输出拆分后的整数数组
        for (int number : dataArray) {
            qDebug() << number;
        }


        qDebug() << "dataArray len is:" << dataArray.length();


    for(int i = 0;i<dataArray.length();i++)
    {
        A_queue_push(dataArray[i]);
        size = A_queue_find_cmd(cmd_buffer,A_CMD_MAX_SIZE);                              //从缓冲区中获取一条指令


        if(size>0)                                              //接收到指令
        {
            qDebug() << "Contents of cmd_buffer:";
            for (uint16_t i = 0; i < size; i++) {
                qDebug() << static_cast<int>(cmd_buffer[i]);
            }
            qDebug() << "size:" << size;


            A_ProcessMessage(cmd_buffer, size,ui);                             //指令处理
        }
    }


}
void Widget::on_Scan_clicked()
{
    ui->lineEdit_IP->clear();
    QList<QString> strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&ipAddressesList.at(i).toIPv4Address())
           {
               strIpAddress.append(ipAddressesList.at(i).toString());
              // break;
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())strIpAddress.append(QHostAddress(QHostAddress::LocalHost).toString());
     ui->lineEdit_IP->addItems(strIpAddress);
}

void Widget::on_pushButton_clicked()
{
    Widget2 *widget2 = new Widget2;
    widget2->setGeometry(this->geometry());
    widget2->show();


}
void Widget::on_pushButton_2_clicked()
{
    SetButtonValue_forAndroid(1,1,1);
    qDebug()<<"ok";
}

void Widget::SEND_DATA(unsigned char t)
{
    QByteArray temp;
    temp.append(t);
    tcpSocket->write(temp);
    qDebug()<<temp;
}
