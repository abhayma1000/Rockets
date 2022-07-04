#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

char message[50];

void setup() {
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);

  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_MED, RF24_PA_HIGH
  
  //Set module as transmitter
  radio.stopListening();

  String str_message = "switch";

  str_message.toCharArray(message, 50);
}

void loop() {    
    radio.write(&message, sizeof(message));

    delay(1000);
}
