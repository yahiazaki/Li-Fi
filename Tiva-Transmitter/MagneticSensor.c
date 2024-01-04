#include "GPIO.h"
#include "tm4c123gh6pm.h" 

void Magnetic_interrupt(){
  
// Set edge-sensitive interrupt on PD3 (corresponds to PF4 on some boards)
GPIO_PORTD_IS_R |= 0x08;  // Set IS bit for PD3
GPIO_PORTD_IBE_R &= ~0x08; // Disable IBE bit for PD3 to work with IEV
GPIO_PORTD_IEV_R &= ~0x08; // Set interrupt to trigger on falling edge for PD3

// Enable interrupt for PD3
GPIO_PORTD_IM_R |= 0x08;

// Enable interrupts globally
NVIC_EN0_R |= 0x00000008; // Enable interrupt for Port D

}