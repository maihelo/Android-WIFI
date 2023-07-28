#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtCharts>
#include <QWheelEvent>
#include <QLineSeries>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    static int net_flag;
    static quint16 port;
    static QHostAddress address;
    static int flag;
    static void SEND_DATA(unsigned char t);
    static void updatedata(float input);
    static void updatedata2(float input);
    static void updatedata3(uint8_t* input,int index,Ui::Widget *dis);
    static QLineSeries* line1;
    static QLineSeries* line2;

    ~Widget();

//private:
    Ui::Widget *ui;

    //void wheelEvent(QWheelEvent *event);
    QChart* chart;
    QChart* chart2;

    static QTcpServer *tcpServer;
    static QTcpSocket *tcpSocket;
private slots:
    void on_pushButton_Open_clicked();
    void on_pushButton_Close_clicked();
    void TCPnewconnect_slot();
    void TCPreadyread_slot();
    void on_Scan_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // WIDGET_H
