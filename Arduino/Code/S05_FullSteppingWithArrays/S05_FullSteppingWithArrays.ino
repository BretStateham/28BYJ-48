//Put all the pins in an array to make them easy to work with
int pins[] {
    2,  //IN1 on the ULN2003 Board, BLUE end of the Blue/Yellow motor coil
    3,  //IN2 on the ULN2003 Board, PINK end of the Pink/Orange motor coil
    4,  //IN3 on the ULN2003 Board, YELLOW end of the Blue/Yellow motor coil
    5   //IN4 on the ULN2003 Board, ORANGE end of the Pink/Orange motor coil
};

//Define the wave drive sequence.  
//With the pin (coil) states as an array of arrays
int waveStepCount = 4;
int waveSteps[][4] = {
    {HIGH,LOW,LOW,LOW},
    {LOW,HIGH,LOW,LOW},
    {LOW,LOW,HIGH,LOW},
    {LOW,LOW,LOW,HIGH}
  };

//Define the full step sequence.  
//With the pin (coil) states as an array of arrays
int fullStepCount = 4;
int fullSteps[][4] = {
    {HIGH,HIGH,LOW,LOW},
    {LOW,HIGH,HIGH,LOW},
    {LOW,LOW,HIGH,HIGH},
    {HIGH,LOW,LOW,HIGH}
  };


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
int targetSteps = 2048;  //2049 steps per rotation when wave or full stepping
//int targetSteps = 4096;  //4096 steps per rotation when half stepping

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  
  for(int pin = 0; pin < 4; pin++) {
    pinMode(pins[pin], OUTPUT);
    digitalWrite(pins[pin], LOW);
  }
}

void step(int steps[][4], int stepCount) {
  //Then we can figure out what our current step within the sequence from the overall current step
  //and the number of steps in the sequence
  int currentStepInSequence = currentStep % stepCount;
  
  //Figure out which step to use. If clock wise, it is the same is the current step
  //if not clockwise, we fire them in the reverse order...
  int directionStep = clockwise ? currentStepInSequence : (stepCount-1) - currentStepInSequence;  

  //Set the four pins to their proper state for the current step in the sequence, 
  //and for the current direction
  for(int pin=0; pin < 4; pin++){
    digitalWrite(pins[pin],steps[directionStep][pin]);
  }  
}

void loop() {
 
  //Comment out the Serial prints to speed things up
  //Serial.print("Step: ");
  //Serial.println(currentStep);
  
  //Get a local reference to the number of steps in the sequence
  //And call the step method to advance the motor in the proper direction

  //Wave Drive
  //int stepCount = waveStepCount;
  //step(waveSteps,waveStepCount);
    
  //Full Step
  int stepCount = fullStepCount;
  step(fullSteps,fullStepCount);

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
