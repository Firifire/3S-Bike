#include <SoftwareSerial.h>

#define debug false

//Pin Define
#define curSenSize 4
const int curSenPin[curSenSize] = { A0, A1, A2, A3};//, A1, A2, A3 }; //A0 = Wind, A1 = Kinectic, A2 = Solar, A3 = Battery, A4 = Arduino
const int battPin = A5;//baterry level
#define rpmSize 2
const int rpmPin[2] = { 5,6 }; //IR sensor INPUT// rpm measurement // 5 = wind || 6 = dynamo
SoftwareSerial myGsm(8, 9); 
//SoftwareSerial imuGPS(10, 11); //RX=pin 3, TX=pin 4

//Define global Varaibles
int rpmValue[rpmSize];
float ampere[curSenSize];

double durationMain = 0;

void setup() { 
	//Printing Values
#if debug == true
  Serial.begin(9600); // connect serial 
#endif

  //Initializing Functions
  currentSensorInit();
  rpmInit();
  connectionInit();
}

void loop() {

  readCurrentValue();
  rpmUpdate();
  if (durationMain >= 2000){  
    
  sendData();
  durationMain = 0;
  }
} 
