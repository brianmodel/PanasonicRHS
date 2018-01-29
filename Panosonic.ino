//Including the CheapStepper library
//Github repo we got this library from is here: https://github.com/tyhenry/CheapStepper
#include <CheapStepper.h>

//Creating a CheapStepper object called stepper on pins 8,9,10, and 11
CheapStepper stepper(8,9,10,11);

//Declaring variables that we will use in our program

//Pin on Arduino that will test if button is pressed
const int inPin = 13;
//This will be the reading on pin 13
int val = 0;
//A temporary variable that will prevent the blades from spinning more than one time when the button is pressed
boolean cont = false;

void setup() {
  //Setting the stepper's rpm to 12
  stepper.setRpm(12);

  //The gear ratio in the stepper motor was measured by others to be
  //63.68395:1. This enables us to more accurately control the motor
  stepper.set4076StepMode();

  //Making pin 13 an input pin to test for voltage 
  pinMode(inPin, INPUT);

  //Begining a serial connection with the Arduino
  Serial.begin(9600);
}

void loop() {
  //Reading the value on pin 13. When the button is pressed, val becomes 0.
  val = digitalRead(inPin);

  //Testing if the button is pressed
  if(val==0){
    //Making our temporary variable true when the button is pressed
    cont = true;
    }
  //Testing if the temporary variable is true, and val is 1, meaning the button is released.
  else if(cont && val==1){
    //We only want the blades to spin when the button is released, so this code will execute 
    //when the button is pressed and released

    //This rotates the blades a certain number of degrees. Because it takes some time for the
    //motor to accelerate and deceleate, the angle has to be greater than 120 degrees in order 
    //to spin the blades 120 degrees, or a third of the way 
    stepper.moveDegreesCW(180);
    //Waiting .1 seconds so as to make sure everything stopped 
    //delay(100);
    //Setting the temporary variable back to false so that this code segment does not execute 
    //again until the button is pressed
    cont = false;
    }
  //Waiting .1 seconds so that the loop does not run continuously, possibly causing problems
  delay(100);
}
