//Just Arduino Nano, SD module, button, and battery
//Once button is pressed, starts blinking and recording after a minute
//Once button is pressed again, stops recording
//Demonstrating SD module

#include <SD.h>
#include <SPI.h>

File myFile;

int sd_cs_pin = 10;

int button_pin = 2;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(button_pin, INPUT_PULLUP);
  
  pinMode(sd_cs_pin, OUTPUT);

  if (SD.begin()) {
    Serial.println("SD card is ready to use.");

  } else {
    Serial.println("SD card initialization failed");

    return;
  }

  myFile = SD.open("test.txt", FILE_WRITE);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(myFile) {
    float time = millis() / 1000.0000;
    
    myFile.println(time);

    myFile.println("\n");
  }
}
