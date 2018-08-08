#include<lpc214x.h>
#define rs 4
#define rw 5
#define en 6
#define rst 7
#define cs1 8
#define cs2 9
#define d 16
void delay(unsigned int n)
{
unsigned int i,j;
for(j=n+1;j>0;j--)
for(i=0;i<100;i++);
}

void glcd_display(char *data)
{
unsigned int i,c=0,p=0;
PINSEL0&=(~0xFFF00);		  
PINSEL1&=(~0xFFFF);
IO0DIR|=(0xFF03F0);
IO0CLR|=(0xFF03F0);
delay(100);

//RESET
IO0CLR|=(1<<rst);
delay(10);
IO0SET|=(1<<rst);
delay(100);
	//lcd intialization Page @0th Column @0th

	IO0CLR|=(0xFF<<16);
	IO0SET|=(0x3E<<16);	
	IO0SET|=((1<<cs1)|(1<<cs2));
	IO0CLR|=((1<<rs)|(1<<rw));
	IO0SET|=(1<<en);
	delay(10);
	IO0CLR|=(1<<en);
	delay(100);

	IO0CLR|=(0xFF<<16);
	IO0SET|=(((0xB8)|(p))<<16);
	IO0SET|=((1<<cs1)|(1<<cs2));
	IO0CLR|=((1<<rs)|(1<<rw));
	delay(1);
	IO0SET|=(1<<en);
	delay(1);
	IO0CLR|=(1<<en);
	delay(1);

	
	IO0CLR|=(0xFF<<16);
	IO0SET|=(((0x40)|(0))<<16);
	IO0SET|=((1<<cs1)|(1<<cs2));
	IO0CLR|=((1<<rs)|(1<<rw));
	delay(1);
	IO0SET|=(1<<en);
	delay(1);
	IO0CLR|=(1<<en);
	delay(1);
	

//display data
for(i=0;i<1024;i++)
{
	if(c<64)
	{
	IO0CLR|=(0xFF<<16);
	IO0SET|=(~data[i]<<16);
	IO0SET|=((1<<cs1)|(1<<rs));
	IO0CLR|=((1<<rw)|(1<<cs2));
	}
	if(c>63 & c<128)
	{
	IO0CLR|=(0xFF<<16);
	IO0SET|=(~data[i]<<16);
	IO0SET|=((1<<cs2)|(1<<rs));
	IO0CLR|=((1<<rw)|(1<<cs1));
	}
	IO0SET|=(1<<en);
	delay(1);
	IO0CLR|=(1<<en);
	delay(1);
	c++;
	if(c==128)
	{
	c=0;
	p++;
	IO0CLR|=(0xFF<<16);
	IO0SET|=(((0xB8)|(p))<<16);
	IO0SET|=((1<<cs1)|(1<<cs2));
	IO0CLR|=((1<<rs)|(1<<rw));
	delay(1);
	IO0SET|=(1<<en);
	delay(1);
	IO0CLR|=(1<<en);
	delay(1);
	
	}
} 

	IO0CLR|=(0xFF<<16);
	IO0SET|=(0x3F<<16);	
	IO0SET|=((1<<cs1)|(1<<cs2));
	IO0CLR|=((1<<rs)|(1<<rw));
	IO0SET|=(1<<en);
	delay(1);
	IO0CLR|=(1<<en);
	delay(100);

}
