#ifndef __UART_H
#define __UART_H
#include "define.h"
#include "stdio.h"
/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/
/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/
/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/

/******************������غ���*********************************/
void uart_init();     //��ʼ������----�˺���ֻ�����ھ���Ƶ��11.0592MHZ,�粻��ͬ�����޸�Դ��
void print(u8 *str);  //����ַ���----�ô˺������digital_to_stringҲ��ʵ���������
void putc(u8 ch);     //����ַ�

//�����·��ĺ���ռ��1K����Flash��40BYTEde����RAM�����鿼���Ƿ�ʹ�ã�������ĺ�EN_PRINTF��Ϊ0�򲻱���
#define EN_PRINTF    		1       	//ʹ��

//#define SIZE_OF_PRINTG	64          //���������,����
void my_printf(const u8* str, ...);	    //��ʽ������ַ���----�÷��ͱ�׼C���Ե�printf������ͬ 

#endif