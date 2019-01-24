#ifndef __BH1750_H__
#define __BH1750_H__
#include "define.h"
#include "delay.h"
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>

sbit	  SCL=P1^0;      //IICʱ�����Ŷ���
sbit  	  SDA=P1^1;      //IIC�������Ŷ���

#define	  SlaveAddress   0x46 	//����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�

void Init_BH1750(void); 			//��ʼ��
float Multiple_read_BH1750(void); 	//����ֵ����ǿ ��λ��lx

#endif