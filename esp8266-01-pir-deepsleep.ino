#include "ESP8266WiFi.h"
#include <PubSubClient.h>
int powerPin = 2;

const char* WIFI_SSID = "YOURSSID";
const char* WIFI_PASSWORD = "YOURPASSWORD";

const PROGMEM char* MQTT_CLIENT_ID = "sensor/motion";
const PROGMEM char* MQTT_SERVER_IP = "YOURMQTTSERVERIP";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;

const PROGMEM char* MQTT_SENSOR_STATE = "sensor/motion/state";

IPAddress ip(10,0,1,20);
IPAddress gateway(10,0,1,1);
IPAddress subnet(255,255,255,0);
unsigned char ap_mac[18] = { 0xF0, 0x9F, 0xC2, 0x34, 0xAA, 0xFF };

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);

  WiFi.forceSleepWake();
  delay(1);
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 1, ap_mac, true);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  client.connect(MQTT_CLIENT_ID);

  delay(1);
  client.publish(MQTT_SENSOR_STATE, "1");
  delay(299);
  client.publish(MQTT_SENSOR_STATE, "0");
  delay(50);
  
  client.disconnect();
  WiFi.disconnect();
 
  ESP.deepSleep(0, WAKE_RF_DISABLED);
}

void loop() {
  //
}
