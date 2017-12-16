//initialize and declare variables
const int ledPin1 = 11; //led attached to this pin
const int buttonPin1 = 7; //push button attached to this pin
 
int buttonState1 = LOW; //this variable tracks the state of the button, low if not pressed, high if pressed
int ledState1 = -1; //this variable tracks the state of the LED, negative if off, positive if on
 
long lastDebounceTime1 = 0;  // the last time the output pin was toggled

//===========================================================================================================

const int ledPin2 = 12; //led attached to this pin
const int buttonPin2 = 6; //push button attached to this pin
 
int buttonState2 = LOW; //this variable tracks the state of the button, low if not pressed, high if pressed
int ledState2 = -1; //this variable tracks the state of the LED, negative if off, positive if on
 
long lastDebounceTime2 = 0;  // the last time the output pin was toggled
long debounceDelay = 200;    // the debounce time; increase if the output flickers
 
void setup() {
 
  //set the mode of the pins...
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin1, INPUT);
 
}//close void setup
 
 
void loop() {
 
  //sample the state of the button - is it pressed or not?
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
 
  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime1) > debounceDelay) {
 
    //if the button has been pressed, lets toggle the LED from "off to on" or "on to off"
    if ( (buttonState1 == HIGH) && (ledState1 < 0) ) {
 
      digitalWrite(ledPin1, HIGH); //turn LED on
      ledState1 = -ledState1; //now the LED is on, we need to change the state
      lastDebounceTime1 = millis(); //set the current time
    }
    else if ( (buttonState1 == HIGH) && (ledState1 > 0) ) {
 
      digitalWrite(ledPin1, LOW); //turn LED off
      ledState1 = -ledState1; //now the LED is off, we need to change the state
      lastDebounceTime1 = millis(); //set the current time
    }//close if/else
 
  }//close if(time buffer)
}
