#include <Arduino.h>
#include "Sensor.h"
#include "Pump.h"
#include "Multiplexer.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "MqttClient.h"

Sensor* waterLevelSensor = nullptr;
Sensor* soilMoistureSensor = nullptr;
Pump* waterPump = nullptr;
Multiplexer* multiplexer = nullptr;
MqttClient* mqttClient = nullptr;

const char* ssid = "LM25112012H87";
const char* password =  "Bramenstruik2015";

char* mqttServer = "192.168.1.78";
int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }

    Serial.println();
    Serial.println("-----------------------");
}

void setup() {
    Serial.begin(115200);
    multiplexer = new Multiplexer(D7,D6,D5);
    waterLevelSensor = new Sensor(multiplexer,0,670,985);
    soilMoistureSensor = new Sensor(multiplexer,3,310,746);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP8266Client")) {

            Serial.println("connected");

        } else {

            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);

        }
    }

    client.publish("esp/test", "Hello from ESP8266");
    client.subscribe("esp/test");
}

void loop() {
    client.loop();
}