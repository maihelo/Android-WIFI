#ifndef PROCESS_FUN_H
#define PROCESS_FUN_H
#include "qglobal.h"
#include "widget.h"


#define A_PTR2U16(PTR) ((((uint8_t *)(PTR))[0]<<8)|((uint8_t *)(PTR))[1])  //从缓冲区取16位数据
#define A_PTR2U32(PTR) ((((uint8_t *)(PTR))[0]<<24)|(((uint8_t *)(PTR))[1]<<16)|(((uint8_t *)(PTR))[2]<<8)|((uint8_t *)(PTR))[3])  //从缓冲区取32位数据


enum A_CtrlType
{
    A_kCtrlUnknown=0x00,
    A_kCtrlButton=0x01,                     //按钮
    A_kCtrlText = 0x02,                            //文本
    A_kCtrlGraph = 0x03,                           //曲线图控件
    A_kCtrlTable = 0x04,                           //表格控件
    A_kCtrlMenu = 0x05,                            //菜单控件
    A_kCtrlSelector = 0x06,                        //选择控件
};

#pragma pack(push)
#pragma pack(1)                           //按字节对齐

typedef struct
{
    uint8_t    cmd_head;                    //帧头

    uint8_t    cmd_type;                    //命令类型(UPDATE_CONTROL)
    uint16_t   screen_id;                   //产生消息的画面ID
    uint16_t   control_id;                  //产生消息的控件ID

    uint8_t    param[256];                  //可变长度参数，最多256个字节

    uint8_t  cmd_tail[4];                   //帧尾
}A_CTRL_MSG,*A_PCTRL_MSG;

#pragma pack(pop)

void A_NotifyText(uint16_t screen_id, uint16_t control_id, uint8_t *str,Ui::Widget *dis);
void A_NotifyButton(uint16_t screen_id, uint16_t control_id);
void A_NotifyGraph(uint16_t screen_id, uint16_t control_id, uint16_t length,uint8_t *str);
void A_ProcessMessage(/*A_PCTRL_MSG*/ uint8_t msg[2048], uint16_t size,Ui::Widget *dis);
#endif // PROCESS_FUN_H
