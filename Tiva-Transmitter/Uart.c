#include "GPIO.h"
#include "Timers.h"
#include "tm4c123gh6pm.h" 

/*Uart module 5 initialization*/
void UART5_INIT(){

  SYSCTL_RCGCUART_R |= 0x20;  //Setting the clock for module 5
  SYSCTL_RCGCGPIO_R |= 0x10; //Setting the clock for GPIO port E
  
   delayMs (50);
  
  UART5_CTL_R &= ~0x00000001; //Disabling the UART for configuration
  UART5_IBRD_R = 104; //Integer part of the baud rate
  UART5_FBRD_R = 11; //Float part of the baud rate
  UART5_CC_R  = 0x0; //Selecting the system clock
  UART5_LCRH_R = 0x60; //Line  control register for formating the UART
  UART5_CTL_R =0x301; //enabling UART,Rx,Tx
  
  GPIO_PORTE_DEN_R |= 0x30;
  GPIO_PORTE_AFSEL_R |= 0x30; //Enabling the alternate function for pins 4,5 in port E
  GPIO_PORTE_AMSEL_R = 0; //Disabling analog function
  GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0XFF00FFFF)|0x00110000; //Setting the pins 4,5 as UART pins

}

/*Writing characters to the other board connected to the Tx of the tiva*/
void Bluetooth_Write(unsigned char data)  
{
    while((UART5_FR_R & (1<<5)) != 0); /* wait until Tx buffer not full before giving it another byte */
    UART5_DR_R = data;     
}

/*Handling strings*/
void Bluetooth_Write_String(char *str)
{
  while(*str != '\0')
	{
		Bluetooth_Write(*(str++));
	}
}