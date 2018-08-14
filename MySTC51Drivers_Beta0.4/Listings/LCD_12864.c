
#include "LCD_12864.h"


void rdbf(void)   
{ 
	while(1)    
	{    
		LCD_12864_RS=0;
	  LCD_12864_RW=1;
		LCD_12864_EN=0;    
		LCD_12864_DATA=0xFF;    
		LCD_12864_EN=1;    
		if(LCD_12864_BUSY == 0)    
		break;     
	} 
}
void wr_data(uchar wrdata)    
{   
	rdbf();  	//��BF=0ʱ,ģ���ڲ����ɽ���������
	LCD_12864_RS=1;  
	LCD_12864_RW=0;  
	LCD_12864_EN=1;   
	LCD_12864_DATA=wrdata;   
	LCD_12864_EN=0; 
}  
void wr_cmd(uchar cmd)    
{        
	rdbf();     //��BF=0ʱ,ģ���ڲ����ɽ�����ָ��  
	LCD_12864_RS=0;  
	LCD_12864_RW=0;  
	LCD_12864_EN=1;   
	LCD_12864_DATA=cmd;  
	LCD_12864_EN=0; 
}
void LCD_12864_display_string(uchar x,uchar y,uchar *seg) //xΪ�к�,yΪ�к� 
{   
	uchar i=0x80;  
	uint t=0;   
	switch(x)          //ȷ����  
	{   
		case 1: i=0x80; break;     //��һ��   
		case 2: i=0x90; break;     //�ڶ���  
		case 3: i=0x88; break;     //������
		case 4: i=0x98; break;     //������ 
		default : break;  
	}   
	i=i+y-1;     //ȷ���к� 
	wr_cmd(i);   
	while(seg[t]!='\0')  
	{   
		wr_data(seg[t]); //д����Ҫ��ʾ�ַ�����ʾ��   
		t++;  
	} 
}
void LCD_12864_init(void)    
{   
	LCD_12864_PSB = 1; //ָ�����нӿ�	     
	wr_cmd(0x30);	//�����趨������ָ�
//	wr_cmd(0x36);	//�����趨������ָ�
	   
	wr_cmd(0x30);   //�����趨 
	   
	wr_cmd(0x01);    //����   

	wr_cmd(0x02);    //��ַ��λ   
	   
	wr_cmd(0x06);   //������ƣ�������ʾ���ƶ� 
//	wr_cmd(0x07);   //������ƣ�������ʾ�����ƶ�
//	wr_cmd(0x04);   //������ƣ�������ʾ���ƶ� 
//	wr_cmd(0x05);   //������ƣ�������ʾ�����ƶ�    
	
//	wr_cmd(0x08);   //������ʾ�أ����أ��α�λ�ò�����   
	wr_cmd(0x0c);   //������ʾ�������أ��α�λ�ò�����
//	wr_cmd(0x0e);   //������ʾ������꿪���α�λ�ò�����
//	wr_cmd(0x0f);   //������ʾ������꿪���α�λ�÷���  
}   