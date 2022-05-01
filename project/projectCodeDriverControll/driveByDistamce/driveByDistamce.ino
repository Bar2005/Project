double tickesPerRevolution = 22;
const float Pi = 3.14159;
double wheelPerimeter = 2 * Pi * 5;
int wantedDistance = 200;
int rightMotorPwmPin = 10;
int rightMotorDirPin = 11;
int leftMotorPwmPin =  6;
int leftMotorDirPin = 5;
int encoderPin = 13;
double rightMotorPower;
double leftMotorPower;
double turnSpeed = 30;
double driveStraightSpeed = 255;
bool encoderState;
bool lastEncoderState;
double duration;
double encoderVal = 0;

int motors [4] = {rightMotorPwmPin, rightMotorDirPin, leftMotorPwmPin, leftMotorDirPin}; // an array includes all the pins that connected to the motors


void setup() {
  rightMotorPower = driveStraightSpeed;
  leftMotorPower = driveStraightSpeed;
  for (int i = 0; i < 5; i++){
    pinMode (motors[i], OUTPUT);
    }
  analogWrite (motors[0], driveStraightSpeed);
  analogWrite (motors[2], driveStraightSpeed);
  pinMode (encoderPin ,INPUT);  
  digitalWrite (motors[3], 1);
  digitalWrite (motors[1], 0);
  Serial.begin (9600);

}

void loop() {
  
  analogWrite (motors[0], driveStraightSpeed);
  analogWrite (motors[2], driveStraightSpeed);
  bool encoderState = digitalRead (encoderPin);
  if (encoderState == !lastEncoderState){encoderVal++;}
  lastEncoderState = encoderState;
  duration = (encoderVal / tickesPerRevolution) * wheelPerimeter;
  if (duration > 0 && duration < 0.2 * wantedDistance){
    driveStraightSpeed = ((400 * duration)/ wantedDistance) + 70;
    Serial.println ("start");
    }
  else if (duration > 0.2 * wantedDistance && duration < 0.6 * wantedDistance){
    driveStraightSpeed = 150;
    Serial.println ("middle");
    }
  else if (duration > 0.6 * wantedDistance && duration <  wantedDistance){
    driveStraightSpeed = ((-200 * duration)/ wantedDistance) + 70;
    Serial.println ("end");
    }
  else if (duration >  wantedDistance){driveStraightSpeed = 0;}
  analogWrite (motors[0], driveStraightSpeed);
  analogWrite (motors[2], driveStraightSpeed);
}
