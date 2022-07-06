#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte addresses[][6] = {"00001", "00002"};

char message[50];

char incoming_message[50];

void setup() {
  Serial.begin(9600);

  radio.begin();
  
  //set the address
  radio.openWritingPipe(addresses[1]);

  radio.openReadingPipe(1, addresses[0]);

  radio.setPALevel(RF24_PA_MIN);

  String str_message = "switch";

  str_message.toCharArray(message, 50);

  radio.stopListening();
    
  radio.write(&message, sizeof(message));

  Serial.println("Message sent...");

  delay(5);

  radio.startListening();
}

void loop() {

    if (radio.available()) {
      char incoming_text[50] = "";

      Serial.println("Received something");

      radio.read(&incoming_text, sizeof(incoming_text));

      String str_incoming_text = String(incoming_text);

      Serial.print("Incoming message: ");

      Serial.println(str_incoming_text);
    }


}
