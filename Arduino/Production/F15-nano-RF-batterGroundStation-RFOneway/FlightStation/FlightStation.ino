#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  String str_message = "Transmitting: OK" + str(millis());
  char message[50];
  str_message.toCharArray(message, 50);
  radio.write(&message, sizeof(message));

  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
}
