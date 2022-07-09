//Transmitter for this is GroundStationMkII

#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte address[6] = "00001";

Servo myservo;

int pos = 0;

int lower_bound = 20;

int upper_bound = 150;

void setup() {
  Serial.begin(9600);
  
  myservo.attach(9);


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
      for (pos = upper_bound; pos >= lower_bound; pos -= 1) {
        myservo.write(pos);

        delay(15);
      }
      for (pos = lower_bound; pos <= upper_bound; pos += 1) {
        myservo.write(pos);
      
        delay(15);
      }
    }

    Serial.println("Successfully launched...");
  }
}