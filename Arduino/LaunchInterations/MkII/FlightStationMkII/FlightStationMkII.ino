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

  Serial.begin(9600);

  
  radio.begin();

  radio.openReadingPipe(0, address);

  radio.setPALevel(RF24_PA_MIN);

  radio.startListening();

  Serial.println("Ready for commands...");

  Serial.println("\n");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (radio.available()) {
    char text[32] = "";

    radio.read(&text, sizeof(text));

    String str_text = String(text);

    Serial.println(str_text);

    if(state == 0) {
      Serial.println("Str text is: " + str_text);

      if("a" == "a") {
        Serial.println("They equal");
        state = 1;
      }
      else {
        Serial.println("They dont equal");
      }
    }

    else if(state == 1) {
      if(str_text == "kill launch...") {
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
    Serial.println("Am here");
    digitalWrite(LED_BUILTIN, HIGH);

    delay(500);

    digitalWrite(LED_BUILTIN, LOW);

    delay(500);    
  }
}
