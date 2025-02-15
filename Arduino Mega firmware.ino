
 
//Include the Arduino Stepper Library
#include <Stepper.h>
//import the bitvoicer library
#include <BitVoicer11.h>

//initiate the bitvoicer Serial Class
BitVoicerSerial bvSerial = BitVoicerSerial();

//store the data type retreived by getData();
byte dataType = 4;

//create an array for all of the output pins for voice
int outPutPins[] = {51,49,47};

// Define Constants
 
// Number of steps per internal motor revolution 
const float STEPS_PER_REV = 32; 
 
//  Amount of Gear Reduction
const float GEAR_RED = 64;
 
// Number of steps per geared output rotation
const float revs = STEPS_PER_REV * GEAR_RED;
 
// Define Variables
 
// Number of Steps Required
int stepsRequired;

//where you are now
int currentFloor=0;

// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing
Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);
 
void setup()
{
pinMode(4,INPUT);
pinMode(3,INPUT);
pinMode(2,INPUT);
pinMode(outPutPins[0],OUTPUT);
pinMode(outPutPins[1],OUTPUT);
pinMode(outPutPins[2],OUTPUT);
Serial.begin(9600);
}

int floorLocation[] = {0,3*revs, 6*revs};


void loop()
{
//First Floor
if(digitalRead(4)==true)
 {
  stepsRequired = floorLocation[0]-currentFloor;
  steppermotor.setSpeed(1200);
  steppermotor.step(stepsRequired);
    currentFloor = floorLocation[0];
 }
 
//Second Floor
 if(digitalRead(3)==true)
 {
  stepsRequired = floorLocation[1]-currentFloor;
  steppermotor.setSpeed(1200);
  steppermotor.step(stepsRequired);
    currentFloor = floorLocation[1];
 }
 
//Third Floor
if(digitalRead(2)==true)
 {
  stepsRequired = floorLocation[2]-currentFloor;
  steppermotor.setSpeed(1200);
  steppermotor.step(stepsRequired);
  currentFloor = floorLocation[2];
 }
 digitalWrite(outPutPins[0], 0);
 digitalWrite(outPutPins[1], 0);
 digitalWrite(outPutPins[2], 0);
 
}
//this function will run anytime serial data is available
void serialEvent()
{
  //reads the serial console and stores the new data
  dataType=bvSerial.getData();

  //check if data type is the same as the one coming from bitvoicer
  if(dataType == BV_INT)
  {
    //the way that this is set up will avoid a bunch of if else statements for the rest of the outputs
    //Assign an  int to hold a pin number
    //int pinNumber = bvSerial.intData;
    //write to the pinNumber based on the current voice int
    digitalWrite(bvSerial.intData,1);
    delay(50);
  }
 }
