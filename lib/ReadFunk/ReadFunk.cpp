#include <ReadFunk.h>

#define STEERING 10
#define THROTTEL 4
#define GEARBOX  2

#define GEAR_MAX 1600
#define GEAR_MIN 1300

#define THROTTEL_MAX 2005
#define THROTTEL_MIN 930
#define THROTTEL_CEN_MIN 1485
#define THROTTLE_CEN_MAX 1515

#define STEERING_MAX 2000
#define STEERING_MIN 980
#define STEERING_CEN_MIN 1485
#define STEERING_CEN_MAX 1515

int Direction = 0;
int Turning  = 0;
int Speed = 0;
int Angle = 0;
int Gear = 2;

void ReadFunk::Initialize() {
    pinMode(STEERING, INPUT);
    pinMode(THROTTEL, INPUT);
    pinMode(GEARBOX, INPUT);
    Read();
}

void ReadFunk::Read() {
    GetGear();
    GetSteering();
    GetThrottle();

#ifdef DEBUG
    Serial.print(" - RC: Gear: ");
    Serial.print(currentGear);
    Serial.print("\tSpeed: ");
    if (Direction == 0)
        Serial.print("STOP\t");
    else if (Direction == 2) {
        Serial.print("FW | ");
        Serial.print(Speed);
    }
    else if (Direction == 1) {
        Serial.print("BW | ");
        Serial.print(Speed);
    }
    Serial.print("\tSTEERING:\t");
    if (Turning == 0)
        Serial.print("STOP\t");
    else if (Turning == 1) {
        Serial.print(" LEFT | ");
        Serial.print(Angle);
    }
    else if (Turning == 2) {
        Serial.print("RIGHT | ");
        Serial.print(Angle);
    }
    Serial.println(" - ");
#endif
}

void ReadFunk::GetGear() {    
    int gearbox = pulseIn(GEARBOX, HIGH);

    if (gearbox < GEAR_MIN)
        Gear = 3;
    else if (gearbox > GEAR_MAX)
        Gear = 1;
    else if (gearbox > GEAR_MIN && gearbox < GEAR_MAX)
        Gear = 2;
    else
        Gear = 255;
}

void ReadFunk::GetSteering() {
    int raw_steering = pulseIn(STEERING, HIGH);
    int steering = constrain(raw_steering, STEERING_MIN, STEERING_MAX);
    
    if (STEERING_CEN_MIN < steering && steering < STEERING_CEN_MAX) {
        Turning = 0; Direction = 0;
    } else if (STEERING_CEN_MIN > steering) {
        Angle = map(steering, STEERING_CEN_MIN, STEERING_MIN, 0, 100);
        Turning = 1;
    } else if (STEERING_CEN_MAX < steering) {
        Angle = map(steering, STEERING_CEN_MAX, STEERING_MAX, 0, 100);
        Turning = 2;
    }
}

void ReadFunk::GetThrottle() {
    int raw_throttle = pulseIn(THROTTEL, HIGH);
    int throttle = constrain(raw_throttle, THROTTEL_MIN, THROTTEL_MAX);
    
    if (THROTTEL_CEN_MIN < throttle && throttle < THROTTLE_CEN_MAX) {
        Speed = 0; 
        Direction = 0;
    } else if (THROTTEL_CEN_MIN > throttle) {
        Speed = map(throttle, THROTTEL_CEN_MIN, THROTTEL_MIN, 0, 100);
        Direction = 1;
    } else if (THROTTLE_CEN_MAX < throttle) {
        Speed = map(throttle, THROTTLE_CEN_MAX, THROTTEL_MAX, 0, 100);
        Direction = 2;
    }    
}
