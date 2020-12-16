#ifndef UltraSonic_h
#define UltraSonic_h
#include <Arduino.h>
#include <Servo.h>

class UltraSonic {
    public:
        void Initialize();
        void SetServoCenter();
        void SetServoFullLeft();
        void SetServoFullRight();
        void SetServoStepRight();
        void SetServoStepLeft();
        int GetDistance();
        int IsCollision();
    private:
        void setServo();
};

#endif