// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24
#include <AccelStepper.h>

AccelStepper stepper1(AccelStepper::DRIVER, 54, 55); // This motor sets the distance from the nozzle to the mandrel
AccelStepper stepper2(AccelStepper::DRIVER, 60, 61); // This is the mandrel spinning motor
AccelStepper stepper3(AccelStepper::DRIVER, 46, 48); // Oscillating stage motor
AccelStepper stepper4(AccelStepper::DRIVER, 26, 28); // This motor runs the syringe pump
boolean homed = false;
const int homeButton1 = 14; //homebuttong for oscillating stage on pin 14
const int homeButton2 = 3;  //homebuttong for distance setting stage on pin 3
int hBval;
int hBval2;
void setup()
{  

pinMode(38, OUTPUT);
digitalWrite(38, LOW);
pinMode(56, OUTPUT);
digitalWrite(56, LOW); 
pinMode(62, OUTPUT);
digitalWrite(62, LOW); 
pinMode(24, OUTPUT);
digitalWrite(24, LOW); 
Serial.begin(9600);
pinMode(homeButton1, INPUT_PULLUP);
pinMode(homeButton2, INPUT_PULLUP);
 
stepper4.setMaxSpeed(40);
stepper4.setAcceleration(100.0);
stepper4.moveTo(1000000);
stepper2.setMaxSpeed(2000);
stepper2.setAcceleration(150.0);
stepper2.moveTo(1000000000);
stepper1.setMaxSpeed(5000);
stepper1.setSpeed(-2000); 
stepper3.setMaxSpeed(20000);
stepper3.setSpeed(2000); 

stepper1Home();
stepper3Home();
   }


void loop() //this loop is the loop that oscillates the 1 stage, while rotating the mandrel and running the syringe pump motor
{  


 stepper4.run();
 
   if (stepper3.distanceToGo() == 0)
    {
stepper3.moveTo(7500);
stepper3.setSpeed(500);
stepper4.run();
    }
stepper4.run();
stepper2.run();
stepper3.runSpeedToPosition();
     if (stepper3.distanceToGo() == 0)
    {
stepper3.moveTo(0);
stepper3.setSpeed(500);
stepper4.run();
    }
    stepper2.run();
    stepper4.run();
    stepper3.runSpeedToPosition();
}
void stepper1Home(){ //homing and setting of distance to nozzle step
  hBval = digitalRead(homeButton1);
  while (hBval == LOW)
  {
    //backwards slowly till it hits the switch and stops
  hBval = digitalRead(homeButton1);
  stepper1.runSpeed();
  }
stepper1.setCurrentPosition(0);
stepper1.setAcceleration(1000);
stepper1.setSpeed(2000);
stepper1.runToNewPosition(17000);
delay(500);
stepper1.setCurrentPosition(0);
}
void stepper3Home(){ //oscillation stage homing 
  hBval2 = digitalRead(homeButton2);
  while (hBval2 == LOW)
  {
    //backwards slowly till it hits the switch and stops
        hBval2 = digitalRead(homeButton2);
    stepper3.runSpeed();
  }
stepper3.setCurrentPosition(0);
stepper3.setAcceleration(1000);
stepper3.setSpeed(3000);
stepper3.runToNewPosition(-7000);
stepper3.setCurrentPosition(0);
delay(500);
stepper3.setAcceleration(1000);
stepper3.setSpeed(3000);
stepper3.runToNewPosition(-3750);
stepper3.setCurrentPosition(0);
}
