#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       ""
#define WLAN_PASS       ""

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""

//HARDWARE NodeMCU_V1CP2102
#define LED_TEST 16
#define BTN_FLASH 0
#define LED_TX  2


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish button = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/button");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);

  //Ports_Configuration
  pinMode(LED_TEST, OUTPUT);
  digitalWrite(LED_TEST, !LOW);  //Turnoff
  pinMode(BTN_FLASH, INPUT);

  //Interrupts
  attachInterrupt(digitalPinToInterrupt(BTN_FLASH), upload, CHANGE);

  //Start info
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&led);
}


void loop() {
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &led) {
      Serial.print(F("Got: "));
      Serial.println((char *)led.lastread);

      if(strcmp((char *)led.lastread, "ON") == 0)
      {
        digitalWrite(LED_TEST, !HIGH);
      }
      if(strcmp((char *)led.lastread, "OFF") == 0)
      {
        digitalWrite(LED_TEST, !LOW);
      }     
    }
  }
}

void upload() {
  // Notice MQTT button state
  bool flash;
  flash = !digitalRead(BTN_FLASH);
  // Now we can publish stuff!
  Serial.print(F("\nSending button val "));
  Serial.print(flash);
  Serial.print("...");  
    
  if (! button.publish(flash)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
