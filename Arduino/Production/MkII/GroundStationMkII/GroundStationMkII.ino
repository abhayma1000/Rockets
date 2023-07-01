#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);

  radio.setPALevel(RF24_PA_MIN);
  
  //Set module as transmitter
  radio.stopListening();




  Serial.println("Enter launch commands...");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() == 1) {
    Serial.println();
    
    String str_message = Serial.readString();

    Serial.print("Message: " + str_message);

    char message[50];

    str_message.toCharArray(message, 50);

        
    radio.write(&message, sizeof(message));

    Serial.println("Message sent to FlightStation...");

  }
}
