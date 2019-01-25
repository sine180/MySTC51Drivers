#include "BH1750.h"


u8    BH_BUF[8];                   //�������ݻ�����


void  Single_Write_BH1750(uchar REG_Address);               //����д������
uchar Single_Read_BH1750(uchar REG_Address);                //������ȡ�ڲ��Ĵ�������
void  Multiple_Read_BH1750();                               //�����Ķ�ȡ�ڲ��Ĵ�������
//------------------------------------
void BH1750_Start();                    //��ʼ�ź�
void BH1750_Stop();                     //ֹͣ�ź�
void BH1750_SendACK(bit ack);           //Ӧ��ACK
bit  BH1750_RecvACK();                  //��ack
void BH1750_SendByte(BYTE dat);         //IIC�����ֽ�д
BYTE BH1750_RecvByte();                 //IIC�����ֽڶ�


/**************************************
��ʼ�ź�
**************************************/
void BH1750_Start()
{
	SDA = 1;                    //����������
	SCL = 1;                    //����ʱ����
	delay5us();                 //��ʱ
	SDA = 0;                    //�����½���
	delay5us();                 //��ʱ
	SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void BH1750_Stop()
{
	SDA = 0;                    //����������
	SCL = 1;                    //����ʱ����
	delay5us();                 //��ʱ
	SDA = 1;                    //����������
	delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(bit ack)
{
	SDA = ack;                  //дӦ���ź�
	SCL = 1;                    //����ʱ����
	delay5us();                 //��ʱ
	SCL = 0;                    //����ʱ����
	delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit BH1750_RecvACK()
{
	SCL = 1;                    //����ʱ����
	delay5us();                 //��ʱ
	CY = SDA;                   //��Ӧ���ź�
	SCL = 0;                    //����ʱ����
	delay5us();                 //��ʱ

	return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BH1750_SendByte(BYTE dat)
{
	BYTE i;

	for (i=0; i<8; i++)         //8λ������
	{
		dat <<= 1;              //�Ƴ����ݵ����λ
		SDA = CY;               //�����ݿ�
		SCL = 1;                //����ʱ����
		delay5us();             //��ʱ
		SCL = 0;                //����ʱ����
		delay5us();             //��ʱ
	}
	BH1750_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE BH1750_RecvByte()
{
	BYTE i;
	BYTE dat = 0;

	SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
	for (i=0; i<8; i++)         //8λ������
	{
		dat <<= 1;
		SCL = 1;                //����ʱ����
		delay5us();             //��ʱ
		dat |= SDA;             //������
		SCL = 0;                //����ʱ����
		delay5us();             //��ʱ
	}
	return dat;
}

//*********************************

void Single_Write_BH1750(uchar REG_Address)
{
	BH1750_Start();                  //��ʼ�ź�
	BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
	BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ
	//  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ
	BH1750_Stop();                   //����ֹͣ�ź�
}

//********���ֽڶ�ȡ*****************************************
/*
uchar Single_Read_BH1750(uchar REG_Address)
{  uchar REG_data;
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=BH1750_RecvByte();              //�����Ĵ�������
	BH1750_SendACK(1);
	BH1750_Stop();                           //ֹͣ�ź�
    return REG_data;
}
*/
//*********************************************************
//
//��������BH1750�ڲ�����
//
//*********************************************************
float Multiple_read_BH1750(void)
{
	uchar i;
	int temp;
	float dat;
	
	Single_Write_BH1750(0x01);   // power on
	Single_Write_BH1750(0x10);   // H- resolution mode
	delay_ms(180);              //��ʱ180ms
	
	
	BH1750_Start();                          //��ʼ�ź�
	BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�

	for (i=0; i<3; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
	{
		BH_BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
		if (i == 3)
		{

			BH1750_SendACK(1);                //���һ��������Ҫ��NOACK
		}
		else
		{
			BH1750_SendACK(0);                //��ӦACK
		}
	}

	BH1750_Stop();                          //ֹͣ�ź�
	
	temp=BH_BUF[0];
	temp=(temp<<8)+BH_BUF[1];//�ϳ�����
	dat = (float)temp/1.2;
	delay_ms(5);
	
	return dat;
}


//��ʼ��BH1750��������Ҫ��ο�pdf�����޸�****
void Init_BH1750(void)
{
	Single_Write_BH1750(0x01);
}