#include "Arduino.h"
#include "CarMovement.h"

#define LEFT 5
#define RIGHT 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

char currentDirection = 'X';
int currentMotorSpeedInPercent = 0;
int currentAngle = 0;

void CarMovement::PrintStatus() {
  Serial.print("MotorStatus: \t\t");
  Serial.print("Direction: ");
  Serial.print(currentDirection);
  Serial.print("\tCurrentSpeed: ");
  Serial.print(currentMotorSpeedInPercent);
  Serial.print("\tCurrentAngle: ");
  Serial.println(currentAngle);  
}

void CarMovement::Initialize() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LEFT, OUTPUT);
}

void CarMovement::Forward(){ 
  if (currentDirection == 'F')
    return;

  digitalWrite(IN1,HIGH); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 hight level
#ifdef DEBUG
  Serial.println("Forward");//send message to serial monitor
#endif
  currentDirection = 'F';
  SetSpeedBoth(currentMotorSpeedInPercent);
}

void CarMovement::Backward(){
  if (currentDirection == 'B')
    return;

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

#ifdef DEBUG
  Serial.println("Back");
#endif
  currentDirection = 'B';
  SetSpeedBoth(currentMotorSpeedInPercent);
}

void CarMovement::Left(){
  if (currentDirection == 'A')
    return;

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  
#ifdef DEBUG
  Serial.println("Left");
#endif
  currentDirection = 'A';
  SetSpeedBoth(currentMotorSpeedInPercent);
}

void CarMovement::Right(){
  if (currentDirection == 'D')
    return;

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  
#ifdef DEBUG
  Serial.println("Right");
#endif
  currentDirection = 'D';
  SetSpeedBoth(currentMotorSpeedInPercent);
}

void CarMovement::SetSpeedBoth(int speedInPercent)
{ 
  if (speedInPercent == currentMotorSpeedInPercent)
    return;
  
  currentMotorSpeedInPercent = speedInPercent; 
  currentAngle = 0;
  
#ifdef DEBUG
  Serial.print("Set Motor Speed to: ");
  Serial.println(currentMotorSpeedInPercent);
#endif
  SetEnginge(RIGHT, currentMotorSpeedInPercent);
  SetEnginge(LEFT, currentMotorSpeedInPercent);
}

void CarMovement::Accelerate()
{
  if (currentMotorSpeedInPercent >= 100)
    return;

  currentMotorSpeedInPercent += 5;
  SetSpeedBoth(currentMotorSpeedInPercent);
}

void CarMovement::Brake()
{
  if (currentMotorSpeedInPercent <= 0)
    return;

  currentMotorSpeedInPercent -= 5;
  SetSpeedBoth(currentMotorSpeedInPercent);
}

void CarMovement::FullGas()
{  
  SetSpeedBoth(100);
}

void CarMovement::FullStop()
{  
  digitalWrite(IN1,LOW); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,LOW); //set IN4 hight level

  SetSpeedBoth(0);
  currentDirection = 'X';
  Serial.println("Emergency Brake");
}

void CarMovement::MoreRight()
{
  if (currentDirection == 'E')
  {
    if (currentAngle <= 100)
      currentAngle += 5; 
  }
  else {
    SetSpeedBoth(currentMotorSpeedInPercent);
    currentDirection = 'E';
    currentAngle = 5;
  }
  SetEnginge(LEFT, currentMotorSpeedInPercent - currentAngle);
  SetEnginge(RIGHT, currentMotorSpeedInPercent + currentAngle);
  
#ifdef DEBUG
  Serial.print("Set more Right: ");
  Serial.println(currentAngle);
#endif
}

void CarMovement::MoreLeft()
{
  
  if (currentDirection == 'Q')
  {
    if (currentAngle <= 100)
      currentAngle += 5; 
  }
  else {
    SetSpeedBoth(currentMotorSpeedInPercent);
    currentDirection = 'Q';
    currentAngle = 5;
  }
  SetEnginge(LEFT, currentMotorSpeedInPercent + currentAngle);
  SetEnginge(RIGHT, currentMotorSpeedInPercent - currentAngle);
  
#ifdef DEBUG
  Serial.print("Set more LEFT: ");
  Serial.println(currentAngle);
#endif
}

void CarMovement::SetEnginge(int motor, int speedInPercent)
{
  int speedToWrite = GetDrivingValue(speedInPercent);
  analogWrite(motor, speedToWrite);
}

int CarMovement::GetDrivingValue(int speedInPercent)
{
  return map(speedInPercent, 0, 100, 0, 255);;
}

