#include <ZumoMotors.h>
#include <QTRSensors.h>
unsigned char SENSORS[] = {4, A3, 11, A0, A2, 5};
const int NUM_SENSORS = sizeof(SENSORS);
const int TIMEOUT = 2000;  // waits for 2500 microseconds for sensor outputs to go low
const int EMITTER_PIN = 2;     // emitter is controlled by digital pin 2
const int SENSOR_LEFT_OUTER = 0;
const int SENSOR_RIGHT_OUTER = 5;
 
const int WHITE_THRESHHOLD = 700;
const int BLACK_THRESHHOLD = 2000;
 
const int SPEED = 300;
ZumoMotors motors;
QTRSensorsRC qtrrc(SENSORS, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void spinRight(int randNumber)
{
   motors.setSpeeds(SPEED, -SPEED);
   delay(0.01);
}
void spinLeft(int randNumber)
{
   motors.setSpeeds(-SPEED, SPEED);
   delay(0.01);
}
void goForward()
{
   motors.setSpeeds(SPEED, SPEED);
   delay(0.01);
}
void goBackward(int randNumber)
{
     motors.setSpeeds(-SPEED, -SPEED);
   delay(0.01);
}

int getSensorReading(int sensor)
{
 updateSensorValues();
 return sensorValues[sensor];
}
void updateSensorValues()
{
 qtrrc.read(sensorValues);
}

void setup()
{
 Serial.begin(115200);
 Serial.print("Motors on \n");
 motors.setSpeeds(SPEED, SPEED);
}

void loop() {
 
 int randNumber = random(100, 400);
 int randNumber2 = random(-400, 400);
 int randNumber3 = random(1000, 2000);
 updateSensorValues();
 int leftSensor = sensorValues[SENSOR_LEFT_OUTER];
 int rightSensor = sensorValues[SENSOR_RIGHT_OUTER];

 int leftSensorValue = getSensorReading(SENSOR_LEFT_OUTER);
 int rightSensorValue = getSensorReading(SENSOR_RIGHT_OUTER);

 if (leftSensorValue < WHITE_THRESHHOLD && rightSensorValue < WHITE_THRESHHOLD)
 {
    goBackward(SPEED);
    delay (1000);
    spinRight(SPEED);
    delay (randNumber3);
    goForward();
 }
 
 if (rightSensorValue < WHITE_THRESHHOLD && rightSensorValue < WHITE_THRESHHOLD)
 {
    goBackward(SPEED);
    delay (1000);
    spinLeft(SPEED);
    delay (randNumber3);
    goForward();
    
 }


// Add moving logic with light sensor values
 
}


