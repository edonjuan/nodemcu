// DIY
// Challenge
// FLASH YOUR NODEMCU
// TODO - CHANCE YOUR IP ADDRESS

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//HARDWARE NodeMCU_V1CP2102
#define LED_TEST 16
#define BTN_FLASH 0

// Update these with values suitable for your network.
const char* ssid = "DIPLOMADO-CIC40";
const char* password = "";

// TODO                    // YOUR IP
const char* mqtt_server = "172.31.112.XX";

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
}
 
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();  
  digitalWrite(LED_TEST, !LOW);
  upload();
  delay(500);
  digitalWrite(LED_TEST, !HIGH);
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


  if((strTopic == "topic")&&(strMessage == "ON"))
  {
     
  }
  if((strTopic == "topic")&&(strMessage == "OFF"))
  {
     
  }
}

void upload() {
  // Notice MQTT button state
  bool flash;
  long randomnum;
  
  flash = !digitalRead(BTN_FLASH);
  // Now we can publish stuff!
  Serial.print(F("\nSending button val "));
  Serial.print(flash);
  Serial.println("...");  

  if(flash)
  {
    client.publish("binary_sensors/mqtt/diy/01/state_topic", "ON"); 
  }
  else
  {
    client.publish("binary_sensors/mqtt/diy/01/state_topic", "OFF"); 
  }

  randomnum = random(0,100);
  sendmqtt("sensors/mqtt/diy/01/state_topic", randomnum);

  Serial.print(F("\nSending random val "));
  Serial.print(randomnum);
  Serial.println("..."); 
  // TOPIC
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.subscribe("#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void sendmqtt(char* topic, float data)
{
  String data_str;
  char data_chr[50];
  int data_int;

  data_int = (int)data;
  if(data_int == data)
  {
    data_str = String(data_int);
  }
  else
  {
    data_str = String(data);
  }
  data_str.toCharArray(data_chr, data_str.length() + 1); 
  client.publish(topic, data_chr);  
}
