#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include <SD.h>

//BNO setup
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);


//SD setup
File myFile;
byte pinCS = 10;


//Button setup
const byte buttonPin = 2;

void add_new_line(File the_file) {
  the_file.print("\n");
}

void add_comma(File the_file) {
  the_file.print(", ");
}


void setup() {
  Serial.begin(115200);
  
  delay(5000);

  Serial.println("Beginning");

  //BNO initialization
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }
  bno.setExtCrystalUse(true);


  
  //SD initialization
  pinMode(pinCS, OUTPUT);
  if (SD.begin()) {
    myFile = SD.open("BNOData3.txt", FILE_WRITE);
  }

  //Button initialization
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
 

  //BNO code
  sensors_event_t event;
  bno.getEvent(&event);



  //SD code
  if (myFile) {
    myFile.print(event.orientation.x, 2);

    add_comma(myFile);

    myFile.print(event.orientation.y, 2);

    add_comma(myFile);
    
    myFile.print(event.orientation.z, 2);

    add_new_line(myFile);
    
    Serial.println("logging...");
  }

  if (digitalRead(buttonPin) == LOW) {
    myFile.close();

    Serial.println("File closed...");
  }

  
  delay(100);
  



  
}
