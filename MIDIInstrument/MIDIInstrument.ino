/*
  Sound and Technology Workshop
  Session2
  2015-05-02
  Public Domain
  
  This script is a MIDI instrument.
  Btn 1,2,3 turn on the 3 notes.
  Pot adjusts the speed
  4th button is mute
  Code and PCB layout on http://morgan.isnot.in/CMHK/ElectronicsWorkshop

*/
#include <LiquidCrystal.h>
#include <MIDI.h>

//Create the MIDI instrument
MIDI_CREATE_DEFAULT_INSTANCE();

//Hold the LED pins
const int ledR = 9;         // the pin that the Red LED is attached to
const int ledG = 10;        // the pin that the Green LED is attached to
const int ledB = 11;        // the pin that the Blue LED is attached to

//Hold data for buttons
int btn1, btn2, btn3, btn4;
bool btnStatus1 = false;
bool btnStatus2 = false;
bool btnStatus3 = false;
bool btnStatus4 = false;
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
  //Setup the MIDI Instrument
  MIDI.begin(4);          // Launch MIDI and listen to channel 4
  Serial.begin(115200);   // Setup the MIDI Instrument on Serial
  
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
  lcd.print("MIDI Instrument");    //Name of this script
  delay(1000);                     //Give us enough time to say hello
  lcd.clear();
}

//The loop
void loop() {
  // Read the values of the buttons
  btn1 = digitalRead(btnPin1);
  btn2 = digitalRead(btnPin2);
  btn3 = digitalRead(btnPin3);
  btn4 = digitalRead(btnPin4);
  
  // Actions for button presses
  if (btn1){
    //Flip the button status
    btnStatus1 = !btnStatus1;
  }
  if (btn2){
    //Flip the button status
    btnStatus2 = !btnStatus2;
  }
  if (btn3){
    //Flip the button status
    btnStatus3 = !btnStatus3;
  }
  if (btn4){
    // Mute Everything
    btnStatus1 = false;
    btnStatus2 = false;
    btnStatus3 = false;
  }

  // Read the values of the Light Resistive Diodes
  lrd1 = analogRead(lrdPin1);
  lrd2 = analogRead(lrdPin2);
  lrd3 = analogRead(lrdPin3);
  
  // Read the values of the Potentiometer
  pot1 = analogRead(potPin1);

  // set the brightness of RGB LED
  analogWrite(ledR, map(lrd1,0,1024,255,0));
  analogWrite(ledG, map(lrd2,0,1024,255,0));
  analogWrite(ledB, map(lrd3,0,1024,255,0));
  
  //Display Status on LCD
  displayOnLCD();
  
  //Play Midi Notes  
  if (btnStatus1){
    MIDI.sendNoteOn(map(lrd1,0,1024, 30, 100),125,1);  // Send a Note scaled from 0-1024 to 30-100, 125 velocity on channel 1
  }
  if (btnStatus2){
    MIDI.sendNoteOn(map(lrd2,0,1024, 30, 100),125,1);  // Send a Note scaled from 0-1024 to 30-100, 125 velocity on channel 1
  }
  if (btnStatus3){
    MIDI.sendNoteOn(map(lrd3,0,1024, 30, 100),125,1);  // Send a Note scaled from 0-1024 to 30-100, 125 velocity on channel 1
  }
  delay(map(pot1,0,1024, 0, 800));		        // Wait for delay based on pot
  
  // Turn Off LED
  analogWrite(ledR, 255);
  analogWrite(ledG, 255);
  analogWrite(ledB, 255);
  
  if (btnStatus1){
    MIDI.sendNoteOff(map(lrd1,0,1024, 30, 100),0,1);   // Stop the note
  }
  if (btnStatus2){
  MIDI.sendNoteOff(map(lrd2,0,1024, 30, 100),0,1);   // Stop the note
  }
  if (btnStatus3){
  MIDI.sendNoteOff(map(lrd3,0,1024, 30, 100),0,1);   // Stop the note
  }
  
  //Delay the loop
  delay(map(pot1,0,1024, 0, 800));
    
} // End of the Loop


void displayOnLCD(){    
  // Display the values of buttons
  lcd.setCursor (0,0);
  lcd.print("Note:"); // Note the extra spaces to erase other text
  
  lcd.setCursor (5,0);
  if(btnStatus1){
    lcd.print(" ON");
  }else{
    lcd.print("OFF");
  }
  
  lcd.setCursor (9,0);
  if(btnStatus2){
    lcd.print(" ON");
  }else{
    lcd.print("OFF");
  }
  
  lcd.setCursor (13,0);
  if(btnStatus3){
    lcd.print(" ON");
  }else{
    lcd.print("OFF");
  }
  
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
