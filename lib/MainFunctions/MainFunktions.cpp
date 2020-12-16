#include <CarMovement.h>
#include <Arduino.h>
#include <ReadFunk.h>
#include "MainFunktions.h"

ReadFunk readRemote;
CarMovement myMotor;

#ifdef DEBUG
bool ToggleRemote = true;
#endif

void MainFunktions::ReadSerial()
{
    String inputString = Serial.readString();

#ifdef DEBUG
    if (inputString == "v")
    {
        ToggleRemote = !ToggleRemote;
        Serial.print("Set Steering to: ");
        if (ToggleRemote)         
            Serial.println("REMOTE");
        else
            Serial.println("SERIAL");      
    }

    if (!ToggleRemote) 
#endif
        handleKeyPress(inputString);   
#ifdef DEBUG
    else 
        RemoteControl();
#endif           
}

void MainFunktions::handleKeyPress(String inputString)
{
    for (int cnt = 0; cnt <= inputString.length(); cnt++) {
        char input = inputString.charAt(cnt);
        // STEERING
        if (input == 'W' || input == 'w')
            myMotor.Forward(); 
        else if (input == 'S'|| input == 's')
            myMotor.Backward();
        else if (input == 'A'|| input == 'a')
            myMotor.Left();
        else if (input == 'Q'|| input == 'q')
            myMotor.MoreLeft();
        else if (input == 'D'|| input == 'd')
            myMotor.Right();
        else if (input == 'E'|| input == 'e')
            myMotor.MoreRight();
        else if (input == 'X'|| input == 'x')
            myMotor.FullStop();
        else if (input == 'Y'|| input == 'y')
            myMotor.PrintStatus();
        else if (input == 'R'|| input == 'r')
            myMotor.Accelerate();
        else if (input == 'F'|| input == 'f')
            myMotor.Brake();
        // SERVO & SONIC
        else if (input == 'i' || input == 'I')
            ultraSonic.SetServoFullRight();
        else if (input == 'k' || input == 'K')
            ultraSonic.SetServoStepRight();
        else if (input == 'z' || input == 'Z')
            ultraSonic.SetServoFullLeft();
        else if (input == 'h' || input == 'H')
            ultraSonic.SetServoStepLeft();
        else if (input == 'j' || input == 'J')
            ultraSonic.SetServoCenter();
        else if (input == 'u' || input == 'U') {
            Serial.print("Distance: "); 
            Serial.println(ultraSonic.GetDistance());
        }
        else if (input == 'm' || input == 'M') {
            readRemote.Read();
        }
    }
    
    if (inputString.toInt() > 0 && inputString.toInt() < 100) {  
        int motorSpeed = inputString.toInt();
        Serial.println(motorSpeed);
        myMotor.SetSpeedBoth(motorSpeed);
    }
}

void MainFunktions::RemoteControl(){
#ifdef DEBUG
    if (!ToggleRemote)
        return;
#endif
    if (readRemote.Gear == 1)
        ultraSonic.SetServoFullLeft();
    if (readRemote.Gear == 2)
        ultraSonic.SetServoCenter();
    if (readRemote.Gear == 3)
        ultraSonic.SetServoFullRight();

    if (ultraSonic.IsCollision() == 1)
        return;

    readRemote.Read();
    if(readRemote.Turning != 0)
    {
        if (readRemote.Turning == 1)
            myMotor.Left(); 
        else if (readRemote.Turning == 2)
            myMotor.Right();

        myMotor.SetSpeedBoth(readRemote.Angle);
    }  
    else if (readRemote.Direction != 0)
    {
        if (readRemote.Direction == 1)
            myMotor.Backward();
        else if (readRemote.Direction == 2)
            myMotor.Forward();

        myMotor.SetSpeedBoth(readRemote.Speed);
    }
}
