const int delayTime = 1;
unsigned long rpmDuration[rpmSize]; // To store time difference
#define sizeRPM 5
float rpm[rpmSize][sizeRPM];
int rpmCur[rpmSize];
boolean rpmSensorLast[rpmSize];

void rpmInit()
{
	for (int i = 0; i < rpmSize; i++) {
		rpmDuration[i] = 0;
		for (int j = 0; j < sizeRPM; j++){
			rpm[i][j] = 0;
		}
		rpmCur[i] = 0;
    rpmSensorLast[i] = false;
		pinMode(rpmPin[i], INPUT);
	}
}

void rpmReset(){
  rpmDuration[0] = 1;
  rpmDuration[1] = 1;
}

void rpmUpdate()
{
	//Wind (Has 3 steps)
	if (rpmSensorLast[0] != digitalRead(rpmPin[0]))
	{
		rpmSensorLast[0] = !rpmSensorLast[0];
		if (rpmSensorLast[0])
		{
			rpm[0][rpmCur[0]++] = (1.0 / (rpmDuration[0] / (1000.0 * 60))) / 3;
			if (rpmCur[0] == sizeRPM)
				rpmCur[0] = 0;
			rpmDuration[0] = 0;
			float rpmVal = 0;
			for (int i = 0; i < sizeRPM; i++) {
				rpmVal += rpm[0][i];
			}
      rpmValue[0] = static_cast<int>(rpmVal / sizeRPM);
#if debug == true
      Serial.print("Wind Mill: ");
			Serial.println(rpmVal / sizeRPM);
#endif
		}
	}
	else if (rpmDuration[0] > 1000) {
		rpm[0][rpmCur[0]++] = 0;
		if (rpmCur[0] == sizeRPM)
			rpmCur[0] = 0;
		rpmDuration[0] = 0;
		float rpmVal = 0;
		for (int i = 0; i < sizeRPM; i++) {
			rpmVal += rpm[0][i];
		}   
    rpmValue[0] = static_cast<int>(rpmVal / sizeRPM);
#if debug == true
    Serial.print("Wind Mill: ");
    Serial.println(rpmVal / sizeRPM);
#endif
	}
	rpmDuration[0] += delayTime;

	//Dynamo (Has 3 steps)
	if (rpmSensorLast[1] != digitalRead(rpmPin[1]))
	{
		rpmSensorLast[1] = !rpmSensorLast[1];
		if (rpmSensorLast[1])
		{
			rpm[1][rpmCur[1]++] = 1.0 / (rpmDuration[1] / (1000.0 * 60));
			if (rpmCur[1] == sizeRPM)
				rpmCur[1] = 0;
			rpmDuration[1] = 0;
			float rpmVal = 0;
			for (int i = 0; i < sizeRPM; i++) {
				rpmVal += rpm[1][i];
			}
     rpmValue[1] = static_cast<int>(rpmVal / sizeRPM);
#if debug == true
      Serial.print("Dynamo: ");
      Serial.println(rpmVal / sizeRPM);
#endif
		}
	}
	else if (rpmDuration[1] > 1000) {
		rpm[1][rpmCur[1]++] = 0;
		if (rpmCur[1] == sizeRPM)
			rpmCur[1] = 0;
		rpmDuration[1] = 0;
		float rpmVal = 0;
		for (int i = 0; i < sizeRPM; i++) {
			rpmVal += rpm[1][i];
		}
   rpmValue[1] = static_cast<int>(rpmVal / sizeRPM);
#if debug == true
    Serial.print("Dynamo: ");
		Serial.println(rpmVal / sizeRPM);
#endif
	}
	rpmDuration[1] += delayTime;
  durationMain += delayTime;
	delay(delayTime);
}
