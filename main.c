#include<lpc214x.h>
#include "display_data.h"
#include "glcd.h"
#include "my_adc.h"
#include "my_uart0.h"
int main(void)
{
unsigned int x,y;
intial_uart0();
first:
glcd_display(hi);
delay(50000);
glcd_display(intro);
delay(150000);
glcd_display(wait);
delay(100000);
glcd_display(start);
delay(100);

back:
do{
x=read_x();
y=read_y();
delay(100);
send_string_uart0("ok\n");
delay(100);
}while(x<50 & y<50);
send_string_uart0("ok1\n");	
delay(1000);

x=read_x();
delay(1000);
y=read_y();
delay(100);
send_string_uart0("ok2\n");	
delay(1000);
if(810<x<840 & 250<y<580)
{
send_string_uart0("ok3\n");	
delay(1000);
glcd_display(processing);
delay(500000);
}
else
{
goto back;
}
goto first;
}
