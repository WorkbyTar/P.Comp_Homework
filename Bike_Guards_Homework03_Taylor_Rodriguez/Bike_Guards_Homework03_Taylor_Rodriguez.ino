/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int ledButtonPin1 = 2;  //right
const int ledButtonPin2 = 5; //head
const int ledButtonPin3 = 4; //left
const int buzzerButtonPin = 3; //buzz
//// the number of the pushbutton pin
const int ledPin1 =  10;  
const int ledPin2 =  13;
const int ledPin3 =  12; // the number of the LED pin

const int buzzerPin = 11;

// variables will change:
int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW; 

int ledButtonState1 = 0;    
int ledButtonState2 = 0;
int ledButtonState3 = 0;

int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;
int lastButtonState3 = HIGH; 

int buzzerButtonState = 0;

long lastDebounceTime1 = 0;
long debounceDelay1 = 50;

long lastDebounceTime2 = 0;
long debounceDelay2 = 50;

long lastDebounceTime3 = 0;
long debounceDelay3 = 50;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
//  
  // initialize the pushbutton pin as an input:

  pinMode(ledButtonPin1, INPUT);
  pinMode(ledButtonPin2, INPUT);
  pinMode(ledButtonPin3, INPUT);
  pinMode(buzzerButtonPin, INPUT);

  digitalWrite(ledPin1,ledState1);
  digitalWrite(ledPin2,ledState2);
  digitalWrite(ledPin3,ledState3);
}

void loop() {
  // read the state of the pushbutton value:

  int reading1 = digitalRead(ledButtonPin1);
  int reading2 = digitalRead(ledButtonPin2);
  int reading3 = digitalRead(ledButtonPin3);

buzzerButtonState = digitalRead(buzzerButtonPin);

if (buzzerButtonState == HIGH) {

digitalWrite(buzzerPin, HIGH);
} else {

digitalWrite(buzzerPin, LOW);
}

//1
 
  if (reading1 != lastButtonState1) {
    // turn LED on:
    lastDebounceTime1 = millis();
  } 

  if ((millis() - lastDebounceTime1) > debounceDelay1 ){
    
    if (reading1 != ledButtonState1){
      ledButtonState1 = reading1;

      if (ledButtonState1 == HIGH){
        ledState1 = !ledState1;
      }
    }
  }
  
  digitalWrite(ledPin1, ledState1);
  lastButtonState1 = reading1; 
//2
  
 if (reading2 != lastButtonState2) {
    // turn LED on:
    lastDebounceTime2 = millis();
  } 

  if ((millis() - lastDebounceTime2) > debounceDelay2 ){
    
    if (reading2 != ledButtonState2){
      ledButtonState2 = reading2;

      if (ledButtonState2 == HIGH){
        ledState2 = !ledState2;
      }
    }
  }
  
  digitalWrite(ledPin2, ledState2);
  lastButtonState2 = reading2; 
 
  
//3
        
  if (reading3 != lastButtonState3) {
    // turn LED on:
    lastDebounceTime3 = millis();
  } 

  if ((millis() - lastDebounceTime3) > debounceDelay3 ){
    
    if (reading3 != ledButtonState3){
      ledButtonState3 = reading3;

      if (ledButtonState3 == HIGH){
        ledState3 = !ledState3;
      }
    }
  }
  
  digitalWrite(ledPin3, ledState3);
  lastButtonState3 = reading3; 



   }

