void readBatteryLevel() {
	int voltReading = analogRead(battPin);//baterry level
	int volts = (voltReading / 1023) * 100;
	if (volts == 100)
	{
		Serial.print(volts);
		Serial.print("%");
		delay(1000);
	}
	else if (volts < 10)
	{
		Serial.print(volts);
		Serial.print("%");
		delay(1000);
	}
	else
	{
		Serial.print(volts);
		Serial.print("%");
		delay(1000);
	}
}
