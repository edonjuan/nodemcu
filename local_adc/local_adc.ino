#define LED_TEST 16
//#define LED_TEST 2    Model: CH340
#define SENSOR  A0

int adc;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_TEST, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {

  adc = analogRead(SENSOR);
  Serial.println(adc);

  if(adc>512)
  {
    digitalWrite(LED_TEST, !HIGH);
  }
  else
  {
    digitalWrite(LED_TEST, !LOW);
  }  
  delay(200); 
}
