#ifndef __DS1302_H__
#define __DS1302_H__
#include<intrins.h>
#include"define.h"
/******DS1302ʱ��оƬ����******/
sbit TSCLK = P2^5;
sbit TIO = P2^4;
sbit TRST = P2^2;
/* д����ʱ�����ڸ�ʽΪBCD��ת16���ƣ�
���磺д��ʱ�� 15��8��13��22��50��30��������
	  DS1302_write_time(0x15,0x08,0x13,0x22,0x50,0x30,0x04);*/                           
extern void DS1302_write_time(uchar year,uchar month,uchar day,uchar hour,uchar minute,uchar second,uchar weak);
extern void DS1302_read_time(uchar *year,uchar *month,uchar *day,uchar *hour,uchar *minute,uchar *second,uchar *week);
#endif