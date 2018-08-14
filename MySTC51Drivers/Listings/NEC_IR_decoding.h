#ifndef __NEC_IR_DECODING_H__
#define __NEC_IR_DECODING_H__
#include"define.h"

/******************** NEC��ʽ�����������***************************/

/********************������ռ�ö�ʱ��0���ⲿ�ж�0*******************/

#define IR_DATA_S_L  90        //���������ʱ����ֵ
#define IR_DATA_S_H  180       //�������ʱ����ֵ
#define IR_DATA_0_L  6         //����0���ʱ����ֵ
#define IR_DATA_0_H  16        //����0�ʱ����ֵ
#define IR_DATA_1_L  17        //����1���ʱ����ֵ
#define IR_DATA_1_H  27        //����1�ʱ����ֵ

#define IR_Receive_Int 0 //һ�廯����ͷ�ӿڣ��ⲿ�ж�0
//#define IR_Receive_Int 1 //һ�廯����ͷ�ӿڣ��ⲿ�ж�1

struct IR_STA{
	u8 Number[4];     //����������
	u8 Dat[33];       //ԭʼ����
	u16 Counter;      //������
	u8  Receive_ok;   //�������
	u8  Start_flag;   //��ʼ����
	u8  Now_flag;     //1Ϊ��ʼ
};

//��������IR_Sta
//�������ܣ�״̬��ǣ�ֻ�������˽ṹ������ĳ�Ա�ɻ�ȡ���������Ϣ�����Ƿ����ڽ��պ�����
extern struct IR_STA IR_Sta; 
//��������IR_init
//�������ܣ��������ϵͳ��ʼ��
void IR_init();  			//������ռ�ö�ʱ��0���ⲿ�ж�0
//��������NEC_IR_decoding
//�������ܣ��������
//�βΣ�num:Ϊָ����4�����ݵ�ָ�� 
//����ֵ�� Ϊ0����ɹ�		Ϊ1����ʧ��
u8 NEC_IR_decoding(u8* num);

#endif
