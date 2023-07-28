/************************************版权申明********************************************
**                             广州大彩光电科技有限公司
**                             http://www.gz-dc.com
**-----------------------------------文件信息--------------------------------------------
** 文件名称:   cmd_queue.c
** 修改时间:   2018-05-18
** 文件说明:   用户MCU串口驱动函数库
** 技术支持：  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
使用必读
cmd_queue.c中共5个函数：清空指令数据queue_reset()、从串口添加指令数据queue_push()、
从队列中取一个数据queue_pop().获取队列中有效数据个数queue_size()、从指令队列中取出一条完整的指令queue_find_cmd（）
若移植到其他平台，需要修改底层寄存器设置,但禁止修改函数名称，否则无法与HMI驱动库(hmi_driver.c)匹配。
--------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------*/
#include "cmd_queue.h"
#include "qglobal.h"
#include <QDebug>

#define A_CMD_HEAD 0XEE                                                  //帧头
#define A_CMD_TAIL 0xFFFCFFFF                                           //帧尾

typedef struct A_QUEUE
{
    uint16_t _head;                                                       //队列头
    uint16_t _tail;                                                       //队列尾
    uint8_t _data[A_QUEUE_MAX_SIZE];                                       //队列数据缓存区
} A_QUEUE;

static A_QUEUE A_que = {0,0,0};                                            //指令队列
static uint32_t A_cmd_state = 0;                                           //队列帧尾检测状态
static uint16_t A_cmd_pos = 0;                                              //当前指令指针位置

/*!
*  \brief  清空指令数据
*/
void A_queue_reset()
{
    A_que._head = A_que._tail = 0;
    A_cmd_pos = A_cmd_state = 0;
}
/*!
* \brief  添加指令数据
* \detial 串口接收的数据，通过此函数放入指令队列
*  \param  _data 指令数据
*/
void A_queue_push(uint32_t _data)
{
    uint16_t pos = (A_que._head+1)%A_QUEUE_MAX_SIZE;
    if(pos!=A_que._tail)                                                //非满状态
    {
        A_que._data[A_que._head] = _data;
        A_que._head = pos;

        // 添加调试信息
       qDebug() << "A_queue_push: Data added to queue:" << static_cast<int>(_data);
       qDebug() << "A_queue_push: Queue head:" << A_que._head << "Queue tail:" << A_que._tail;
    }

}

//从队列中取一个数据
static void queue_pop(uint8_t* _data)
{
    if(A_que._tail!=A_que._head)                                          //非空状态
    {
        
        *_data = A_que._data[A_que._tail];
        A_que._tail = (A_que._tail+1)%A_QUEUE_MAX_SIZE;
    }
}

//获取队列中有效数据个数
uint16_t A_queue_size()
{
    return ((A_que._head+A_QUEUE_MAX_SIZE-A_que._tail)%A_QUEUE_MAX_SIZE);
}
/*!
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t A_queue_find_cmd(uint8_t *buffer,uint16_t buf_len)//qdata uint8_t   qsize uint16_t
{
    uint16_t cmd_size = 0;
    uint8_t _data = 0;

    while(A_queue_size()>0)
    {

        //取一个数据
        queue_pop(&_data);

        if(A_cmd_pos==0&&_data!=A_CMD_HEAD)                               //指令第一个字节必须是帧头，否则跳过
        {
            qDebug() << "Skipping data:" << static_cast<int>(_data);
            continue;
        }

        // 输出当前取出的数据和指令指针位置
        qDebug() << "A_queue_find_cmd: Current data: " << _data << " A_cmd_pos: " << A_cmd_pos;

        if(A_cmd_pos<buf_len)                                           //防止缓冲区溢出
            buffer[A_cmd_pos++] = _data;

        A_cmd_state = ((A_cmd_state<<8)|_data);   //拼接最后4个字节，组成一个32位整数

        qDebug() <<" A_cmd_state: " << A_cmd_state;

        //最后4个字节与帧尾匹配，得到完整帧
        if(A_cmd_state==A_CMD_TAIL)
//        if(_data==255)
        {

            cmd_size = A_cmd_pos;                                       //指令字节长度
            A_cmd_state = 0;                                            //重新检测帧尾巴
            A_cmd_pos = 0;                                              //复位指令指针

#if(CRC16_ENABLE)
            //去掉指令头尾EE，尾FFFCFFFF共计5个字节，只计算数据部分CRC
            if(!CheckCRC16(buffer+1,cmd_size-5))                      //CRC校验
                return 0;

            cmd_size -= 2;                                            //去掉CRC16（2字节）
#endif
            qDebug() << "Found complete command! Command size:" << cmd_size;
            return cmd_size;
        }
    }
    return 0;                                                         //没有形成完整的一帧
}
