#include <LiquidCrystal.h>

// Define the LCD pins
const int rs = 12;
const int en = 11;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;


const int buzzer = 10; //defining the buzzer pin
const int buttonpin = 3; //defining the button pin
const int IR_Receiver = 9;  //defining the IR_Receiver pin
const int LED = 8;  //defining the LED pin
bool flag = false;

int buttonstate = 0;  
unsigned long duration; //duration of the pulse

// Create an LCD object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(20, 4);

  Serial.begin(9600);

     /*Inputs*/
  pinMode(IR_Receiver,INPUT); //setting IR receiver as input
  pinMode(buttonpin, INPUT); //setting the button as input

      /*Outputs*/
  pinMode(LED,OUTPUT); //setting LED as output
  pinMode(buzzer, OUTPUT); //setting buzzer as output



}

void loop() {

   duration = pulseIn(9, HIGH); //reading the pulses generated from Tiva
   buttonstate = digitalRead(buttonpin); //Reading the mute button state

    /*Duration interval for the Magnetic sensor Protocol*/
   if (duration>400000 && duration<600000){
    lcd.clear();
     lcd.setCursor(0, 0);
    lcd.print("Magnet Detected!");
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
      delay(5000);
   }

    /*Duration interval for the Ultrasonic sensor Protocol*/
   else if (duration<18000 && duration>10000){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Object Detected!");    
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
    delay(5000);
  }

  /*Duration interval for the Smoke/Gas sensor Protocol*/
  else if (duration<400000 && duration>200000) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Smoke/Gas ");
     lcd.setCursor(0, 1);
     lcd.print("Detected!");
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
    delay(5000);
  }

   //System is on but tghere is nothing to detect
  else if (duration<60000 && duration>40000){
    lcd.clear();
    lcd.setCursor(0, 0);
    if (flag){
    lcd.print("System ");
    lcd.setCursor(0, 1);
    lcd.print("Started");
    delay(2000);
    flag = false;
    }
    lcd.clear();
    lcd.print("Nothing ");
    lcd.setCursor(0, 1);
   lcd.print("Detected!");
   delay(1000);
        if (buttonstate){
        delay(5000);
        digitalWrite(buzzer, LOW);
        digitalWrite(8, LOW);
      }
  }

    //System is disabled
  else if (duration< 4000){
    flag = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Disabled");
    delay(1000);
        if (buttonstate){
        delay(5000);
        digitalWrite(buzzer, LOW);
        digitalWrite(8, LOW);
      }
  }

  Serial.println(duration);

}
