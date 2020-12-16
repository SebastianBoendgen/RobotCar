#include <Servo.h>
#include <Arduino.h>
#include <UltraSonic.h>

Servo myservo; // create servo object to control servo
int Echo = A4;
int Trig = A5;
#define SERVOMIN 0
#define SERVOMAX 180
#define SERVOSTEP 1
#define SERVO_OFFSET 0

#define MIN_DISTANCE 5
int servoValue = 90 + SERVO_OFFSET;


void UltraSonic::Initialize()
{
    myservo.attach(3);
    myservo.write(SERVOMIN);
    delay(1000);
    myservo.write(SERVOMAX);
    delay(1000);
    myservo.write(servoValue);
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);
}

int UltraSonic::GetDistance() {
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    return (int)pulseIn(Echo, HIGH) / 58;
}

void UltraSonic::SetServoCenter()
{
    servoValue = 90; setServo();
}

void UltraSonic::SetServoStepLeft()
{
    if (servoValue >= SERVOMAX)
        return;
    
    servoValue += SERVOSTEP; setServo();
}

void UltraSonic::SetServoStepRight()
{
    if (servoValue <= SERVOMIN)
        return;
    
    servoValue -= SERVOSTEP; setServo();
}

void UltraSonic::SetServoFullLeft()
{
    servoValue = SERVOMAX; setServo();
}

void UltraSonic::SetServoFullRight()
{ 
    servoValue = SERVOMIN; setServo();
}

void UltraSonic::setServo()
{
    myservo.write(servoValue + SERVO_OFFSET);
}

int UltraSonic::IsCollision() {
    if (GetDistance() < MIN_DISTANCE)
        return 1;
    
    return 0;
}
