#include <Adafruit_RGBLCDShield.h>

#include <Wire.h>

#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

bool zone1 = false;
bool zone2 = false;
bool zone3 = false;
bool autonomous = false;
bool teleop = false;
boolean noObject1 = true;
boolean noObject2= true;
boolean noObject3 = true;
int sensorPin1 = 2;
int sensorPin2 = 3;
int sensorPin3 = 4;
int ledPin=3;

void setup() {
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("Zone1");
lcd.setCursor(0, 1);
lcd.print("Zone2");
lcd.setCursor(9,0);
lcd.print("Zone3");
}

void loop() {

 
  noObject1 = digitalRead(sensorPin1);
  noObject2 = digitalRead(sensorPin2);
  noObject3 = digitalRead(sensorPin3);


  if(noObject1)
  {
  lcd.setCursor(6,0);
  lcd.print("N");
  lcd.setBacklight(0x1);
  Serial.println("Object 1 not detected.");
  
    
  }
  else
  {
    
    Serial.println("Object 1 detected.");
    lcd.setCursor(6,0);
    lcd.print("A");
    lcd.setBacklight(0x3);
    delay(800);
    lcd.setBacklight(0x1);  
    
  }
if(noObject2)
  {
   lcd.setCursor(6,1);
   lcd.print("N");
   lcd.setBacklight(0x1);
   Serial.println("Object 2 not detected.");
  
  }
 else
  {
    Serial.println("Object 2 detected.");
    lcd.setCursor(6,1);
    lcd.print("A");
    lcd.setBacklight(0x3);
    delay(800);
    lcd.setBacklight(0x1);  

  }
if(noObject3) 
  {
   lcd.setCursor(15,0);
   lcd.print("N");
   lcd.setBacklight(0x1);
   Serial.println("Object 2 not detected.");
  }
  else
  {
    Serial.println("Object 3 detected.");
    lcd.setCursor(15,0);
    lcd.print("A");
    lcd.setBacklight(0x3);
    delay(800);
    lcd.setBacklight(0x1);  
  }

if (noObject1 == false && noObject2 == false && noObject3 == false)
{
  lcd.setBacklight(0x3);
}

}

