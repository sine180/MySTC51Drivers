#include"DS1302.h"
void DS1302_init()
{
	TRST = 0;
	_nop_();
	TSCLK = 0;
	_nop_();
}
void Write_time(uchar cmd, dat)
{
	uchar i;
	DS1302_init();
	TRST = 1;
	for(i=0;i<8;i++)
	{			
		_nop_();
		TSCLK = 0;
		if((cmd&0x01)==0x01)
			TIO = 1;
		else
			TIO = 0;
		cmd>>=1;
		TSCLK = 1;
	}
	for(i=0;i<8;i++)
	{	
		_nop_();
		TSCLK = 0;
		if((dat&0x01)==0x01)
			TIO = 1;
		else
			TIO = 0;
		dat>>=1;
		TSCLK = 1;
	}
	TSCLK = 0;
	TRST = 0;	
}
uchar Read_time(uchar cmd)
{
	uchar i,temp,time_h,time_l;
	DS1302_init();
	TRST = 1;
	for(i=0;i<8;i++)
	{	
		_nop_();
		TSCLK = 0;
		if((cmd&0x01)==0x01)
			TIO = 1;
		else
			TIO = 0;
		cmd>>=1;
		TSCLK = 1;	
	}
	for(i=0;i<8;i++)
	{				
		_nop_();
		TSCLK = 0;
		temp>>=1;		
		if(TIO)
		temp = temp|0x80;		
		TSCLK = 1;
	}
	TSCLK = 0;
	TRST = 0;
	time_h = temp/16;
	time_l = temp%16;
	temp = time_h*10+time_l;
	return temp;
}
void DS1302_write_time(uchar year,month,day,hour,minute,second,week)
{
	Write_time(0x8e,0x00);			//�ر�д����
	Write_time(0x8C,year);			//��
	Write_time(0x88,month);			//��
	Write_time(0x86,day);			//��
	Write_time(0x84,hour);			//ʱ
	Write_time(0x82,minute);		//��
	Write_time(0x80,second);		//��
	Write_time(0x8A,week);			//����
	Write_time(0x8e,0x80);			//��д����
}
void DS1302_read_time(uchar *year,uchar *month,uchar *day,uchar *hour,uchar *minute,uchar *second,uchar *week)
{
	Write_time(0x8e,0x00);			//�ر�д����
	*year = Read_time(0x8D);		//��
	*month = Read_time(0x89);	   	//��
	*day = Read_time(0x87);		  	//��
	*hour = Read_time(0x85);		//ʱ
	*minute = Read_time(0x83);		//��
	*second = Read_time(0x81);		//��
	*week = Read_time(0x8B);		//����
	Write_time(0x8e,0x80);			//��д����
}