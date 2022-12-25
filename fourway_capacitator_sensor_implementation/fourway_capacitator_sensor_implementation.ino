#include <CapacitiveSensor.h>

//Parameters
bool autocal  = 1;
const int numReadings  = 10;
const int sensitivity  = 100;
const int thresh  = 600;
CapacitiveSensor cs0  = CapacitiveSensor(2, 3);
CapacitiveSensor cs1  = CapacitiveSensor(4, 5);
CapacitiveSensor cs2  = CapacitiveSensor(6, 7);
CapacitiveSensor cs3  = CapacitiveSensor(8, 9);

unsigned long current_time = 0;
unsigned long last_logic_time = 0;
unsigned long LOGIC_INTERVAL = 2;

bool cs0IsOn = 0;
bool cs1IsOn = 0;
bool cs2IsOn = 0;
bool cs3IsOn = 0;

bool isConstant = false;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  if (autocal == 0) {
    {
      cs0.set_CS_AutocaL_Millis(0xFFFFFFFF);
      cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);
      cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
      cs3.set_CS_AutocaL_Millis(0xFFFFFFFF);
    }
  }
}

void loop() {
  current_time = millis();
  if(current_time - last_logic_time > LOGIC_INTERVAL) { // ALL LOGIC HERE
    last_logic_time = current_time;

    // cs0 LOGIC
    if(smoothZero(&cs0) > thresh) {
      if(isConstant) {
        Serial.println(F("CS0-H")); // H stands for HELD
      } else if(cs0IsOn == false) {
        cs0IsOn = true;
        Serial.println(F("CS0-P")); // P stands for PRESSED
      }
    } else {
      if(isConstant == false && cs0IsOn) {
        cs0IsOn = false;
        Serial.println(F("CS0-R")); // R stands for RELEASED
      }
    }

    // cs1 LOGIC
    if(smoothZero(&cs1) > thresh) {
      if(isConstant) {
        Serial.println(F("CS1-H")); // H stands for HELD
      } else if(cs1IsOn == false) {
        cs1IsOn = true;
        Serial.println(F("CS1-P")); // P stands for PRESSED
      }
    } else {
      if(isConstant == false && cs1IsOn) {
        cs1IsOn = false;
        Serial.println(F("CS1-R")); // R stands for RELEASED
      }
    }

    // cs2 LOGIC
    if(smoothZero(&cs2) > thresh) {
      if(isConstant) {
        Serial.println(F("CS2-H")); // H stands for HELD
      } else if(cs2IsOn == false) {
        cs2IsOn = true;
        Serial.println(F("CS2-P")); // P stands for PRESSED
      }
    } else {
      if(isConstant == false && cs2IsOn) {
        cs2IsOn = false;
        Serial.println(F("CS2-R")); // R stands for RELEASED
      }
    }

    // cs3 LOGIC
    if(smoothZero(&cs3) > thresh) {
      if(isConstant) {
        Serial.println(F("CS3-H")); // H stands for HELD
      } else if(cs3IsOn == false) {
        cs3IsOn = true;
        Serial.println(F("CS3-P")); // P stands for PRESSED
      }
    } else {
      if(isConstant == false && cs3IsOn) {
        cs3IsOn = false;
        Serial.println(F("CS3-R")); // R stands for RELEASED
      }
    }
    
  }
}

long smoothZero(CapacitiveSensor *capSens) {
  long readings [numReadings];
  int readIndex  = 0;
  long total  = 0;
  ////Perform average on sensor readings
  long average;
  // subtract the last reading:
  total = total - readings[readIndex];
  // read the sensor:
  readings[readIndex] = capSens->capacitiveSensor(sensitivity);
  // add value to total:
  total = total + readings[readIndex];
  // handle index
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  //memset(readings, 0, sizeof(readings));
  // calculate the average:
  average = total / numReadings;

  return average;
}
