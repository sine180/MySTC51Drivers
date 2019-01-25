#ifndef __I2C_h__
#define __I2C_h__
#include"define.h"
#include<intrins.h>
#include"DELAY.h"	
/**********ģ��I2Cͨ������*************/

/******�ӿڶ���******/
sbit SCL = P1^1;
sbit SDA = P1^2;

/*��������ַ,���ݵ�ַ,Ҫд/��������ĵ�ַ��*/
uchar I2C_write_onedata(uchar Device_address,uchar word_address,uchar dat);
uchar I2C_read_onedata(uchar Device_address,uchar word_address,uchar *dat);
/*��������ַ,���ݵ�ַ,Ҫд/��������ĵ�ַ,��/д�����ݸ�����*/
uchar I2C_write_data(uchar Device_address,uchar word_address,uchar *dat,uint n);
uchar I2C_read_data(uchar Device_address,uchar word_address,uchar *dat,uint n);
#endif
