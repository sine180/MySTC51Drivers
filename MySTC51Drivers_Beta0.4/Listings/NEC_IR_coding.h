#ifndef __NEC_IR_CODING_H__
#define __NEC_IR_CODING_H__
#include"define.h"
#include"DELAY.h"
/**************�ú��������ʵ��NEC��ʽ�����������*****************/

sbit IR_Send=P3^2; //����led�ӿ�

//������ռ�ö�ʱ��0�Ͷ�ʱ��1

extern void NEC_IR_send_order(uchar a,b,c,d);//4�ֽ�ָ��
#endif