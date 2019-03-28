#define LED_TEST 16
//#define LED_TEST 2    Model: CH340

int i;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_TEST, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(LED_TEST, !HIGH);
  for(i=0; i<100; i++)
  {
    Serial.println(i);
    delay(20);  
  }

  digitalWrite(LED_TEST, !LOW);
  for(i=100; i>=1; i--)
  {
    Serial.println(i); 
    delay(20); 
  }
}
