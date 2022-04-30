

long durationRight; // variable for the duration of right sound wave travel
long durationLeft; // variable for the duration of left sound wave travel
int trigPinRight = 1;
int echoPinRight = 2;
int trigPinLeft = 3;
int echoPinLeft = 4;
int rightMotorPwmPin = 10;
int rightMotorDirPin = 11;
int leftMotorPwmPin =  5;
int leftMotorDirPin = 6;
double rightMotorPower;
double leftMotorPower;
double turnSpeed = 30;
double driveStraightSpeed = 40;
double rightDistance;
double leftDistance;
int motors [4] = {rightMotorPwmPin, rightMotorDirPin, leftMotorPwmPin, leftMotorDirPin}; // an array includes all the pins that connected to the motors

void setup() 
{
  for (int i = 0; i < 5; i++){
    pinMode (motors[i], OUTPUT);
    }
    pinMode (echoPinLeft, INPUT);
    pinMode (echoPinRight, INPUT);
    pinMode (trigPinLeft, OUTPUT);
    pinMode (trigPinRight, OUTPUT);
    digitalWrite (motors[1], 0);
    digitalWrite (motors[3], 1);
    Serial.begin (9600);
    driveStraightSpeed = 40;
    // just initializing
}

void loop() 
{ 
    rightDistance = 90;
    leftDistance = 90;
    analogWrite (motors[0], driveStraightSpeed);
    analogWrite (motors[2], driveStraightSpeed);
    if (rightDistance < 100 || leftDistance < 100){
      if (rightDistance > leftDistance){ 
        Serial.println ("left");
        turn (false);
        }
      if (rightDistance < leftDistance){ 
        Serial.println ("right");
        turn (true);
        }
      else {
driveStraightSpeed = 0;
        } 
        // either stop or turn in order to be vertical to the wall
      } 
    
}
void turn (bool directionToMove){
  int currentTime = millis();
  analogWrite (motors[0], turnSpeed);
  analogWrite (motors[2], turnSpeed);
  if (directionToMove){
    while (leftDistance > rightDistance){
      findRightDistance();
      findLeftDistance();
      digitalWrite (motors[1], 0);
      digitalWrite (motors[3], 0);
      }
    }
  if (!directionToMove){
    while(leftDistance < rightDistance){
    findRightDistance();
    findLeftDistance();
    digitalWrite (motors[1], 1);
    digitalWrite (motors[3], 1);
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
