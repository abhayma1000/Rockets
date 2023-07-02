#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Serial.begin(9600);
  Serial.println("Ready for receiving...");
  Serial.println("\n");
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    String str_text = String(text);

    Serial.println(text);
  }
}
