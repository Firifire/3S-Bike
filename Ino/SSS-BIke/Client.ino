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

	myGsm.println("AT+CIPSTART=\"TCP\",\"0.tcp.ngrok.io\",\"12516\"");
	delay(5000);
	readData();
	delay(5000);
}

void sendData() {
    myGsm.println("AT+CIPSEND");
    delay(2000);
		readData();
    myGsm.print("S");
    myGsm.print(rpmValue[0]);
    myGsm.print("|");
     myGsm.print(rpmValue[1]);
    myGsm.print("|");
    myGsm.print(ampere[0]);
    myGsm.print("|");
		myGsm.print(ampere[1]);
    myGsm.print("|");
    myGsm.print(ampere[2]);
    myGsm.println("<EOF>");
		delay(300);
		myGsm.write(0x1A);
    delay(2000);
    readData();
}

void readData() {
	while (myGsm.available() != 0)
		Serial.write(myGsm.read());
}
