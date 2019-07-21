#include <LPC21xx.H> 
char data_transmit[]="\nShri Ganeshay Namhaa";
//# define PLOCK=0x400 
void PLL_INIT()
{
 PLLCON = 0x01;   //Enable PLL
 PLLCFG = 0x24;   //Multiplier and divider setup
 PLLFEED = 0xAA;  //Feed sequence
 PLLFEED = 0x55;
 
 while(!(PLLSTAT & 0x00000400)); //is locked?
 
 PLLCON = 0x03;   //Connect PLL after PLL is locked
 PLLFEED = 0xAA;  //Feed sequence
 PLLFEED = 0x55;
 VPBDIV = 0x01; 
}

void INIT_UART()
{
PINSEL0=0x05;
U0LCR=0x83;
U0DLL=135;		  
U0DLM=1;
//U0FDR=0xF1;
U0LCR&=0x0F;
}

void U0WRITE(char data)
{
while(!(U0LSR & (1<<5)));
U0THR=data;
}

void transmit(char *address )
{
int i;
while(*address !=0x00)
{
U0WRITE(*address);
for( i=0;i<65000;i++);
address++;
   
}

}

char *receive_data (void) 
 {     
  int i=0;               /* Read character from Serial Port   */
  char *x;
  char rec[100];
  x=&rec[0];
  while (!(U0LSR & 0x01));
	  rec[0]=U0RBR;
    	i++;
  return(x);
 
}


int main()
{
char *x; 
PLL_INIT();
INIT_UART();
 		transmit(data_transmit);
//U0WRITE('a');
  while(1)
   {
		x=receive_data();
		
		U0WRITE(*x);
   }

}
