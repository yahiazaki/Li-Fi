#include "tm4c123gh6pm.h" 


/*GPIO initializations*/
void GPIO_INIT(){

  //enable clock for TIMER0
   SYSCTL_RCGCTIMER_R |= 0x01;

    SYSCTL_RCGCGPIO_R|=0x02; //enable clock for GPIOB
    GPIO_PORTB_DIR_R &= (~(1<<6)); //setting pins 6 to input pins
    GPIO_PORTB_DIR_R &= (~(1<<3)); //setting pins 3 to input pins
    GPIO_PORTB_DEN_R|=(1<<6); //setting pins 6 to be digital pins
    GPIO_PORTB_DEN_R|=(1<<3);//setting pins 3 to be digital pins
    GPIO_PORTB_PUR_R |= (1<<6); //Pullup resistance for pin 6
    GPIO_PORTB_PUR_R |= (1<<3); //Pullup resistance for pin 3

    SYSCTL_RCGCGPIO_R|=0x01; //enable clock for GPIOA
    GPIO_PORTA_DIR_R|=(1<<4);  //setting pins 4 to output pins
    GPIO_PORTA_DEN_R|=(1<<4); //setting pins 4 to be digital pins

    SYSCTL_RCGCGPIO_R|=0x04; //enable clock for GPIOC
    GPIO_PORTC_DIR_R|=(1<<4);  //setting pins 4 to output pins
    GPIO_PORTC_DEN_R|=(1<<4); //setting pins 4 to be digital pins

    SYSCTL_RCGCGPIO_R|=0x08; //enable clock for GPIOD
    GPIO_PORTD_DIR_R &= ~(1<<3);  //setting pin 3 to input pin
    GPIO_PORTD_DEN_R|=(1<<3); //setting pin 3 to be digital pin


    SYSCTL_RCGCADC_R |= 0x01; //enable clock for ADC input channel 0
    GPIO_PORTE_AFSEL_R |= (1<<3); //enable alternate function for port E pin 3
    GPIO_PORTE_DEN_R &= ~(1<<3); //disable digital functionality for pin 3 
    GPIO_PORTE_AMSEL_R |= (1<<3); //enable analog function for port E pin 3
    
    SYSCTL_RCGCGPIO_R |= 0x20; //enable clock for GPIOF
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_DIR_R &= ~(1<<4); //SW1
    GPIO_PORTF_DEN_R |= 0x1E;
    GPIO_PORTF_PUR_R |= 0x10;
    
}

/*Switch one for starting the system*/
void Button1_interrupt(){

  // Set edge-sensitive interrupt on PF4
GPIO_PORTF_IS_R &= ~0x10;  // Set IS bit for PF4 as edge triggered
GPIO_PORTF_IBE_R = 0; // Disable IBE bit for PF4 to work with IEV
GPIO_PORTF_IEV_R &= ~0x10; // Set interrupt to trigger on falling edge for PF4


// Enable interrupt for PF4
GPIO_PORTF_IM_R |= 0x10;

// Enable interrupts globally
NVIC_EN0_R |= 0x40000000; // Enable interrupt for Port F

}

/*External button for closing the system*/
void Button2_interrupt(){

  // Set edge-sensitive interrupt on PB3
GPIO_PORTB_IS_R &= ~0x08;  // Set IS bit for PB3 as edge triggered
GPIO_PORTB_IBE_R = 0; // Disable IBE bit for PB3 to work with IEV
GPIO_PORTB_IEV_R &= ~0x08; // Set interrupt to trigger on falling edge for PB3


// Enable interrupt for PB3
GPIO_PORTB_IM_R |= 0x08;

// Enable interrupts globally
NVIC_EN0_R |= 0x00000002; // Enable interrupt for Port B

}