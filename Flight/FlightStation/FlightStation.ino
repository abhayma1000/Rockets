//states: pre-setup, setup, logging, after: 0, 1, 2, 3

int state = 0;

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if (state == 0) {
    
    //if the button is pressed
      state = 1;
  }

  if (state == 1) {
    //lights are flashing

    //wait for {TIME}
    //state = 2
  }

  if (state == 2) {
    //Log data

    //Log for {TIME2}

    //state = 3
  }

  if (state == 3) {
    //Start flashing the lights
    //Stop logging and save the data
  }
}
