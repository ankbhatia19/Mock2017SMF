const int ledPin = 11; //led attached to this pin
const int buttonPin = 7; //push button attached to this pin
 
int buttonState = LOW; //this variable tracks the state of the button, low if not pressed, high if pressed
int ledState = -1; //this variable tracks the state of the LED, negative if off, positive if on
 
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 200;    // the debounce time; increase if the output flickers

//Servo+Proximity ==========================================================================================

#include <Servo.h>
boolean noObject1 = true;
boolean noObject2 = true;
boolean noObject3 = true;
int sensorPin1 = 2;
int ledPin1 = 5;
int sensorPin2 = 3;
int ledPin2 = 6;
int sensorPin3 = 4;
int ledPin3 = 7;
boolean zone1 = false;
boolean zone2 = false;
boolean zone3 = false;
#define VERTICAL 1
#define HORIZONTAL 2
#define WAG 3
class Timer{
  private:
  int timeDelay;
  
  public:
  Timer()
  {
    timeDelay = 0;  
  }
  int assignDelay()
  {
      timeDelay = random(10000,20000);
      return timeDelay;
  }
};
int arrayNum[3]; 
Servo servo1;
Servo servo2;
Servo servo3;
void vertical(Servo s, unsigned long clockTime)
{
   s.write(90);
}
void horizontal(Servo s, unsigned long clockTime)
{
  s.write(180);
}
void wag(Servo s, unsigned long clockTime)
{
  clockTime += millis();
  while (millis() < clockTime)
  {
    s.write(180);
    delay(1000);
    s.write(0);
    delay(1000);
    s.write(180);
    delay(1000);
    s.write(0);
    delay(1000);   
}
}
void randNum()
{
  int used[3];
  int i;
  arrayNum[0] = random(1,4);
  for (;;)
 {
   arrayNum[1] = random(1,4);
   if (arrayNum[1] != arrayNum[0])
   {
     break;
   }
 }
 
 for (i=0;i<3;i++)used[i]=0;
 used[arrayNum[0]-1]=1;
 used[arrayNum[1]-1]=1;
 for (i=0;i<3;i++)
 {
    if (used[i] == 0)
    {
      arrayNum[2] = i+1;
    }
 }
 Serial.print(arrayNum[0]);
 Serial.print(' ');
 Serial.print(arrayNum[1]);
 Serial.print(' ');
 Serial.println(arrayNum[2]);
 Serial.println("1 = vertical, 2 = horizontal, 3 = spinning");
}
void setMotorState(Servo s, int state, unsigned long clockTime)
{
  if (state == 1) 
  {
    vertical(s, clockTime); 
  }
  if (state == 2)
  {
    
    horizontal(s, clockTime);
  }
}
void setMotorStateWag(Servo s, int state, unsigned long clockTime)
{
  if (state == 3)
  {
    
    wag(s, clockTime);
  }
}

void autonomous()
{
  
}

void teleop()
{
  Timer clock;
   noObject1 = digitalRead(sensorPin1);
  noObject2 = digitalRead(sensorPin2);
  noObject3 = digitalRead(sensorPin3);

  if (noObject1 == false && zone1 )
  {
    Serial.println("Object 1 detected.");
    digitalWrite(ledPin1, HIGH);
  }
  else
  {
    digitalWrite(ledPin1, LOW);
  }
  if (noObject2 == false && zone2)
  {
    Serial.println("Object 2 detected.");
    digitalWrite(ledPin2, HIGH);
  }
  else
  {
    digitalWrite(ledPin2, LOW);
  }
  if (noObject3 == false && zone3)
  {
    Serial.println("Object 3 detected.");
    digitalWrite(ledPin3, HIGH);
  }
  else
  {
    digitalWrite(ledPin3, LOW);
  }
   int clockDelay = clock.assignDelay();
  randomSeed(analogRead(0));
  randNum();
  Serial.println(clockDelay);
  setMotorState(servo1, arrayNum[0], (unsigned long) clockDelay);
  setMotorState(servo2, arrayNum[1], (unsigned long) clockDelay);
  setMotorState(servo3, arrayNum[2], (unsigned long) clockDelay);
  setMotorStateWag(servo1, arrayNum[0], (unsigned long) clockDelay);
  setMotorStateWag(servo2, arrayNum[1], (unsigned long) clockDelay);
  setMotorStateWag(servo3, arrayNum[2], (unsigned long) clockDelay);
  if (arrayNum[0] == 1)
  {
    zone1 = true;
    zone2 = false;
    zone3 = false;
  }
  if (arrayNum[1] == 1)
  {
    zone1 = false;
    zone2 = true;
    zone3 = false;
  }
  if (arrayNum[2] == 1)
  {
    zone1 = false;
    zone2 = false;
    zone3 = true;
  }
}

Timer clock;

void setup() {
 //Servo Prox

 pinMode(sensorPin1, INPUT_PULLUP);
  pinMode(sensorPin2, INPUT_PULLUP);
  pinMode(sensorPin3, INPUT_PULLUP);
  Serial.begin(9600);
   servo1.attach(9);
  servo2.attach(13);
  servo3.attach(10);
  Serial.begin(9600);

  //Button

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // button if else control statements

  //sample the state of the button - is it pressed or not?
  buttonState = digitalRead(buttonPin);
  
 
  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime) > debounceDelay) {
 
    //if the button has been pressed, lets toggle the mode from "auto to teleop" or "teleop to auto"
    if ( (buttonState == HIGH) && (ledState < 0) ) {
 
      digitalWrite(ledPin, HIGH); //turn LED on
      ledState = -ledState; //now the LED is on, we need to change the state
      autonomous();
      lastDebounceTime = millis(); //set the current time
    }
    else if ( (buttonState == HIGH) && (ledState > 0) ) {
 
      digitalWrite(ledPin, LOW); //turn LED off
      ledState = -ledState; //now the LED is off, we need to change the state
      while (true) //mimics void loop
      {
      teleop();
      }
      //once it goes here, I'm not sure whether it can be switched back to auto
      lastDebounceTime = millis(); //set the current time
    }//close if/else
 
  }//close if(time buffer)

}
