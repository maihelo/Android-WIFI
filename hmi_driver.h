#ifndef HMI_DRIVER_H
#define HMI_DRIVER_H
#include "qglobal.h"





void SetTextValue_forAndroid(uint16_t screen_id,uint16_t control_id,uchar *str);
void GraphChannelDataAdd_forAndroid(uint16_t screen_id,uint16_t control_id,uint8_t *pData,uint16_t nDataLen);
void SetButtonValue_forAndroid(uint16_t screen_id,uint16_t control_id,uchar state);















#endif // HMI_DRIVER_H
