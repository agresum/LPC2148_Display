#include<lpc214x.h>
/* CONNECTIONS X+ P0.25(AD0.4), Y+ P0.29(AD0.2), X- P0.28(AD0.1), Y- P0.30(AD0.3)*/ 

#define adclkdiv (14<<8)
#define adpdn (1<<21)
#define adstart (1<<24)
#define adstop ~(1<<24)
int x,y;
unsigned int read_x(void);		  	
unsigned int read_y(void);  			
  
unsigned int read_x(void)		  	//CONFIGURE Y+ & Y- AS GPIO AND X+ AS ADC
{
unsigned int temp,temp1,i;
//temp=PINSEL1;
//temp1=IO0DIR;

AD0CR=(((adpdn)|(adclkdiv))|(1<<4));
PINSEL1|=(1<<18);		//pin P0.25 AS ANALOG INPUT AD0.4
PINSEL1&=(~(1<<19));
PINSEL1&=(~(((3<<24)|(3<<26))|(3<<28)));	//PIN P0.28, PIN P0.29 AND P0.30 AS GPIO
IO0DIR|=((1<<29)|(1<<30));
IO0DIR&=(~(1<<28));
IO0SET|=(1<<29);
IO0CLR|=(1<<30);
for(i=0;i<1000;i++);
AD0CR|=(adstart);
while(((AD0DR4)&0x80000000)==0x00000000);
x=((AD0DR4>>6) & 0x3FF);
AD0CR&=(adstop);

//PINSEL1=temp;
//IO0DIR=temp1;
return x;
}
