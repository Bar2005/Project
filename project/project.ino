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
#define echoPin 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 5 //attach pin D3 Arduino to pin Trig of HC-SR04
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int rightMotorPwmPin;
int rightMotorDirectionPin;
int leftMotorPwmPin;
int leftMotorDirectionPin;
int rightMotorPower;
int leftMotorPower;
double xVal = RemoteXY.joystick_1_x;
double yVal = RemoteXY.joystick_1_y;

void setup() 
{
  RemoteXY_Init (); 
  motorsInit (rightMotorPwmPin, rightMotorDirectionPin, leftMotorPwmPin, leftMotorDirectionPin);
  ultrasonicInit ();
  Serial.begin(9600);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  updatemotorPower();            //Finds the right values of power to the right and the left motors
  updateDirection ();            //Finds the right Direction for each motor
      map(rightMotorPower, 0, 100, 0, 255);      //Make the values found above prportional
      map(leftMotorPower, 0, 100, 0, 255);       //Make the values found above prportional
       analogWrite (rightMotorPwmPin, rightMotorPower);
       analogWrite (leftMotorPwmPin, leftMotorPower);
  Serial.println (RemoteXY.joystick_1_x , RemoteXY.joystick_1_y);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 
  //TODO why cant I call delay ()? how can I fix this?

}

void motorsInit (int RightMotorPwmPin, int RightMotorDirectionPin, int LeftMotorPwmPin, int LeftMotorDirectionPin){
  pinMode ( RightMotorPwmPin, OUTPUT);
  pinMode ( RightMotorDirectionPin, OUTPUT);
  pinMode ( LeftMotorPwmPin, OUTPUT);
  pinMode ( LeftMotorDirectionPin, OUTPUT);
  }
  void updatemotorPower (){
     if ( -10 < xVal < 10) {
    rightMotorPower = abs(yVal);
    leftMotorPower = abs(yVal);
    } else if (xVal >= 10) {
    rightMotorPower = abs(yVal/2);
    leftMotorPower = abs(yVal);
    } else if (xVal <= -10) {
    rightMotorPower = abs(yVal);
    leftMotorPower = abs(yVal/2); 
        } 
    }
    void updateDirection (){
      if (yVal > 0) {
      digitalWrite (rightMotorDirectionPin, 1);
      digitalWrite (leftMotorDirectionPin, 1);
      } else if (yVal < 0) {
        digitalWrite (rightMotorDirectionPin, -1);
        digitalWrite (leftMotorDirectionPin, -1);
        }
      }
      



void ultrasonicInit (){
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.println("Ultrasonic initialize");
}
double ultrasonicValue() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
