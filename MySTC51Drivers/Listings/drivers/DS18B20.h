#ifndef __DS18B20_H__
#define __DS18B20_H__
#include<intrins.h>
#include"define.h"
#include"delay.h"
/******DS18B20�¶ȴ���������******/
/****�ӿڶ���****/
sbit DS = P2^2;
/****��������****/
void DS18B20_init();
float DS18B20_read_temperature();
void DS18B20_change();
#endif