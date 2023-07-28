#include "qglobal.h"
#include "cmd_queue.h"
#include "process_fun.h"
#include "widget.h"
uint8_t  cmd_buffer[A_CMD_MAX_SIZE];
void A_ProcessMessage(/*A_PCTRL_MSG */uint8_t msg[2048], uint16_t size,Ui::Widget *dis)
{

      uint8_t cmd_type = msg[1];            //命令类型
      uint8_t screen_id = msg[2];          //画面ID
      uint8_t control_id = msg[3];        //控件ID

    qDebug() << "cmd_type:"<<msg[1];

    qDebug() << "screen_id:"<<screen_id;

    qDebug() << "control_id:"<<control_id;


    switch(cmd_type)
    {
    case A_kCtrlButton:                                                   //按钮控件
        A_NotifyButton(screen_id,control_id);
        break;
    case A_kCtrlText:                                                     //文本控件
//        A_NotifyText(screen_id,control_id,msg->param,dis);
          A_NotifyText(screen_id,control_id,&msg[4],dis);
        break;
    case A_kCtrlGraph:
//        A_NotifyGraph(screen_id,control_id,len,&msg->param[2]);                   //画图控件
        A_NotifyGraph(screen_id, control_id, size - 8, &msg[4]); // 注意减去帧头、帧尾和控件ID的长度
    default:
        break;
    }
}




void A_NotifyText(uint16_t screen_id, uint16_t control_id, uint8_t *str,Ui::Widget *dis)
{
    if(screen_id == 0)
    {
      if(control_id == 3)
      {
            Widget::updatedata3(str,1,dis);
      }
      else if(control_id == 4)
      {
            Widget::updatedata3(str,2,dis);
      }
      else if(control_id == 5)
      {
            Widget::updatedata3(str,3,dis);
      }
      else if(control_id == 6)
      {
            Widget::updatedata3(str,4,dis);
      }
      else if(control_id == 7)
      {
            Widget::updatedata3(str,5,dis);
      }
      else if(control_id == 8)
      {
            Widget::updatedata3(str,6,dis);
      }
    }
}
void A_NotifyButton(uint16_t screen_id, uint16_t control_id)
{
  if(screen_id == 0)
  {
    if(control_id == 10)
    {

    }
    else if(control_id == 3)
    {

    }
  }
}

void A_NotifyGraph(uint16_t screen_id, uint16_t control_id, uint16_t length,uint8_t *str)
{
    int i = 0;
    float temp = 0;
    if(screen_id == 0)
    {
//      if(control_id == 0)
//      {
//          qDebug()<<length<<endl;
//          qDebug()<<str;
//          while(i<length)
//          {
//              temp = str[i++];
//              Widget::updatedata(temp);
//          }
//      }
//      else
          if(control_id == 1)
      {
          while(i<length)
          {
              temp = str[i++];
              Widget::updatedata2(temp);
          }
      }
    }
}
