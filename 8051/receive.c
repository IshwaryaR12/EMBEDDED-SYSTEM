#include<reg51.h>
void send_char(char a)
{
    SBUF = a;
    while(TI == 0);
    TI = 0;
}
char get_char()
{
    while(RI == 0);
    RI = 0;
    return SBUF;
}
void send_data(char *s)
{
	while(*s)
	{
		send_char(*s++);
	}
}
void main()
{
    char i_b[10];
	  char i;
	  char stored[] ="Stored ID:8051 | You Typed: ";
    
    TMOD = 0x20;
    TH1 = 0xFD;  
    SCON = 0x50; 
    TR1 = 1;     
    while(1)
    {
       for(i=0;i<5;i++)
			{
				i_b[i]=get_char();
				send_char(i_b[i]);
			}
			i_b[5]='\0';
			send_char('\r');
			send_char('\n');
			send_data(stored);
			send_data(i_b);
			send_char('\r');
			send_char('\n');
    }
}
