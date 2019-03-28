#define LED_TEST 16
//#define LED_TEST 2    Model: CH340
#define BTN_FLASH 0

bool flash;
int i;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_TEST, OUTPUT);
  pinMode(BTN_FLASH, INPUT);
  Serial.begin(115200);
  //Interrupts
  attachInterrupt(digitalPinToInterrupt(BTN_FLASH), Button, FALLING);
  i=1;
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

void Button() {
  Serial.println(i++);
}
