#include <SoftwareSerial.h>
SoftwareSerial espSerial(11, 12);
const int pingPin = 2;
const int echoPin = 3;
long duration;
int distance;


#define IR_SENSOR_RIGHT 4
#define IR_SENSOR_LEFT 13
#define MOTOR_SPEED 200

//Right motor
int enableRightMotor=10;
int rightMotorPin1=9;
int rightMotorPin2=8;

//Left motor
int enableLeftMotor=5;
int leftMotorPin1=7;
int leftMotorPin2=6;

void setup()
{
  pinMode(pingPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);
  Serial.begin(9600);   
  espSerial.begin(9600); 
}


void loop()
{

  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  String str1=String("distance:= ")+String(cm);
espSerial.println(str1);

if(cm < 25)
{
 rotateMotor(0, 0);
  
}

  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  //If none of the sensors detects black line, then go straight
  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
  {
     if(cm > 25)
     {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
     }
  }
  //If right sensor detects black line, then turn right
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW )
  {
      rotateMotor(MOTOR_SPEED, -MOTOR_SPEED); 
  }
  //If left sensor detects black line, then turn left  
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH )
  {
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED); 
  } 
  //If both the sensors detect black line, then stop 
  else 
  {
    rotateMotor(0, 0);
  }

 

}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}


long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
