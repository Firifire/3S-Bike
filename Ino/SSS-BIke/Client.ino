//﻿byte datasend[];
/*
0 = solar current sensor
1 = wind current sensor
2 = dynamo current sensor
3 = battery current sensor
4 = rpm of wind
5 = rpm of dynamo
6 = latitude
7 = longitude
speed
battery level
*/

void connectionInit() {
	myGsm.begin(9600);
	Serial.begin(9600);
	delay(500);

	myGsm.println("AT+CIPSHUT");
	delay(1000);
	readData();

	myGsm.println("AT+CIPMUX=0");
	delay(2000);
	readData();

	myGsm.println("AT+CGATT=1");
	delay(1000);
	readData();


	myGsm.println("AT+CSTT=\"diginet\",\"\",\"\"");//setting the APN,2nd parameter empty works for all networks  //Maxis: unet (3G), max4g, net//diginet
	delay(5000);
	readData();

	myGsm.println();
	myGsm.println("AT+CIICR");
	delay(6000);
	readData();

	myGsm.println("AT+CIFSR"); //init the HTTP request
	delay(2000);
	readData();

	myGsm.println("AT+CIPSTART=\"TCP\",\"0.tcp.ngrok.io\",\"15868\"");
	delay(5000);
	readData();
	delay(5000);

	myGsm.println("AT+CIPSEND");
	delay(2000);
	readData();
}

void sendData() {
	bool isWriting = false;
	char c = ' ';
	// Keep reading from SIM800 and send to Arduino Serial Monitor
	while (myGsm.available())
	{
		c = myGsm.read();
		Serial.write(c);
	}
	// Keep reading from Arduino Serial Monitor and send to SIM900A
	while (Serial.available())
	{
		isWriting = true;
		c = Serial.read();
		//    myGsm.write(c); 
	}
	if (isWriting) {
		myGsm.println("AT+CIPSEND");
		delay(200);
		readData();

		myGsm.println("LAT:3 | LON:101");
		delay(300);
		isWriting = false;
		readData
		();
		myGsm.write(0x1A);
	}
}

void readData() {
	while (myGsm.available() != 0)
		Serial.write(myGsm.read());
}
