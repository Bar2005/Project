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
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 95 bytes
  { 255,5,0,0,0,88,0,16,31,1,2,0,37,79,22,11,2,26,31,31,
  79,78,0,79,70,70,0,10,48,6,35,15,15,4,26,31,79,78,0,31,
  79,70,70,0,10,48,23,52,15,15,4,26,31,79,78,0,31,79,70,70,
  0,10,48,40,35,15,15,4,26,31,79,78,0,31,79,70,70,0,10,48,
  23,18,15,15,4,26,31,79,78,0,31,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t pushSwitch_1; // =1 if state is ON, else =0 
  uint8_t pushSwitch_2; // =1 if state is ON, else =0 
  uint8_t pushSwitch_3; // =1 if state is ON, else =0 
  uint8_t pushSwitch_4; // =1 if state is ON, else =0 

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
bool drive = true;
double turnSpeed = 60;
double driveStraightSpeed = 100;
int motors [4] = {rightMotorPwmPin, rightMotorDirPin, leftMotorPwmPin, leftMotorDirPin}; // an array includes all the pins that connected to the motors


void setup() 
{
  RemoteXY_Init (); 
  rightMotorPower = driveStraightSpeed;
  leftMotorPower = driveStraightSpeed;
  for (int i = 0; i < 5; i++){
    pinMode (motors[i], OUTPUT);
    }
  Serial.begin (9600);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler (); 
  if (RemoteXY.switch_1){
  RemoteXY_Handler (); 
  rightMotorPower = turnSpeed;
  leftMotorPower = turnSpeed;
    if (RemoteXY.pushSwitch_3){
    digitalWrite (motors[3], 0);
    digitalWrite (motors[1], 1);
    Serial.println ("turn right");
    } else if (RemoteXY.pushSwitch_1) { 
    digitalWrite (motors[1], 0);
    digitalWrite (motors[3], 1);
    Serial.println ("turn left");
    }  else {
    rightMotorPower = driveStraightSpeed;
    leftMotorPower = driveStraightSpeed;
    } 
    if (RemoteXY.pushSwitch_4){
    digitalWrite (motors[3], 0);
    digitalWrite (motors[1], 0);
    Serial.println("forward");  
    } else if (RemoteXY.pushSwitch_2){
    digitalWrite (motors[3], 1);
    digitalWrite (motors[1], 1);
    Serial.println("backward");
      } 
    if (!RemoteXY.pushSwitch_1 && !RemoteXY.pushSwitch_2 && !RemoteXY.pushSwitch_3 && !RemoteXY.pushSwitch_4){
  leftMotorPower = 0;
  rightMotorPower = 0;
  Serial.println ("stop!!");
      }  
  // deciding which side every motor needs to move    
  analogWrite (motors[0], rightMotorPower);
  analogWrite (motors[2], leftMotorPower);
  // actually moving the motors
  // do not call delay() 
  } else {
  analogWrite (motors[0], 0);
  analogWrite (motors[2], 0);
  Serial.println ("stop");
  }
}
