#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

#include <FS.h>
#include <SD.h>
#include <SPI.h>

void writeFile(File &file, float lux);
void openFile(fs::FS &fs, const char* path);
void writeFile(File &file);

BH1750 lightMeter;
File file;

#define MAX_W 100
#define TIME_DELAY 500
int i = 0;

void setup() 
{
  	Serial.begin(9600);
	Wire.begin();
	
	if (!SD.begin(5))
	{
		Serial.println("Scheda non montata correttamente");
		return;
	}

	uint8_t cardType = SD.cardType();
	Serial.printf("Tipo di scheda: %u\n", cardType);

	if (!lightMeter.begin())
	{
		Serial.println("Errore nel sensore");	
	}

	Serial.println("Iniziano le misurazioni");
	openFile(SD, "/lux_data.txt");
}

void loop() 
{
	float lux = lightMeter.readLightLevel();
	Serial.printf("Lux level: %.2f\n", lux);

	if (i == MAX_W)
	{
		file.close();
	}
	
	else
	{
		writeFile(file, lux);
		writeFile(file);
		
		i++;
		delay(TIME_DELAY);
	}
}

void openFile(fs::FS &fs, const char* path)
{
	file = fs.open(path, FILE_APPEND);
	
	if (!file)
	{
		Serial.println("Errore, file non esistente");
		return;
	}

	Serial.println("File creato");
}

void writeFile(File &file, float lux)
{
	if (!file.print(lux))
	{
		Serial.println("Errore nella scrittura");
		return;
	}

	file.print(lux);
	Serial.println("Scrittura avvenuta con successo");
}

void writeFile(File &file)
{
	file.print("\n");
}


