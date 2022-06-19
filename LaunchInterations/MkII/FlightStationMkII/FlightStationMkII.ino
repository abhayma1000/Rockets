//Just Arduino Nano, RF module, and battery
//Once signal is sent to nano via RF, just blinks
//Once another signal is sent to nano via RF, stops blinking
//Meant to show RF module works
//WIP

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int state = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);

  
  radio.begin();

  radio.openReadingPipe(0, address);

  radio.setPALevel(RF24_PA_MIN);

  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (radio.available()) {
    char text[32] = "";

    radio.read(&text, sizeof(text));

    Serial.println(text);



    if(state == 0) {
      if(text == "activate launch...") {
        state = 1;
      }
    }

    else if(state == 1) {
      if(text == "kill launch...") {
        state == 0;
      }
    }
    

  }

  if(state == 0) {
    digitalWrite(LED_BUILTIN, HIGH);

    delay(3000);

    digitalWrite(LED_BUILTIN, LOW);
  }

  if(state == 1) {
    digitalWrite(LED_BUILTIN, HIGH);

    delay(500);

    digitalWrite(LED_BUILTIN, LOW);

    delay(500);    
  }
}
