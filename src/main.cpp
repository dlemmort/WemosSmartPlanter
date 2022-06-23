#include <Arduino.h>
#include <cstdio>
#include "Sensor.h"
#include "Pump.h"
#include "Multiplexer.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"


//Devices
Sensor* waterLevelSensor = nullptr;
Sensor* soilMoistureSensor = nullptr;
Pump* waterPump = nullptr;
Multiplexer* multiplexer = nullptr;

//WiFi
char* ssid = "LM25112012H87";
const char* password =  "Bramenstruik2015";

//MQTT
const char* mqttServer = "192.168.1.78";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
String waterLevel_str;
String soilMoisture_str;
char waterLevel[20];
char soilMoisture[20];

char mqttIn[8];
int mode;
int value;
char outPayload[50];


//WiFiClient
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
unsigned long interval = 30000UL;


void messageReader(char *topic, byte *payload, unsigned int length) {
    int newLength = length;

    Serial.println("");
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    for (int i=0;i<length;i++){
        mqttIn[i] = (char)payload[i];
    }

    if (mqttIn[0] < '0' || mqttIn[1] != ','){
        Serial.println("Incorrect MQTT format");
    }
    else{
        mode = mqttIn[0] - '0';
        memset(mqttIn,0,sizeof(mqttIn));
        newLength -= 2;
        for (int i = 0; i < newLength;i++){
            mqttIn[i] = (char)payload[i+2];
        }
        value = atoi(mqttIn);
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    messageReader(topic, payload, length);

    switch(mode){
        case 0: {
            //set mqtt publish frequency (input in minutes to milliseconds)
            interval = value * 60000UL;
        } break;
        case 1: {
            //give water for x seconds
            waterPump->giveWater(value);
        } break;
        case 2: {
            //publish current watersensorvalue
            std::sprintf(outPayload,"%d",waterLevelSensor->getSensorValue());
            client.publish("plant1/debug/waterlevel",outPayload);
        } break;
        case 3: {
            //publish current soil moisture value
            std::sprintf(outPayload,"%d",soilMoistureSensor->getSensorValue());
            client.publish("plant1/debug/soilmoisturevalue",outPayload);
        } break;
        case 4: {
            //set water level min value
            waterLevelSensor->setMinValue(value);
        } break;
        case 5: {
            //set water level max value
            waterLevelSensor->setMaxValue(value);
        } break;
        case 6: {
            //set moisture min value
            soilMoistureSensor->setMinValue(value);
        } break;
        case 7: {
            //set moisture max value
            soilMoistureSensor->setMaxValue(value);
        } break;
        case 8: {
            //publish sensor values
            std::printf(outPayload,"%d",waterLevelSensor->getPercentageValue());
            client.publish("home/plant/1/waterLevel",outPayload);
            std::printf(outPayload,"%d",soilMoistureSensor->getPercentageValue());
            client.publish("home/plant/1/moisture",outPayload);
        }
    }


}

void setup() {
    Serial.begin(115200);
    multiplexer = new Multiplexer(D7,D6,D5);
    waterLevelSensor = new Sensor(multiplexer,1,200,799);
    soilMoistureSensor = new Sensor(multiplexer,0,310,746);
    waterPump = new Pump(D1);



    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

            Serial.println("connected");

        } else {

            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);

        }
    }
    client.subscribe("home/plant/1/in");
}

void reconnect() {
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
            Serial.println("connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void loop() {
    if (!client.connected()){
        reconnect();
    }

    client.loop();

    unsigned long now = millis();

    if(now - lastMsg > interval) {
        lastMsg = now;

        waterLevel_str = String(waterLevelSensor->getPercentageValue());
        waterLevel_str.toCharArray(waterLevel,waterLevel_str.length()+1);
        client.publish("Plant1/waterLevel",waterLevel);

        soilMoisture_str = String(soilMoistureSensor->getPercentageValue());
        soilMoisture_str.toCharArray(soilMoisture,soilMoisture_str.length()+1);
        client.publish("Plant1/soilMoisture", soilMoisture);

    }
}