/*
  StepperMel.cpp - Library for stepper motor.
  Created by Robert and Azamat, December 29, 2020.
  Released into the public domain.
*/
#include <Arduino.h>
#include "StepperMel.h"

StepperMel::StepperMel(int pStep,int pDir,int pMS1,int pMS2,int pMS3){
PIN_STEP=pStep;
PIN_DIR=pDir;
PIN_MS1=pMS1;
PIN_MS2=pMS2;
PIN_MS3=pMS3;
pinMode(PIN_STEP, OUTPUT);
pinMode(PIN_DIR, OUTPUT);
pinMode(PIN_MS1, OUTPUT);
pinMode(PIN_MS2, OUTPUT);
pinMode(PIN_MS3, OUTPUT);
digitalWrite(PIN_STEP, 1);
digitalWrite(PIN_DIR, 0);
}

void StepperMel::attach(int pStep,int pDir,int pMS1,int pMS2,int pMS3){
PIN_STEP=pStep;
PIN_DIR=pDir;
PIN_MS1=pMS1;
PIN_MS2=pMS2;
PIN_MS3=pMS3;
pinMode(PIN_STEP, OUTPUT);
pinMode(PIN_DIR, OUTPUT);
pinMode(PIN_MS1, OUTPUT);
pinMode(PIN_MS2, OUTPUT);
pinMode(PIN_MS3, OUTPUT);
digitalWrite(PIN_STEP, 1);
digitalWrite(PIN_DIR, 0);
}

void StepperMel::setStep(int stepLength){
  currentStep=stepLength;
  digitalWrite(PIN_MS1, MS[stepLength][0]);
  digitalWrite(PIN_MS2, MS[stepLength][1]);
  digitalWrite(PIN_MS3, MS[stepLength][2]);
};

void StepperMel::moveStep(float dir,int pause,int moveCount){
if (dir<=0) dir=0; else dir=1;  
digitalWrite(PIN_DIR, dir);
for(int j = 0; j < moveCount; j++) {
digitalWrite(PIN_STEP, HIGH);
delay(int(pause/1000));
digitalWrite(PIN_STEP, LOW);
delay(int(pause/1000));
}
};

void StepperMel::moveAccStep(float dir,int pause,int moveCount){
if (dir<=0) dir=0; else dir=1;  
float p=20000;
digitalWrite(PIN_DIR, dir);
int k=0;
while (p>pause){
p=max(pause,p*0.95);
digitalWrite(PIN_STEP, HIGH);
delay(int(p/1000));
digitalWrite(PIN_STEP, LOW);
delay(int(p/1000));
  k++;
}

for(int j = 0; j < moveCount-2*k; j++) {
digitalWrite(PIN_STEP, HIGH);
delay(int(pause/1000));
digitalWrite(PIN_STEP, LOW);
delay(int(pause/1000));
}

for(int j = 0; j < k; j++) {
p=p/0.95;
digitalWrite(PIN_STEP, HIGH);
delay(int(p/1000));
digitalWrite(PIN_STEP, LOW);
delay(int(p/1000));
}
}

void StepperMel::moveAngle(float speed,float angle, bool acc){
  long moveCount=abs(angle)*pow(2,currentStep)/1.8;
  long pause=max(1000,STEPPER_ANGLE/(speed*pow(2,currentStep)));
  if (acc)  
moveAccStep(angle,pause,moveCount);
else
moveStep(angle,pause,moveCount);
};

void StepperMel::moveVector(float speed,int _length, bool acc){
pos+=_length;
int pause=max(1000,k/(speed*pow(2,currentStep)));
int moveCount=abs(_length)*pow(2,currentStep)*100;
if (acc)
moveAccStep(_length,pause,moveCount);
else
moveStep(_length,pause,moveCount);

}

void StepperMel::movePosition(float speed,int newPos, bool acc){
  moveVector(speed,newPos-pos,acc);
}

void StepperMel::moveHome(){
  moveVector(10,-pos,0);
}

int StepperMel::getPosition(){
  return pos;
}