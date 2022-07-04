#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int state = 0;

int led = 5;

void setup() {

  Serial.begin(9600);
  
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

  radio.begin();

  radio.openReadingPipe(0, address);

  radio.setPALevel(RF24_PA_MIN);

  radio.startListening();
  

}
 
void loop() {
  
  if (radio.available()) {
    char text[32] = "";

    radio.read(&text, sizeof(text));

    String str_text = String(text);

    char test_case[] =  {'s', 'w', 'i', 't', 'c', 'h'};

    bool equals_case = true;

    for (int i = 0; i < sizeof(test_case); i++) {
      if (text[i] != test_case[i]) {
        equals_case = false;
      }
    }

    if (equals_case) {
      Serial.println("Signal received...");
      if (state == 0) {
        state = 1;
      }
      else if (state == 1) {
        state = 0;
      }
    }
  }

  if (state == 0) {
    digitalWrite(led, LOW);
  }
  else if (state == 1) {
    digitalWrite(led, HIGH);
  }
}
