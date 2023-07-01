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

  Serial.begin(9600);

  Serial.println("Ready for commands...");

  Serial.println("\n");
}

void loop() {
  if (radio.available()) {
    char text[32] = "";

    radio.read(&text, sizeof(text));

    String str_text = String(text);

    Serial.println("Received text:");

    Serial.println(text);

    char first_case[] =  {'l', 'a', 'u', 'n', 'c', 'h'};

    char second_case[] = {'k', 'i', 'l', 'l'};



    bool equals_first = true;
    bool equals_second = true;

    for (int i = 0; i < sizeof(first_case); i++) {
      if (text[i] != first_case[i]) {
        equals_first = false;
      }
    }

    for (int i = 0; i < sizeof(second_case); i++) {
      if (text[i] != second_case[i]) {
        equals_second = false;
      }
    }




    if(state == 0) {


      if(equals_first) {
        Serial.println("Equals first");
        state = 1;

        Serial.println("\n\n");
      }
      else {
        Serial.println("Doesnt equal first");

        Serial.println("\n\n");
      }
    }

    else if(state == 1) {
      if(equals_second) {
        Serial.println("Equals second");

        state = 0;

        digitalWrite(led, HIGH);

        delay(3000);

        digitalWrite(led, LOW);

        Serial.println("\n\n");
      }
    }
    

  }

  if(state == 0) {
    digitalWrite(led, LOW);
  }

  if(state == 1) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);      
  }
}

bool char_equal(char inputted[], char actual[]) {

  for (int i = 0; i < sizeof(actual); i++) {
    if (actual[i] != inputted[i]) {
      return false;
    }
  }

  return true;
}
