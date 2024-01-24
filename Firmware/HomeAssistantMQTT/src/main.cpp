#include <WiFi.h>
#include <PubSubClient.h>

// Function prototypes
void connectWiFi();
void connectMQTT();

// Replace these values with your Wi-Fi and MQTT broker details
const char* ssid = "Nihal";
const char* password = "nihal@165";
const char* mqtt_server = "192.168.0.117";
const int mqtt_port = 1883;
const char* mqtt_username = "mqtt_user";
const char* mqtt_password = "mqtt_password";
const char* mqtt_topic = "sensors/device001";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectWiFi();

  // Connect to MQTT broker
  client.setServer(mqtt_server, mqtt_port);
  connectMQTT();
}

void loop() {
  // Generate random sensor data
  float temperature = random(20, 30);  // Replace with your actual temperature logic
  float humidity = random(40, 60);     // Replace with your actual humidity logic

  // Create a JSON payload
  String payload = "{\"temperature\":" + String(temperature, 1) + ",\"humidity\":" + String(humidity, 1) + "}";

  // Publish the sensor data to MQTT
  if (client.connected()) {
    client.publish(mqtt_topic, payload.c_str());
  }

  delay(10000);  // Publish every 10 seconds
}

void connectWiFi() {
  Serial.println("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to Wi-Fi");
}

void connectMQTT() {
  Serial.println("Connecting to MQTT broker");
  while (!client.connected()) {
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
