#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>

namespace Ui {
class Widget2;
}

class Widget2 : public QWidget
{
    Q_OBJECT

public:
    explicit Widget2(QWidget *parent = nullptr);
    ~Widget2();

private slots:
    void on_MenuBt1_clicked();

    void on_MenuBt2_clicked();

private:
    Ui::Widget2 *ui;
};

#endif // WIDGET2_H
