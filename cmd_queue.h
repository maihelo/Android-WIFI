#ifndef CMD_QUEUE_H
#define CMD_QUEUE_H
#include "glob.h"
#define A_CRC16_ENABLE 0            // 如果需要CRC16校验功能，修改此宏为1(此时需要在VisualTFT工程中配CRC校验)
#define A_CMD_MAX_SIZE 2048           // 单条指令大小，根据需要调整，尽量设置大一些
#define A_QUEUE_MAX_SIZE 8192        // 指令接收缓冲区大小，根据需要调整，尽量设置大一些


/*!
*  \brief  清空指令数据
*/
void A_queue_reset(void);

/*!
* \brief  添加指令数据
* \detial 串口接收的数据，通过此函数放入指令队列
*  \param  _data 指令数据
*/
void A_queue_push(uint32_t _data);

/*!
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t A_queue_find_cmd(uint8_t *cmd,uint16_t buf_len);

uint16_t A_queue_size();


#endif // CMD_QUEUE_H
