#ifndef __DHT11_H__
#define __DHT11_H__

#include "define.h"
#include "delay.h"

//IO����
sbit P2_0=P2^0;

//����0 �ɹ�
//��������ֵ ������룺����λ�ã�
//������ʪ�ȣ��¶�
u8 dht11_get_data(u8 *RH,u8 *T);
#endif