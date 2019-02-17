
const int mVperAmp = 185; // 5A module
const int ACSoffset = 2500;
double Voltage;
double ampere[curSenSize];


void currentSensorInit() {
	for (int i = 0; i < curSenSize; i++) {
		pinMode(curSenPin[i], INPUT);
	}
}

void readCurrentValue() {
	for (int i = 0; i < curSenSize; i++) {
		ampere[i] = (((analogRead(curSenPin[i]) / 1024.0) * 5000 - ACSoffset) / mVperAmp) -0.053;
#if debug == true

    Serial.print("slot");
    Serial.print(i);
    Serial.print(": ");
		Serial.println(ampere[i], 3);
#endif // debug == true
	}
}
