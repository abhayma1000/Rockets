#include <SD.h>
#include <SPI.h>

File myFile;

int pinCS = 10; // Pin 10 on Arduino Uno




int button_pin = 2;

bool done = false;


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;



void setup() {
  Serial.begin(9600);

  if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
  //if (! bmp.begin_SPI(BMP_CS)) {  // hardware SPI mode  
  //if (! bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {  // software SPI mode
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);


  

  pinMode(button_pin, INPUT_PULLUP);
  
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

  myFile = SD.open("bmp_data.txt", FILE_WRITE);

  Serial.println("Writing data to file");

}

void loop() {

  if (done == false) {
    if (! bmp.performReading()) {
      Serial.println("Failed to perform reading :(");
      return;
    }
    
    Serial.print("Temperature = ");
    Serial.print(bmp.temperature);
    Serial.println(" *C");
  
    Serial.print("Pressure = ");
    Serial.print(bmp.pressure / 100.0);
    Serial.println(" hPa");
  
    Serial.print("Approx. Altitude = ");
    Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
  
    myFile.println(bmp.readAltitude(SEALEVELPRESSURE_HPA));

    Serial.println("Recording...");
  }

  if (digitalRead(button_pin) == 0) {
    done = true;

    Serial.println("Stopped recording...");

    myFile.close();

    Serial.println();
  }

  delay(1000);

  

}
