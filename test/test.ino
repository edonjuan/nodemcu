#define LED_TEST 16
#define BTN_FLASH 0
#define LED_TX  2

bool flash;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_TEST, OUTPUT);
  pinMode(BTN_FLASH, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  flash = !digitalRead(BTN_FLASH);
  if(flash)
  {
    digitalWrite(LED_TEST, !HIGH);   // turn the LED on (HIGH is the voltage
  }
  else
  {
    digitalWrite(LED_TEST, !LOW);
  }
  delay(50); 
}
