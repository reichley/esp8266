/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"
#include <PubSubClient.h>
int powerPin = 2;

const char* WIFI_SSID = "YOURSSID";
const char* WIFI_PASSWORD = "YOURPASSWORD";

const PROGMEM char* MQTT_CLIENT_ID = "esp8266/motion";
const PROGMEM char* MQTT_SERVER_IP = "10.0.1.237";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;

const PROGMEM char* MQTT_SENSOR_STATE = "home/sensor/motion/state";

ADC_MODE(ADC_VCC);

IPAddress ip(10,0,1,20);
IPAddress gateway(10,0,1,1);
IPAddress subnet(255,255,255,0);

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup_wifi() {
  delay(10);

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int Attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Attempt++;
    //Serial.print(".");
    if (Attempt == 100)
    {
      //Serial.println("");
      //Serial.println("Could not connect to WiFi. Sleeping for 1 minute.");
      delay(10);
      ESP.deepSleep(0, WAKE_RF_DISABLED);
    }
  }
  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
}

void recon_mqtt() {
  int Attempt2 = 0;
  while (client.connected() == false) {
    delay(50);
    Attempt2++;
    //Serial.print(".");
    if (Attempt2 == 150)
    {
      //Serial.println("");
      //Serial.println("Could not connect to MQTT. Sleeping for 1 minute.");
      WiFi.disconnect();
      delay(10);
      ESP.deepSleep(0, WAKE_RF_DISABLED);
    }
  }
}

void setup() {
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);

  WiFi.forceSleepWake();
  
  setup_wifi();
  
  float v = ESP.getVcc() / 1000.0;

  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  client.connect(MQTT_CLIENT_ID);

  recon_mqtt();

  delay(1);
  client.publish(MQTT_SENSOR_STATE, "1");
  delay(50);
  client.publish(MQTT_SENSOR_BATT, String(v).c_str());
  delay(249);
  client.publish(MQTT_SENSOR_STATE, "0");
  delay(50);
  
  client.disconnect();
  WiFi.disconnect();
 
  ESP.deepSleep(0, WAKE_RF_DISABLED);
}

void loop() {
  //
}
