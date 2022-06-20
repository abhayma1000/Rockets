int state = 0;

int button_pin = 2;

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(button_pin, INPUT_PULLUP);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(state == 0) {
    int button_state = digitalRead(button_pin);

    if(button_state == LOW) {
      //Start blinking
      state = 1;
    }
  }

  if(state == 1) {
    digitalWrite(LED_BUILTIN, HIGH);

    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);

    delay(1000);
  }
}
