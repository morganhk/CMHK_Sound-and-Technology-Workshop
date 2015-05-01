/*
  Sound and Technology Workshop
  Session2
  2015-05-02
  Public Domain
  
  This script displays all the input values on the LCD
  Press all 4 buttons to get a tone
  The LED colors are controlled by the LRD
  The Pot does nothing
  Code and PCB layout on http://morgan.isnot.in/CMHK/ElectronicsWorkshop

*/
#include <LiquidCrystal.h>
#include "pitches.h"

//Hold the LED pins
const int ledR = 9;         // the pin that the Red LED is attached to
const int ledG = 10;        // the pin that the Green LED is attached to
const int ledB = 11;        // the pin that the Blue LED is attached to

//Hold data for buttons
int btn1, btn2, btn3, btn4;
const int btnPin1 = 12;
const int btnPin2 = 13;
const int btnPin3 = A4;
const int btnPin4 = A5;

//Hold data for LRD
int lrd1, lrd2, lrd3;
const int lrdPin1 = A2;
const int lrdPin2 = A1;
const int lrdPin3 = A0;

//Hold data for Potentiometer
int pot1;
const int potPin1 = A3;

//Hold the LCD pins
LiquidCrystal lcd(2, 3, 4, 5, 6 , 7);

//Setup
void setup() {
  //Setup the button pins as INPUT
  pinMode(btnPin1, INPUT);
  pinMode(btnPin2, INPUT);
  pinMode(btnPin3, INPUT);
  pinMode(btnPin4, INPUT);
  
  //Setup the LED pins as OUTPUT
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  //Setup the LCD
  lcd.begin(16, 2);            //16 characters on 2 lines
  lcd.print("Hello CMHK :)");  //say hello
  lcd.setCursor(0,1);
  lcd.print("Standalone Demo");    //Name of this script
  delay(1000);
  lcd.clear();
  lcd.print("Hello :)");
}

//The loop
void loop() {
  // Read the values of the buttons
  btn1 = digitalRead(btnPin1);
  btn2 = digitalRead(btnPin2);
  btn3 = digitalRead(btnPin3);
  btn4 = digitalRead(btnPin4);
  
  // Read the values of the Light Resistive Diodes
  lrd1 = analogRead(lrdPin1);
  lrd2 = analogRead(lrdPin2);
  lrd3 = analogRead(lrdPin3);

  // Read the values of the Potentiometer
  pot1 = analogRead(potPin1);

  // set the brightness of LED
  analogWrite(ledR, map(lrd1,0,1024,255,0));
  analogWrite(ledG, map(lrd2,0,1024,255,0));
  analogWrite(ledB, map(lrd3,0,1024,255,0));
  
  //Display status on LCD
  displayOnLCD();
  
  // Check if all 4 buttons are pressed, then play tone
  if (btn1 == 1 && btn2 == 1 && btn3 == 1 && btn4 == 1){
     playNotes(); 
  }
  delay(100);
} // End of the Loop


// The code that plays the tone
void playNotes(){
  // notes in the melody:
  int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  };
  
  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };
  
  // Use a "for loop" to go through the melody note by note
  for (int thisNote = 0; thisNote < 8; thisNote++) {
  
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
    }
}

void displayOnLCD(){    
  // Display the values of buttons
  lcd.setCursor (9,0);
  lcd.print(btn1);
  
  lcd.setCursor (11,0);
  lcd.print(btn2);
  
  lcd.setCursor (13,0);
  lcd.print(btn3);
  
  lcd.setCursor (15,0);
  lcd.print(btn4);
  
  // Display the values of LRD
  lcd.setCursor (5,1);
  if (lrd1 < 100) lcd.print(" ");     // If the number is smaller than 100 we add a space
  if (lrd1 < 10) lcd.print(" ");      // If the number is smaller than 10 we add a space
  lcd.print(lrd1);
  
  lcd.setCursor (9,1);
  if (lrd2 < 100) lcd.print(" ");     // If the number is smaller than 100 we add a space
  if (lrd2 < 10) lcd.print(" ");      // If the number is smaller than 10 we add a space
  lcd.print(lrd2);
  
  lcd.setCursor (13,1);
  if (lrd3 < 100) lcd.print(" ");     // If the number is smaller than 100 we add a space
  if (lrd3 < 10) lcd.print(" ");      // If the number is smaller than 10 we add a space
  lcd.print(lrd3);   
  
  // Display the values of potentiometer
  lcd.setCursor (0,1);
  if (pot1 < 1000) lcd.print(" ");    // If the number is smaller than 1000 we add a space
  if (pot1 < 100) lcd.print(" ");     // If the number is smaller than 100 we add a space
  if (pot1 < 10) lcd.print(" ");      // If the number is smaller than 10 we add a space
  lcd.print(pot1);
  
}
