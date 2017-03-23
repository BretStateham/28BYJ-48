int bluePin = 2;    //IN1 on the ULN2003 Board, BLUE end of the Blue/Yellow motor coil
int pinkPin = 3;    //IN2 on the ULN2003 Board, PINK end of the Pink/Orange motor coil
int yellowPin = 4;  //IN3 on the ULN2003 Board, YELLOW end of the Blue/Yellow motor coil
int orangePin = 5;  //IN4 on the ULN2003 Board, ORANGE end of the Pink/Orange motor coil

// Well use the step count in the loop method to help with logic
int waveStepCount = 4;

//Keeps track of the current step.
//We'll use a zero based index. 
int currentStep = 0;

//Keeps track of the current direction
//Relative to the face of the motor. 
//Clockwise (true) or Counterclockwise(false)
//We'll default to clockwise
bool clockwise = true;

// How many steps to go before reversing, set to zero to not bounce.
//int targetSteps = 0;  //targetSteps 0 means the motor will just run in a single direction.
int targetSteps = 2048;  //2048 steps per rotation when wave or full stepping
//int targetSteps = 4096;  //4096 steps per rotation when half stepping

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  
  pinMode(bluePin, OUTPUT);
  pinMode(pinkPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(orangePin,OUTPUT);
  
  digitalWrite(bluePin, LOW);
  digitalWrite(pinkPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(orangePin, LOW);
}

void loop() {
  
  
  //Comment out the Serial prints to speed things up
  //Serial.print("Step: ");
  //Serial.println(currentStep);
  
  //Get a local reference to the number of steps in the sequence
  int stepCount = waveStepCount;
  
  //Then we can figure out what our current step within the sequence from the overall current step
  //and the number of steps in the sequence
  int currentStepInSequence = currentStep % stepCount;
  
  //Figure out which step to use. If clock wise, it is the same is the current step
  //if not clockwise, we fire them in the reverse order...
  int directionStep = clockwise ? currentStepInSequence : (stepCount-1) - currentStepInSequence;  
  
  switch(directionStep){
    case 0:
      digitalWrite(bluePin, HIGH);
      digitalWrite(pinkPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(orangePin, LOW);
      break;
    case 1:
      digitalWrite(bluePin, LOW);
      digitalWrite(pinkPin, HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(orangePin, LOW);
      break;
    case 2:
      digitalWrite(bluePin, LOW);
      digitalWrite(pinkPin, LOW);
      digitalWrite(yellowPin, HIGH);
      digitalWrite(orangePin, LOW);
      break;
    case 3:
      digitalWrite(bluePin, LOW);
      digitalWrite(pinkPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(orangePin, HIGH);
      break;
  }
  
    // Increment the program field tracking the current step we are on
  ++currentStep;
  
  // If targetSteps has been specified, and we have reached
  // that number of steps, reset the currentStep, and reverse directions
  if(targetSteps != 0 && currentStep == targetSteps){
    currentStep = 0;
    clockwise = !clockwise;
  } else if(targetSteps == 0 && currentStep == stepCount) {
    // don't reverse direction, just reset the currentStep to 0
    // resetting this will prevent currentStep from 
    // eventually overflowing the int variable it is stored in.
    currentStep = 0;
  }
  
  //2000 microseconds, or 2 milliseconds seems to be 
  //about the shortest delay that is usable.  Anything
  //lower and the motor starts to freeze. 
  //delayMicroseconds(2250);
  delay(2);
}
