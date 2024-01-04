#include "GPIO.h"
#include "Uart.h"
#include "Timers.h"
#include "GPIO.h"
#include "Uart.h"
#include "GPIO.h"
#include "Uart.h"
#include "tm4c123gh6pm.h" 

//Analog value is stored for calibration
unsigned int adc_value;


    /* Analog to digital converter function initialization*/

void ADC_INIT(){

    ADC0_ACTSS_R &= ~(1<<3); //disable sample sequencer ss3 to configure the ADC
    ADC0_EMUX_R &= ~(0xF000); //configuring the trigger source
    ADC0_SSMUX3_R = 0; //analog signals are converted on input channel zero which is connected to PE3
    ADC0_SSCTL3_R |= 0x06; //configure ss3
    ADC0_ACTSS_R |= (1<<3); //enabling the ss3

}

/* Analog to digital converter function initialization*/

void ADC_Handler(){
    
    ADC0_PSSI_R |= (1<<3);
    while( (ADC0_RIS_R & (1<<3)) == 0 ); //waiting for the interrupt flag to be set 
    adc_value = ADC0_SSFIFO3_R; //storing the analog value in the FIFO
    ADC0_ISC_R = (1<<3); 

    /*ADC calibration*/

    if(adc_value<=900){
    GPIO_PORTF_DATA_R = 0x08;
    }
    
    else if(adc_value > 900){
      //Writing to the Application
    Bluetooth_Write_String("Smoke/Gas detected\n");
    GPIO_PORTF_DATA_R = 0x02;
    
    /*Smoke Sensor Protocol*/
    GPIO_PORTC_DATA_R |=(1<<4);
    timer0A_delayus(200000);
    GPIO_PORTC_DATA_R &= ~(1<<4);
    timer0A_delayus(200000);
    GPIO_PORTC_DATA_R |=(1<<4);
    
    }


}