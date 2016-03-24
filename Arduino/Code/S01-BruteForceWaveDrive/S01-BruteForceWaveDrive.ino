int bluePin = 2;    //IN1 on the ULN2003 Board, BLUE end of the Blue/Yellow motor coil
int pinkPin = 3;    //IN2 on the ULN2003 Board, PINK end of the Pink/Orange motor coil
int yellowPin = 4;  //IN3 on the ULN2003 Board, YELLOW end of the Blue/Yellow motor coil
int orangePin = 5;  //IN4 on the ULN2003 Board, ORANGE end of the Pink/Orange motor coil

//Keeps track of the current step.
//We'll use a zero based index. 
int currentStep = 0;

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
  
  switch(currentStep){
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
  
  currentStep = (++currentStep < 4) ? currentStep : 0;
  
  //2000 microseconds, or 2 milliseconds seems to be 
  //about the shortest delay that is usable.  Anything
  //lower and the motor starts to freeze. 
  //delayMicroseconds(2250);
  delay(2);
}
