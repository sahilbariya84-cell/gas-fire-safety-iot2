#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define GAS_PIN 34
#define DHT_PIN 15
#define BUZZER_PIN 25
#define RED_LED 26
#define GREEN_LED 33

const int GAS_THRESHOLD = 2000;              // 0-4095 ADC scale
const float TEMP_THRESHOLD = 50.0;           // deg C, fire/heat limit
DHT dht(DHT_PIN, DHT22);
const char* MQTT_SERVER = "broker.hivemq.com";
const char* TOPIC = "college/safety/alert";  // change to something unique

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    if (!client.connect("esp32-safety-01")) delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setServer(MQTT_SERVER, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int gas = analogRead(GAS_PIN);
  float temp = dht.readTemperature();
  if (isnan(temp)) temp = 0;
  bool alarm = (gas > GAS_THRESHOLD) || (temp > TEMP_THRESHOLD);

  digitalWrite(RED_LED, alarm);
  digitalWrite(GREEN_LED, !alarm);
  digitalWrite(BUZZER_PIN, alarm);

  String msg = String("{\"gas\":") + gas + ",\"temp\":" + temp +
               ",\"status\":\"" + (alarm ? "ALERT" : "SAFE") + "\"}";
  client.publish(TOPIC, msg.c_str());
  Serial.println(msg);
  delay(2000);
}