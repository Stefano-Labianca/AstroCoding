#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() 
{
  	Serial.begin(9600);
	Wire.begin();

	if (!lightMeter.begin())
	{
		Serial.println("Errore nel sensore");	
	}

	Serial.println("Iniziano le misurazioni");
}

void loop() 
{
	float lux = lightMeter.readLightLevel();
	Serial.printf("Lux level: %.2f\n", lux);

  	delay(1000);
}