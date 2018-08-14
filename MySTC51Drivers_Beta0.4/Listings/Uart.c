#include "uart.h"

#if Fosc==11059200     //��������˾���Ƶ��11059200
	#if Machine_Cycle==2UL   //12c5a60s2
		void uart_init()     //������19200
		{
			PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
			SCON = 0x50;		//8λ����,�ɱ䲨����
			AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
			AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
			TMOD &= 0x0F;		//�����ʱ��1ģʽλ
			TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
			TL1 = 0xDC;			//�趨��ʱ��ֵ
			TH1 = 0xDC;			//�趨��ʱ����װֵ
			ET1 = 0;				//��ֹ��ʱ��1�ж�
			TR1 = 1;				//������ʱ��1
		}

	#elif Machine_Cycle==12UL    //89c52
		void uart_init()     //19200
		{
			PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
			SCON = 0x50;		//8λ����,�ɱ䲨����
			AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
			AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
			TMOD &= 0x0F;		//�����ʱ��1ģʽλ
			TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
			TL1 = 0xFD;			//�趨��ʱ��ֵ
			TH1 = 0xFD;			//�趨��ʱ����װֵ
			ET1 = 0;				//��ֹ��ʱ��1�ж�
			TR1 = 1;				//������ʱ��1
		}
	#endif
#elif Fosc==12000000     //��������˾���Ƶ��12000000
	#if Machine_Cycle==2UL   //12c5a60s2
		void uart_init()     //������19200
		{
			PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
			SCON = 0x50;		//8λ����,�ɱ䲨����
			AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
			AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
			TMOD &= 0x0F;		//�����ʱ��1ģʽλ
			TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
			TL1 = 0xD9;		//�趨��ʱ��ֵ
			TH1 = 0xD9;		//�趨��ʱ����װֵ
			ET1 = 0;		//��ֹ��ʱ��1�ж�
			TR1 = 1;		//������ʱ��1
		}

	#elif Machine_Cycle==12UL    //89c52
		void uart_init()     //4800
		{
			PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
			SCON = 0x50;		//8λ����,�ɱ䲨����
			AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
			AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
			TMOD &= 0x0F;		//�����ʱ��1ģʽλ
			TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
			TL1 = 0xF3;		//�趨��ʱ��ֵ
			TH1 = 0xF3;		//�趨��ʱ����װֵ
			ET1 = 0;		//��ֹ��ʱ��1�ж�
			TR1 = 1;		//������ʱ��1
		}
	#endif
#endif
void putc(u8 ch)
{
	TI = 0;
	SBUF = ch;	        
	while(!TI);			//�ȴ��������
	TI = 0;	
}
void print(u8* str)
{
	while(*str!='\0')
	{
		putc(*str);
		str++;
	}
} 

#if EN_PRINTF
/*
void my_printf(u8* str, ...)
{
	u8 string[SIZE_OF_PRINTG];
  void* Arg=0;
	Arg=(u8 *)&str;
  Arg=(u8 *)Arg+sizeof(str); //��ջ4�ֽڶ���	
	vsprintf(string,str,Arg);
	print(string);
	Arg=0;
	
} 
*/
void my_printf(u8* str, ...)
{
  void* Arg=(u8 *)&str+sizeof(str);
	TI = 1;
	vprintf(str,Arg);
	Arg=0;
	
}
#endif
