#ifndef MainFunctions_h
#define MainFunctions_h

#include <CarMovement.h>
#include <UltraSonic.h>
#include <Arduino.h>
#include <ReadFunk.h>

class MainFunktions {
    public:
        void ReadSerial();
        void RemoteControl();
        CarMovement myMotor;
        UltraSonic ultraSonic;
        ReadFunk readRemote;
        bool ToggleRemote;
    private:
        void handleKeyPress(String inputString);
};

#endif