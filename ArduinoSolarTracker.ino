// Scott Wiedemann
// 01/15/2015
// Solar Tracker for Arduino

// Finds a bright spot, like the sun, a ceiling light or lamp.  Dumb, right?

#include <Servo.h>  // servo library

Servo horizontalServo;
int horizontalServoDeadzone = 90;

Servo verticalServo;
int verticalServoDeadzone = 90;

void setup() {
  Serial.begin(9600); // write to log
  horizontalServo.attach(9);
  verticalServo.attach(10);
}

void loop() {
  String logMessage = "NO MESSAGE";
  
  // how big of step should we take?
  // TODO: Should this varry bases on the size of the deltas along eash axis?
  int dm = 3;
  
  // how accurate (or inaccurate) is this thing?
  int tolerance = 17;
  
  int lrd1 = analogRead(0); // lower right
  int lrd2 = analogRead(1); // upper right
  int lrd3 = analogRead(2); // upper left
  int lrd4 = analogRead(3); // lower left

/*
  logMessage = "lrd 1,2,3,4: ";
  logMessage += lrd1;
  logMessage += ", ";
  logMessage += lrd2;
  logMessage += ", ";
  logMessage += lrd3;
  logMessage += ", ";
  logMessage += lrd4;
  Serial.println(logMessage);
*/  
  int at = (lrd2 + lrd3) / 2; // average top
  int ad = (lrd1 + lrd4) / 2; // average down
  int al = (lrd3 + lrd4) / 2; // average left
  int ar = (lrd1 + lrd2) / 2; // average right
  
  int dvert = at - ad; // vertical difference
  int dhoriz = al - ar; // horizontal difference
  
  //logMessage = "dhoriz: ";
  //logMessage += dhoriz;
  //Serial.println(logMessage);
  if(abs(dhoriz) > tolerance) {
    
    // FIXME: if the vertical angle breaches the zenith, then dm should be negated.  Can and how should this be detected?
    if(dhoriz < 0) {
      dm = dm*-1;
    }
    int horm = horizontalServoDeadzone + dm;

    //logMessage = "horm: ";
    //logMessage += horm;
    //Serial.println(logMessage);
    horizontalServo.write(horm);
  } else {
    horizontalServo.write(horizontalServoDeadzone);
  }

  dm = 4;

  logMessage = "dvert: ";
  logMessage += dvert;
  Serial.println(logMessage);
  if(abs(dvert) > tolerance) {
    if(dvert < 0) {
      dm = dm*-1;
    }
    int vertm = verticalServoDeadzone + dm;

    //logMessage = "vertm: ";
    //logMessage += vertm;
    //Serial.println(logMessage);
    verticalServo.write(vertm);
  } else {
    verticalServo.write(verticalServoDeadzone);
  }

  //horizontalServo.write(horizontalServoDeadzone);
  //verticalServo.write(verticalServoDeadzone);
  //Serial.println(horizontalServo.read());
  //Serial.println(verticalServo.read());
}

