// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

/*

Assumed Pin Mappings

| ULN2003 Board | Motor Phase | Arduino Pin |
| ------------- | ----------- | ----------- |
| IN1           | Blue        |           2 |
| IN2           | Pink        |           3 |
| IN3           | Yellow      |           4 |
| IN4           | Orange      |           5 |

*/



//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

//The first 4 means FULLSTEP, then the coil end pins Blue, Yellow, Pink, Orange
AccelStepper stepper(4, 2, 4, 3, 5);  

void setup()
{  
   stepper.setMaxSpeed(1000);
   
   //On my 28BYJ-48 with a 64:1 gear ratio my max speed was about 650
   //Positive speeds are clockwise, Negative Speeds are counter-clockwise
   stepper.setSpeed(650);	 
}

void loop()
{  
   stepper.runSpeed();
}
