#ifndef __UART_H
#define __UART_H
#include "define.h"


/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/
/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/
/****ע�⣺���޸�define.h�й��ھ���Ƶ�ʺͻ������ڵĶ���****/


/******************������غ���*********************************/

void uart_init();     //��ʼ������----�˺���ֻ�����ھ���Ƶ��11.0592MHZ,�粻��ͬ�����޸�Դ��
void print(u8 *str);  //����ַ���----�ô˺������digital_to_stringҲ��ʵ���������
void putc(u8 ch);     //����ַ�

/******************����ʹ��printf������Ҫռ��1KB����Flash��45B��RAM�ռ䣬
*******************����Ƭ���ռ��С������Ҫʹ�ã������·�EN_PRINTFΪ0����*/
#define EN_PRINTF    		1       	//ʹ��printf

//#define SIZE_OF_PRINTG	64          //���������,����
//void my_printf(const u8* str, ...);	//��ʽ������ַ���----�÷��ͱ�׼C���Ե�printf������ͬ������,ֱ��ʹ��printf����

#if EN_PRINTF
#include "stdio.h"
#endif

#endif