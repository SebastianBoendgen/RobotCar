#ifndef ReadFunk_h
#define ReadFunk_h
#include <Arduino.h>

class ReadFunk {
    public:
        void Initialize();
        void Read();
        int Direction;
        int Turning;
        int Speed;
        int Angle;
        int Gear;
    private:
        void GetGear();
        void GetSteering();
        void GetThrottle();
        int throttel;
        int steering;
};

#endif