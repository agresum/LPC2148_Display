#include<lpc214x.h>
#define Fosc 12000000                    
#define Fcclk (Fosc*5)                 
#define Fcco (Fcclk*4)                 
#define Fpclk (Fcclk/4)*1              
#define UART_BPS 9600			 			//Set buadrate here
void intial_uart0(void);
void send_1byte_uart0(char data);
void send_string_uart0(char *str);
void serial_display_uart0(unsigned int temp);

void intial_uart1(void);
void send_1byte_uart1(char data);
void send_string_uart1(char *str);
void serial_display_uart1(unsigned int temp);

void intial_uart0(void)	
{
unsigned int Baud16;
PINSEL0|=(1|(1<<2));
U0LCR=0x83;		            				// DLAB = 1
Baud16=(Fpclk/16)/UART_BPS;  
U0DLM=Baud16/256;							
U0DLL=Baud16%256;						
U0LCR=0x03;
}

void send_1byte_uart0(char data)	   //Function to send a byte on UART0
{  
U0THR=data;				    
while((U0LSR&0x40)==0);	    
}

void send_string_uart0(char *str)		 //A function to send a string on UART0
{  
while(1)
{  
if(*str =='\0') break;
send_1byte_uart0(*str++);	    
}
}

void serial_display_uart0(unsigned int temp)
{
unsigned char cn,b[4],b1,b2,b3,b4;
	for(cn=0;cn<4;cn++)
	b[cn]=0;
	cn=0;
	while((temp)!=0)
	{
		b[cn]=temp%10;
		temp=temp/10;
		cn++;
	}
	b1=b[3];
	b2=b[2];
	b3=b[1];
	b4=b[0];
	send_1byte_uart0(b1+'0');
	send_1byte_uart0(b2+'0');
	send_1byte_uart0(b3+'0');
	send_1byte_uart0(b4+'0');
	send_1byte_uart0('\n');
}

void intial_uart1(void)	
{
unsigned int Baud16;
PINSEL0|=((1<<16)|(1<<18));
U1LCR=0x83;		            				// DLAB = 1
Baud16=(Fpclk/16)/UART_BPS;  
U1DLM=Baud16/256;							
U1DLL=Baud16%256;						
U1LCR=0x03;
}

void send_1byte_uart1(char data)	   //Function to send a byte on UART0
{  
U1THR=data;				    
while((U1LSR&0x40)==0);	    
}

void send_string_uart1(char *str)		 //A function to send a string on UART0
{  
while(1)
{  
if(*str =='\0') break;
send_1byte_uart1(*str++);	    
}
}

void serial_display_uart1(unsigned int temp)
{
unsigned char cn,b[4],b1,b2,b3,b4;
	for(cn=0;cn<4;cn++)
	b[cn]=0;
	cn=0;
	while((temp)!=0)
	{
		b[cn]=temp%10;
		temp=temp/10;
		cn++;
	}
	b1=b[3];
	b2=b[2];
	b3=b[1];
	b4=b[0];
	send_1byte_uart1(b1+'0');
	send_1byte_uart1(b2+'0');
	send_1byte_uart1(b3+'0');
	send_1byte_uart1(b4+'0');
	send_1byte_uart1('\n');
}
