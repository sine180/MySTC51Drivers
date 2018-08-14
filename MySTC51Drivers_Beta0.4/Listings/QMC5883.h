#ifndef __QMC5883_H__
#define __QMC5883_H__
#include "define.h"	
#include <math.h>     
#include <stdio.h>   
#include <INTRINS.H>
#include "delay.h"
#include "I2C.h"

#define QMC5883_ADDR               0x1a 

/***********����**************/
u8 QMC5883_InitConfig(void);            	//��ʼ��5883
u8 QMC5883_GetData(float *angle);           //�뱱����н�
#endif
