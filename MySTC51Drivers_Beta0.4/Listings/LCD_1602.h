#ifndef __LCD_1602_H__
#define __LCD_1602_H__
#include "define.h"
#include <intrins.h>
#include <stdio.h>
#include "DELAY.h"
/*****************1602Һ��������***************/

/*******************����ӿ�*************************/

#define LCD_1602_DATA P0

sbit LCD_1602_RS = P3^5;
sbit LCD_1602_RW = P3^6;
sbit LCD_1602_EN = P3^4;

/*******************��������*************************/

void LCD_1602_init();		   		  									//��ʼ�����з�ʽ
void LCD_1602_clean();														//����
/**************** x=(1--4) y(1--8) pΪ�ַ����׵�ַ **/
void LCD_1602_display(u8 x,u8 y,u8 l,u8 *p);	//д�ַ���
#endif
