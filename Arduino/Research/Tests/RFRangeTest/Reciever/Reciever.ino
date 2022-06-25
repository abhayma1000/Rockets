#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int state = 0;

int led = 5;

void setup() {
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
      switch (state) {
        case 0:
          state = 1;
        case 1:
          state = 0; 
      }
    }

  }   

  if (state == 0) {
    digitalWrite(led, HIGH);
  }
  else if (state == 1) {
    digitalWrite(led, LOW);
  }

}
