/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 4
#define REMOTEXY_SERIAL_TX 5
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 27 bytes
  { 255,1,0,0,0,20,0,16,16,1,2,0,21,40,22,11,2,26,31,31,
  79,78,0,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

bool drive = true;
long durationRight; // variable for the duration of right sound wave travel
long durationLeft; // variable for the duration of left sound wave travel
int trigPinRight = 1;
int echoPinRight = 2;
int trigPinLeft = 3;
int echoPinLeft = 4;
int rightMotorPwmPin = 10;
int rightMotorDirPin = 11;
int leftMotorPwmPin =  12;
int leftMotorDirPin = 13;
double rightMotorPower;
double leftMotorPower;
double turnSpeed = 60;
double rightDistance;
double leftDistance;
int motors [4] = {rightMotorPwmPin, rightMotorDirPin, leftMotorPwmPin, leftMotorDirPin}; // an array includes all the pins that connected to the motors

void setup() 
{
  RemoteXY_Init (); 
  for (int i = 0; i < 5; i++){
    pinMode (motors[i], OUTPUT);
    }
    pinMode (echoPinLeft, INPUT);
    pinMode (echoPinRight, INPUT);
    pinMode (trigPinLeft, OUTPUT);
    pinMode (trigPinRight, OUTPUT);
    digitalWrite (motors[1], 0);
    digitalWrite (motors[3], 0);

    // just initializing
}

void loop() 
{ 
  RemoteXY_Handler ();
  while (drive){
    findRightDistance();
    findLeftDistance();
    if (rightDistance < 100 || leftDistance < 100){
      if (rightDistance > leftDistance){ turn (false);}
      if (rightDistance < leftDistance){ turn (true);}
      else {
    analogWrite (motors[0], 0);
    analogWrite (motors[2], 0);
        }
        // either stop or turn in order to be vertical to the wall
      }
    if (RemoteXY.switch_1){drive = false;} // in case something goes wrong, we can always turn off the car from our phone
    }
    analogWrite (motors[0], 0);
    analogWrite (motors[2], 0);
}
void turn (bool directionToMove){
  int currentTime = millis();
  analogWrite (motors[0], turnSpeed);
  analogWrite (motors[2], turnSpeed);
  if (directionToMove){
    while (leftDistance > rightDistance){
      digitalWrite (motors[1], 0);
      digitalWrite (motors[3], 1);
      }
    }
  if (!directionToMove){
    while(leftDistance < rightDistance){
    digitalWrite (motors[1], 1);
    digitalWrite (motors[3], 0);
    }
    }
  }
  void findRightDistance (){
    // Clears the trigPin condition
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationRight = pulseIn(echoPinRight, HIGH);
  // Calculating the distance
  rightDistance = durationRight* 0.034 / 2;
  }
  void findLeftDistance (){
    // Clears the trigPin condition
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationLeft = pulseIn(echoPinLeft, HIGH);
  // Calculating the distance
  leftDistance = durationLeft * 0.034 / 2;
  }
