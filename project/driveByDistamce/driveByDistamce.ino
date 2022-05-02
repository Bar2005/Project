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
double distanceTraveled;
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

//initializing
}

void loop() {
  
  analogWrite (motors[0], driveStraightSpeed);
  analogWrite (motors[2], driveStraightSpeed);
  bool encoderState = digitalRead (encoderPin); // reads the encoder val
  if (encoderState == !lastEncoderState){encoderVal++;}
  lastEncoderState = encoderState;
  distanceTraveled = (encoderVal / tickesPerRevolution) * wheelPerimeter; // what the distance that we have traveled is equal to
  if (distanceTraveled > 0 && distanceTraveled < 0.2 * wantedDistance){
    driveStraightSpeed = ((400 * distanceTraveled)/ wantedDistance) + 70; //just the math itself
    Serial.println ("start");
    }
  else if (distanceTraveled > 0.2 * wantedDistance && distanceTraveled < 0.6 * wantedDistance){
    driveStraightSpeed = 150;
    Serial.println ("middle");
    }
  else if (distanceTraveled > 0.6 * wantedDistance && distanceTraveled <  wantedDistance){
    driveStraightSpeed = ((-200 * distanceTraveled)/ wantedDistance) + 70;
    Serial.println ("end");
    }
  else if (distanceTraveled >  wantedDistance){driveStraightSpeed = 0;} // in case we have past the wanted direction, stop the car!!
  analogWrite (motors[0], driveStraightSpeed);
  analogWrite (motors[2], driveStraightSpeed);
}
