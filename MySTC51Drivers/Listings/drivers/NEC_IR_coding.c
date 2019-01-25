#include "NEC_IR_coding.h" 
void send0()
{
	TR0 = 1;
	TH1 = (65536-516)/256;
	TL1 = (65536-516)%256;
	TR1 = 1;
	while(!TF1);
	TF1 = 0;
	TR1 = 0;

	TR0 = 0;
	IR_Send = 1;
	TH1 = (65536-516)/256;
	TL1 = (65536-516)%256;
	TR1 = 1;
	while(!TF1);
	TF1 = 0;
	TR1 = 0;
	IR_Send = 1;
}
void send1()
{
 	TR0 = 1;				 //�򿪺��ⷢ�䶨ʱ��0 ������38khz����
	TH1 = (65536-516)/256;
	TL1 = (65536-516)%256;	 //��ʱ��T1��ʱ560us
	TR1 = 1;				 //�򿪶�ʱ��1
	while(!TF1);			 //��ʱ������
	TF1 = 0;				 //���ñ�־λ
	TR1 = 0;				 //�رն�ʱ��1

	TR0 = 0;
	IR_Send = 1;
	TH1 = (65536-1548)/256;	  ////��ʱ��T1��ʱ1650us
	TL1 = (65536-1548)%256;
	TR1 = 1;
	while(!TF1);
	TF1 = 0;
	TR1 = 0;
	IR_Send = 1;
}
void IRsend_byte(uchar num)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if(num&0x01)
		send1();
		else
		send0();
		num>>=1;
	}
}
void IRstart()
{
	TR0 = 1;
	TH1 = (65536-8294)/256;
	TL1 = (65536-8294)%256;
	TR1 = 1;
	while(!TF1);
	TF1 = 0;
	TR1 = 0;

	TR0 = 0;
	IR_Send = 1;
	TH1 = (65536-4147)/256;
	TL1 = (65536-4147)%256;
	TR1 = 1;
	while(!TF1);
	TF1 = 0;
	TR1 = 0;
	IR_Send = 1;
}
void IRstop()
{
	TR0 = 1;
	TH1 = (65536-516)/256;
	TL1 = (65536-516)%256;
	TR1 = 1;
	while(!TF1);
	TF1 = 0;
	TR1 = 0;

	TR0 = 0;
	IR_Send = 1;
	TH1 = (65536-516)/256;
	TL1 = (65536-516 )%256;
	TR1 = 1;
	while(!TF1);
	TF1 = 0;
	TR1 = 0;
	IR_Send = 1;
}
void timer_init()
{
	TMOD = 0x12;
	TH0  = 0xf6;
	TL0  = 0xf6;
	EA   = 1;
	ET0  = 1;
}

void NEC_IR_send_order(u8 a,b,c,d)
{
	timer_init();
	delay_ms(5);
	IRstart();						 
	IRsend_byte(a);					 
	IRsend_byte(b);		
	IRsend_byte(c);
	IRsend_byte(d);
	IRstop();
}
void timer0()interrupt 1
{
	IR_Send = ~IR_Send;
}
