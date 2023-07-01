#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

int state = 0;

int led = 5;

char incoming_text[50];

char sending_text[50];

void setup() {

  Serial.begin(9600);

  radio.begin();

  radio.openWritingPipe(addresses[0]);

  radio.openReadingPipe(1, addresses[1]);

  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_MED, RF24_PA_HIGH

  radio.startListening();
}
 
void loop() {
  
  if (radio.available()) {
    radio.read(&incoming_text, sizeof(incoming_text));

    String str_incoming_text = String(incoming_text);

    Serial.print("Received message: ");

    Serial.println(str_incoming_text);

    radio.stopListening();

    String str_sending_text = "Acknowledgement...";

    str_sending_text.toCharArray(sending_text, 50);

    radio.write(&sending_text, sizeof(sending_text));

    Serial.println("Sent acknowledgement...");
  }
}
