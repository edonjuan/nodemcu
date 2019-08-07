// 2019 Refrigerator_v1.0
// Author: edonjuan

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//HARDWARE NodeMCU_V1CP2102
#define LED_TEST 16
#define BTN_FLASH 0

// Update these with values suitable for your network.
const char* ssid = "Intel-IoT";
const char* password = "1N73RN37D3L45C0545";
const char* mqtt_server = "172.31.112.81";
const char* mqtt_username = "mqtt_user";
const char* mqtt_password = "mqtt_pass";

// Objects
WiFiClient espClient;
PubSubClient client(espClient);



void setup()
{
  setup_wifi(); 
  client.setClient(espClient);
  client.setServer(mqtt_server, 1883);

  // Function to call (Data incoming)
  client.setCallback(callback);

  pinMode(LED_TEST, OUTPUT);
  digitalWrite(LED_TEST, !LOW);

  //Interrupts
  attachInterrupt(digitalPinToInterrupt(BTN_FLASH), upload, CHANGE);
}
 
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void setup_wifi() {
  Serial.begin(115200);
  delay(100);
 
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

  String strMessage;
  String strTopic;
  String strPayload;
  
  payload[length] = '\0';
  strTopic = String((char*)topic);
  strMessage = String((char*)payload);
  Serial.println(strTopic);
  Serial.println(strMessage);


  if(strMessage == "ON")  // BOOLEAN MESSAGES
  {
     
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

  client.publish("ha/button", "ON"); 
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient",mqtt_username,mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.subscribe("ha/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
