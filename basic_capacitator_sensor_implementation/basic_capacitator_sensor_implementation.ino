#include <CapacitiveSensor.h>

//Parameters
bool autocal  = 1;
const int numReadings  = 10;
const int sensitivity  = 100;
const int thresh  = 600;
CapacitiveSensor cs  = CapacitiveSensor(2, 3);

unsigned long current_time = 0;
unsigned long last_logic_time = 0;
unsigned long LOGIC_INTERVAL = 2;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  if (autocal == 0) {
    {
      cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
    }
  }
}

void loop() {
  current_time = millis();
  if(current_time - last_logic_time > LOGIC_INTERVAL) { // ALL LOGIC HERE
    last_logic_time = current_time;
    if(smoothZero(&cs) > thresh) {
      Serial.println(F("Threshold passed"));
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
