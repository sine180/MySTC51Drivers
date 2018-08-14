#include "define.h"
#include "delay.h"
#include "Digital_Tube.h"
#include "NEC_IR_decoding.h"
#include "Uart.h"
/********������define.h�е�������Ƶ������������**************/
void main()
{
    u8 num[4];
	u8 flag;
	delay_ms(10);
	uart_init();
    IR_init(); 
	while(1)
	{   
		flag = NEC_IR_decoding(&num);
		Digital_display_4hex(&num);
	}
}
