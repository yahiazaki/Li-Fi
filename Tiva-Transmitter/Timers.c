#include "tm4c123gh6pm.h" 

/*Microseconds delay function */
void timer0A_delayus(int time){
   
    TIMER0_CTL_R = 0x0; //Disabling the timer for configuration
    TIMER0_CFG_R = 0;   //Use the 32 bit timer
    TIMER0_TAMR_R = 0x02; //Setting the timer as periodic
    TIMER0_TAILR_R = (time* 16)-1; //Reload value
    TIMER0_CTL_R |= 0x03; //enabling the timer
    while((TIMER0_RIS_R & 0x01) == 0); //counting down until from the reload untill reaching zero
    TIMER0_ICR_R = 0x01; //Clearing the interrupt status in RIS

}

/*Sample of millisecond dellay without Timers*/
void delayMs (int n)
{
    int i, j; 
    for(i=0; i < n; i++) 
    {
        for(j=0; j < 3180; j++)
        {
        }
    }
 }
