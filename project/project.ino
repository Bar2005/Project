/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.7 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.10.2 or later version;
     - for iOS 1.8.2 or later version;
    
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
uint8_t RemoteXY_CONF[] =
  { 255,2,0,0,0,12,0,15,31,1,
  5,0,14,34,30,30,2,26,31 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_1_x; // =-100..100 x-coordinate joystick position 
  int8_t joystick_1_y; // =-100..100 y-coordinate joystick position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
int rightMotorPwmPin = 10;
int rightMotorDirPin = 11;
int leftMotorPwmPin =  12;
int leftMotorDirPin = 13;
double rightMotorPower;
double leftMotorPower;
double turnSpeed = 120;
double driveStraightSpeed = 200;

void setup() 
{
  RemoteXY_Init (); 
  Serial.begin (9600);
  pinMode(rightMotorPwmPin, OUTPUT);
  pinMode(rightMotorDirPin, OUTPUT);
  pinMode(leftMotorPwmPin, OUTPUT);
  pinMode(leftMotorDirPin, OUTPUT);
}

void loop() 
{ 
  RemoteXY_Handler();
  int xVal = RemoteXY.joystick_1_x;
  int yVal = RemoteXY.joystick_1_y;
  if ( -10 < xVal < 10 && -10 < yVal < 10) {
    rightMotorPower = 0;
    leftMotorPower = 0;
    Serial.println ("stop");
    } else {
    rightMotorPower = turnSpeed;
    leftMotorPower = turnSpeed;
      } 
    // deciding whether to stop the car or drive 
    
    if (xVal > 10 && yVal > 0) {
    digitalWrite (leftMotorDirPin, 0);
    digitalWrite (rightMotorDirPin, 1);
    Serial.println ("turn right");
    } else if (xVal < -10 && yVal > 0) { 
    digitalWrite (rightMotorDirPin, 0);
    digitalWrite (leftMotorDirPin, 1);
    Serial.println ("turn left");
    }  else {
    rightMotorPower = driveStraightSpeed;
    leftMotorPower = driveStraightSpeed;
    }  if (-10 < xVal < 10 && yVal > 10){
    digitalWrite (leftMotorDirPin, 0);
    digitalWrite (rightMotorDirPin, 0);
    Serial.println("forward");  
    } else if (-10 < xVal < 10 && yVal < -10){
    digitalWrite (leftMotorDirPin, 1);
    digitalWrite (rightMotorDirPin, 1);
    Serial.println("backward");
      } 
  // deciding which side every motor needs to move    
  analogWrite (rightMotorPwmPin, rightMotorPower);
  analogWrite (leftMotorPwmPin, leftMotorPower);
  // actually moving the motors
  // do not call delay() 
}
