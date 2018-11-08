/*
 * BPM counter
 * 
 * Small utility to display BPM on a 16x2 I2C LED display 
 * Written for DIN Sync devices like the TR-606, with no speed display.  
 * Counts clock pulses/s, so it needs a fast clock (24ppq DIN sync or faster), 
 * if you want to determine BPM from a slow clock, like a click track or drum 
 * trigger, use my bpmcounter2 utility (which calculates speed from the timing  
 * between each pair of clicks)
 * 
 * Connect the (TTL level) clock signal to pin 2 (and ground to GND) - e.g. 
 * DIN Sync Pin 3 to Arduino Uno Pin 2, DIN Pin 2 to any GND terminal on the Uno 
 * 
 * Copyright 2018 Sevo Stille <mailto:sevo@radiox.de>
 * @license GPL-3.0+ <http://www.gnu.org/licenses/gpl.html>
 * 
*/


#include <LiquidCrystal_I2C.h> // For display

LiquidCrystal_I2C lcd(0x3F, 16, 2); // default 16/2 I2C display

const int ticks_per_beat = 24; // ENTER PULSE PER QUARTER CLOCK RATE HERE  (My JMS studio clock goes up to 96ppq output, 
                               // for Korg DIN sync you'd want 48, for Roland 24) 

 
int ledPin = LED_BUILTIN ;           //   STATUS LED
 
int led = 0, ledc = 0;  //  INTEGERS TO STORE LED VALUE AND COUNTER

int input = 2;                // input at pin 2
volatile byte counter;        // tick counter
float bpm;                    // BPM value


// timer interrupt function, invoked by each tick on pin, updates counter and LED 
void isr()
 {
   //On each tick update count
      counter++;

   if (ledc++ > (ticks_per_beat-1)){              // count up to one beat 
    ledc = 0;
   }
   digitalWrite(ledPin, ledc<(ticks_per_beat/4));  // flash LED for first quarter of beat
 }

 void setup()
 {
   attachInterrupt(0, isr, RISING);     //  ADD AN INTERRUPT FOR EACH TICK INPUT   
   pinMode(ledPin, OUTPUT); // Set LED OUT
   pinMode(input, INPUT); // Sets input
   counter = 0;

   lcd.init(); //Init display 
   lcd.backlight(); //Power up backlight  
     lcd.print("BPM Counter");           
     lcd.setCursor(0, 1);
     lcd.print("by sevo");          
     delay(2000);                     // pause
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("BPM counting");       // go
       
}

 void loop()
 {
   delay(1000);//Update RPM every second

   detachInterrupt(0); // Halt interrupt

   bpm = (counter/(ticks_per_beat/60.0));

     lcd.setCursor(0, 0);
     lcd.print(counter,DEC);                        //  PRINT tick count
     lcd.print(" ticks/s      ");                       

     lcd.setCursor(0, 1);
     lcd.print(bpm,DEC);                        //  PRINT BPM
     lcd.print(" BPM           ");
   counter = 0;

   attachInterrupt(0, isr, RISING);   //Restart interrupt 
  
 }

 
