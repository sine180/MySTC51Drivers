#include "LCD_1602.h"


/*------------��������--------------*/
void LCD_1602_W_cmd(u8 cmd);
void LCD_1602_W_dat(u8 dat);
void LCD_1602_display(u8 x,u8 y,u8 l,u8 *p);
void LCD_pointer_position(u8 x,y);
void LCD_1602_init();
/*----------------------------------*/
void LCD_1602_W_cmd(u8 cmd)
{
	LCD_1602_RS = 0;
	LCD_1602_RW = 0;
	LCD_1602_DATA = cmd;
	LCD_1602_EN = 1;
	delay5us();
	LCD_1602_EN = 0;
	delay_ms(1);
}
void LCD_1602_W_dat(u8 dat)
{
	LCD_1602_RS = 1;
	LCD_1602_RW = 0;
	LCD_1602_DATA = dat;
	LCD_1602_EN = 1;
	delay5us();
	LCD_1602_EN = 0;
	delay5us();
}
void LCD_1602_display(u8 x,u8 y,u8 l,u8 *p) //�ַ�����ʾ
{
	u8 i;
    LCD_pointer_position(x,y);
	for(i=0;p[i]!='\0'&&i<l;i++)
	{
		LCD_1602_W_dat(p[i]);
	}
	for(;i<l;i++)
		LCD_1602_W_dat(0x20);
	
}
void LCD_pointer_position(u8 x,y)//����ָ��λ��
{
	if(x==1&&y>0&&y<40)
	LCD_1602_W_cmd(0x80+y-1);
	else if(x==2&&y>0&&y<40)
	LCD_1602_W_cmd(0x80+0x40+y-1);
	else
	LCD_1602_W_cmd(0x80);
}
void LCD_1602_clean()
{
	LCD_1602_W_cmd(0x01); //����
	delay_ms(2);
}
void LCD_1602_init()
{
 	LCD_1602_RW = 0;
	delay_ms(15);
	LCD_1602_W_cmd(0x38);
	delay_ms(100);
	LCD_1602_W_cmd(0x38); //8λ���ݽӿڣ�16*2���ַ�
	delay_ms(1);
	LCD_1602_W_cmd(0x08); //����ʾ
	delay_ms(1);
	LCD_1602_W_cmd(0x01); //����
	delay_ms(2);
//	LCD_1602_W_cmd(0x04); //дһ���ַ��󣬵�ַָ���һ����һ���������ƶ�
//	LCD_1602_W_cmd(0x05); //дһ���ַ��󣬵�ַָ���һ����һ�����������ƶ�
	LCD_1602_W_cmd(0x06); //дһ���ַ��󣬵�ַָ���һ����һ���������ƶ�
//	LCD_1602_W_cmd(0x07); //дһ���ַ��󣬵�ַָ���һ����һ�����������ƶ�

	LCD_1602_W_cmd(0x0c); //����ʾ������ʾ���
//	LCD_1602_W_cmd(0x0e); //����ʾ����ʾ��꣬��겻��˸
//	LCD_1602_W_cmd(0x0f); //����ʾ����ʾ��꣬�����˸

	delay_ms(2);
}

