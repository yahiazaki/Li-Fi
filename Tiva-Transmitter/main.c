#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "Uart.h"
#include "Timers.h"
#include "MagneticSensor.h"
#include "ADC.h"

//starting and stopping the system flag
bool Start_Stop = false;

//Magnetic handler function which executes when rising the interrupt flag
void MagneticHandler(){
  
//Writing message to the Application
  Bluetooth_Write_String("Magnet detected\n");
  
  /*Magnetic sensor protocol*/
  GPIO_PORTC_DATA_R |=(1<<4);
  timer0A_delayus(500000);
  GPIO_PORTC_DATA_R &= ~(1<<4);
  timer0A_delayus(500000);
  GPIO_PORTC_DATA_R |=(1<<4);
  
  GPIO_PORTD_ICR_R |= 0x08; //Clearing the interrupt flag
}

//Switch inturrupt which start the system with setting the flag
void StartHandler(){

  //SW1-start
    if(GPIO_PORTF_RIS_R & 0x10)
    {
    Start_Stop = true;
    GPIO_PORTF_ICR_R |= 0x10; 
    }
    
}

//Button inturrupt which stop the system with clearing the flag
void StopHandler(){

   if (GPIO_PORTB_RIS_R & 0x08){
    Start_Stop = false;
    GPIO_PORTB_ICR_R |= 0x08;
    }
    
}

 /*Main Program*/
int main(){
  
  /*Initializations*/
    UART5_INIT();
    GPIO_INIT();
    ADC_INIT();
    
    /*interrupts initializations*/
    Magnetic_interrupt();
    Button1_interrupt();
    Button2_interrupt();
    __asm("CPSIE i"); 
    
    while(1){
      
     /*start the system if flag is raised*/
       if(Start_Stop){
         
            //Enable magnetic interrupt
            GPIO_PORTD_IM_R |= 0x08;
            
            //Ultrasonic Sensor Trigerring
            GPIO_PORTA_DATA_R &= ~(1 << 4);
            timer0A_delayus(10);
            GPIO_PORTA_DATA_R |= (1 << 4);
            timer0A_delayus(10);
            GPIO_PORTA_DATA_R &= ~(1 << 4);

            // Wait for the echo pin to become active
            timer0A_delayus(2000);


            // Check the echo pin
            
            if ((GPIO_PORTB_DATA_R & (1 << 6)) == 0) {
              //Writing message to the application
                Bluetooth_Write_String("Object detected\n");
                
                /*Ultrasonic protocol*/
                GPIO_PORTC_DATA_R |=(1<<4);
                timer0A_delayus(100000);
                GPIO_PORTC_DATA_R &= ~(1<<4);
                timer0A_delayus(100000);
                GPIO_PORTC_DATA_R |=(1<<4);

            } 
            else {
                  //No Obstacle Detected
                GPIO_PORTC_DATA_R |=(1<<4);
                timer0A_delayus(50000);
                GPIO_PORTC_DATA_R &= ~(1<<4);
                timer0A_delayus(50000);
                GPIO_PORTC_DATA_R |=(1<<4); 
            }
       
           //Smoke&Gas Sensor Trigerring
            ADC_Handler();  
        
      }
    
      /*Disabling the system if flag is cleared*/
    else{
      
     //Disable magnetic interrupt
   GPIO_PORTD_IM_R &= ~0x08;
   
   //Writing to the Application
   Bluetooth_Write_String("System Disabled\n");
   
   //Waiting for interrupts
   __asm(" wfi");
   
   }
        
 }
    
}
    