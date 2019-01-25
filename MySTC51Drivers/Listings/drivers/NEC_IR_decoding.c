#include "NEC_IR_decoding.h"

struct IR_STA IR_Sta;
/*-----------��������------------*/
void translate();
/*---------------����----------------*/
u8 NEC_IR_decoding(u8* num)
{
	u8 i;   
		if(IR_Sta.Receive_ok)
		{
			translate();
			for(i=0;i<4;i++)
				num[i]=IR_Sta.Number[i];
			return 0;
		}
		return 1;
}
/*********��ʼ��***************/
#if Fosc==11059200UL
void IR_init()
{	
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ	
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x02;		//���ö�ʱ��ģʽ
	TL0 = 0xA4;			//���ö�ʱ��ֵ
	TH0 = 0xA4;			//���ö�ʱ����ֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	EA = 1;		 		//�����ж�
	ET0 = 1;   	 		//�򿪶�ʱ���ж�0
	EX0 = 1;			//���ⲿ�ж�0
	IT0 = 1;				//�ⲿ�ж�0�½��ش���
}
#elif Fosc==12000000UL
void IR_init()
{	
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ	
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x02;		//���ö�ʱ��ģʽ
	TL0 = 0x9C;			//���ö�ʱ��ֵ
	TH0 = 0x9C;			//���ö�ʱ����ֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	EA = 1;		 		//�����ж�
	ET0 = 1;   	 		//�򿪶�ʱ���ж�0
#if IR_Receive_Int==0
	EX0 = 1;			//���ⲿ�ж�0
	IT0 = 1;			//�ⲿ�ж�0�½��ش���
#elif IR_Receive_Int==1
	EX1 = 1;			//���ⲿ�ж�1
	IT1 = 1;			//�ⲿ�ж�1�½��ش���
#endif	
	IR_Sta.Counter=0;
    IR_Sta.Receive_ok=0;
    IR_Sta.Start_flag=0;
    IR_Sta.Now_flag=0;
    
}
#endif
/***********��ʱ���ж�************/
void timer0() interrupt 1
{
	IR_Sta.Counter++;		   //	100us
}

/*------��������ж�------*/
#if IR_Receive_Int==0 
void IR_read() interrupt 0 
#elif IR_Receive_Int==1 
void IR_read() interrupt 2 
#endif
{
	if(IR_Sta.Start_flag)
	{
		if(IR_Sta.Counter>IR_DATA_S_L&&IR_Sta.Counter<IR_DATA_S_H)
		{
			IR_Sta.Dat[0] = 1;
			IR_Sta.Now_flag=1;
		}
		else if(IR_Sta.Dat[0] == 1)
		{	
			if(IR_Sta.Counter>IR_DATA_0_L&&IR_Sta.Counter<IR_DATA_0_H)
				IR_Sta.Dat[IR_Sta.Now_flag] = 0;
			else if(IR_Sta.Counter>IR_DATA_1_L&&IR_Sta.Counter<IR_DATA_1_H) 
				IR_Sta.Dat[IR_Sta.Now_flag] = 1;
			else
				{ 
					IR_Sta.Start_flag = 1;
					IR_Sta.Dat[0] = 0;
					IR_Sta.Now_flag=1;										 
				}
			IR_Sta.Now_flag++;	  
			if(IR_Sta.Now_flag==33)
			{
				IR_Sta.Dat[0] = 0;
				IR_Sta.Receive_ok = 1;
				IR_Sta.Start_flag = 0;
				IR_Sta.Now_flag = 1;
			}			
		} 
		else
		{
			IR_Sta.Start_flag = 1;
			IR_Sta.Dat[0] = 1;
		}
	}
	else
	{
		IR_Sta.Start_flag = 1;
	}
	IR_Sta.Counter = 0;			
}
/*----------����---------*/
void translate()
{
	uchar i,j;
	for(i=0;i<4;i++)
		for(j=0;j<8;j++)
			{ 	
				IR_Sta.Number[i]>>=1;
				if(IR_Sta.Dat[i*8+j+1])
				IR_Sta.Number[i] |= 0x80;
			}
	IR_Sta.Receive_ok = 0;	
}
