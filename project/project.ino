/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.7 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.9.02 or later version;
     - for iOS 1.6.2 or later version;
    
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
uint8_t RemoteXY_CONF[] =
  { 255,2,0,0,0,12,0,14,31,1,
  5,0,18,27,30,30,2,26,31 };
  
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

int rightMotorPwmPin;
int rightMotorDirectionPin;
int leftMotorPwmPin;
int leftMotorDirectionPin;
double xVal = RemoteXY.joystick_1_x;
double yVal = RemoteXY.joystick_1_y;

void setup() 
{
  RemoteXY_Init (); 
  motorsInit (rightMotorPwmPin, rightMotorDirectionPin, leftMotorPwmPin, leftMotorDirectionPin);
  Serial.begin(9600);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  Serial.println (RemoteXY.joystick_1_x , RemoteXY.joystick_1_y);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}

void motorsInit (int RightMotorPwmPin, int RightMotorDirectionPin, int LeftMotorPwmPin, int LeftMotorDirectionPin){
  pinMode ( Motor_1_PwmPin, OUTPUT);
  pinMode ( Motor_1_DirectionPin, OUTPUT);
  pinMode ( Motor_2_PwmPin, OUTPUT);
  pinMode ( Motor_2_DirectionPin, OUTPUT);
  }
