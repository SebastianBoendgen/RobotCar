#ifndef CarMovement_h
#define CarMovement_h
#include <Arduino.h>

class CarMovement {
  public:
    void Initialize();
    void Forward();
    void Backward();
    void Left();
    void Right();
    void MoreRight();
    void MoreLeft();
    void SetSpeedBoth(int speed);
    void FullGas();
    void FullStop();
    void PrintStatus();
    void Accelerate();
    void Brake();
  private:
    int currentMotorSpeedInPercent;
    char currentDirection;
    int currentAngle;
    void SetEnginge(int, int);
    int GetDrivingValue(int speedInPercent);
};

#endif