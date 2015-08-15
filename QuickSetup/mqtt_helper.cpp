#include <ESP8266WiFi.h>
#include "quick_setup.h"
#include "wifi_helper.h"
#include "mqtt_helper.h"
#include <PubSubClient.h>



MQTT_HELPER_CLASS * mqtt_helper;

WiFiClient wclient;
PubSubClient mqttClient(wclient);

#define BUFFER_SIZE 100
void callback(const MQTT::Publish& pub) {
  Serial.print(pub.topic());
  Serial.print(" => ");
  if (pub.has_stream()) {
    uint8_t buf[BUFFER_SIZE];
    int read;
    while (read = pub.payload_stream()->read(buf, BUFFER_SIZE)) {
      Serial.write(buf, read);
    }
    pub.payload_stream()->stop();
    Serial.println("");
  } else
    Serial.println(pub.payload_string());
}


void MQTT_HELPER_CLASS::mqttSetup(String server, int port, String user, String password, String clientID) {
    mqttServer = server;
    mqttPort = port;
    mqttUser = user;
    mqttPassword = password;
    mqttClientID = clientID;

    mqttClient.set_server(mqtt_helper->mqttServer, mqtt_helper->mqttPort);

    mqtt_helper->ConnectToMQTTServer();   
}

void MQTT_HELPER_CLASS::mqttLoop() {
  
  if (mqttClient.connected()) {
    mqttClient.loop();
  } else {
    mqtt_helper->ConnectToMQTTServer();
  }
  

}

void MQTT_HELPER_CLASS::ConnectToMQTTServer() {
  
  Serial.println("Connecting to MQTT server");
  if (mqttClient.connect(MQTT::Connect(mqttClientID).set_auth(mqttUser, mqttPassword))) {
    Serial.println("Connected to MQTT server");

    // TO-DO // Create inject functions
    mqttClient.set_callback(callback);
    mqttClient.subscribe("/test/DHT");
  } else {
    Serial.println("Could not connect to MQTT server");
  }
  
}

/*
void MQTT_HELPER_CLASS::OnMessageReceive(MessageCallback msgCallback) {
  
}
*/


