#ifndef __DIGITAL_TUBE_H__
#define __DIGITAL_TUBE_H__
#include"define.h"
#include"DELAY.h"
/****�������ʾ����****/
#define  Digital_Data P0
sbit Digital_Duan = P2^6;
sbit Digital_Wei = P2^7;

void  Digital_display_time(u8 h,u8 m,u8 s);//�������ʾʱ��
void  Digital_display_num(u32 num);//�������ʾ����
void  Digital_display_4hex(u8 *num);//�������ʾ4��16������
#endif
