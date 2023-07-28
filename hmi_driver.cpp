#include "hmi_driver.h"
#include "widget.h"



#define ATX_8(P1) A_SEND_DATA((P1)&0xFF)                    //发送单个字节
#define ATX_8N(P,N) A_SendNU8((uint8_t *)P,N)                 //发送N个字节
#define ATX_16(P1) ATX_8((P1)>>8);ATX_8(P1)                 //发送16位整数
#define ATX_16N(P,N) A_SendNU16((uint16_t *)P,N)              //发送N个16位整数
#define ATX_32(P1) ATX_16((P1)>>16);ATX_16((P1)&0xFFFF)     //发送32位整数
#define A_SEND_DATA(P) A_SEND_DATA(P)          //发送一个字节
#define A_BEGIN_CMD() ATX_8(0XEE)            //帧头
#define A_END_CMD() ATX_32(0XFFFCFFFF)       //帧尾

void A_SEND_DATA(uint8_t c)
{
    Widget::SEND_DATA(c);
}
void A_SendStrings(uint8_t *str)
{
    while(*str)
    {
        ATX_8(*str);
        str++;
    }
}
void A_SendNU8(uint8_t *pData,uint16_t nDataLen)
{
    uint16_t i = 0;
    for (;i<nDataLen;++i)
    {
        ATX_8(pData[i]);
    }
}
void SetTextValue_forAndroid(uint16_t screen_id,uint16_t control_id,uint8_t *str)
{
    A_BEGIN_CMD();
    ATX_8(0x10);
    ATX_16(screen_id);
    ATX_16(control_id);
    A_SendStrings(str);
    A_END_CMD();
}
void GraphChannelDataAdd_forAndroid(uint16_t screen_id,uint16_t control_id,uint8_t *pData,uint16_t nDataLen)
{
    A_BEGIN_CMD();
    ATX_8(0x03);
    ATX_16(screen_id);
    ATX_16(control_id);
    ATX_16(nDataLen);
    ATX_8N(pData,nDataLen);
    A_END_CMD();
}

void SetButtonValue_forAndroid(uint16_t screen_id,uint16_t control_id,uchar state)
{
  A_BEGIN_CMD();
 // ATX_8(0xB1);
  ATX_8(0x01);
  ATX_16(screen_id);
  ATX_16(control_id);
  ATX_8(state);
  A_END_CMD();
}