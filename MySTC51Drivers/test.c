#include "define.h"
#include "delay.h"
#include "Uart.h"

/********������define.h�е�������Ƶ������������**************/

void main()
{
    delay_ms(100);
	uart_init(); //19200
	while(1)
	{   
        printf("Hello World!");
        delay_ms(1000);
	}
}
