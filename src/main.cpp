#include <CarMovement.h>
#include <Arduino.h>
#include <MainFunktions.h>

MainFunktions mainFunc;
int cnt = 0;

void setup() {
  Serial.begin(9600);
  mainFunc.myMotor.Initialize();
  mainFunc.myMotor.FullStop();
  mainFunc.ultraSonic.Initialize();
  mainFunc.readRemote.Initialize();
}

//Repeat execution
void loop() {
  if (Serial.available())
  {
    mainFunc.ReadSerial();
  }

  mainFunc.RemoteControl();

  int distance = mainFunc.ultraSonic.GetDistance();
  if (distance <= 2)
    mainFunc.myMotor.FullStop();
}