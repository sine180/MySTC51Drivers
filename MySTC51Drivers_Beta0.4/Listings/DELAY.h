#ifndef __DELAY_H__
#define __DELAY_H__
#include"define.h"
#include<intrins.h>

/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/
/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/
/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/

#define TIME_MS Fosc/Machine_Cycle/1000
#define TIME_I	(TIME_MS+506)/514
#define TIME_J	((TIME_MS+506)%514)/2

/***********��ʱ����**************/
void delay_ms(uint ms);     //�����
void delay5us();
#endif
