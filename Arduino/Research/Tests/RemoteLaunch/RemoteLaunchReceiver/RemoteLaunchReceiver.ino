//Transmitter for this is GroundStationMkII

#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte address[6] = "00001";

Servo myservo;

int lower_bound = 40;

int upper_bound = 170;

int pos = upper_bound;

void setup() {
  Serial.begin(9600);
  
  myservo.attach(9);

  myservo.write(upper_bound);

  radio.begin();

  radio.openReadingPipe(0, address);

  radio.setPALevel(RF24_PA_MIN);

  radio.startListening();

  Serial.println("Ready for commands...");

  Serial.println("\n");
}

void loop() {

  if (radio.available()) {
    char text[32] = "";

    radio.read(&text, sizeof(text));

    Serial.println("Received test: ");

    String str_text = String(text);

    Serial.println(text);

    char test_case[] =  {'l', 'a', 'u', 'n', 'c', 'h'};

    bool equals_case = true;

    for (int i = 0; i < sizeof(test_case); i++) {
        if (text[i] != test_case[i]) {
          equals_case = false;
        }
      }

    if (equals_case) {
      myservo.write(upper_bound);

      delay(4000);

      myservo.write(lower_bound);

      delay(4000);

      myservo.write(upper_bound);
    }

    Serial.println("Successfully launched...");
  }
}
