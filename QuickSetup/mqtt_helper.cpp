#include <ESP8266WiFi.h>
#include "quick_setup.h"
#include "wifi_helper.h"
#include "mqtt_helper.h"
#include <PubSubClient.h>



MQTT_HELPER_CLASS * mqtt_helper;

WiFiClient wclient;
PubSubClient mqttClient(wclient);

void MQTT_HELPER_CLASS::mqttSetup(String server, int port, String user, String password, String clientID,callback_t cb,String topic) {
    mqttServer = server;
    mqttPort = port;
    mqttUser = user;
    mqttPassword = password;
    mqttClientID = clientID;
    mqttCB = cb;
    mqttSubscriptionTopic = topic;

    mqttClient.set_server(mqtt_helper->mqttServer, mqtt_helper->mqttPort);

    mqtt_helper->ConnectToMQTTServer(mqtt_helper->mqttCB);   
}

void MQTT_HELPER_CLASS::mqttLoop() {
  
  if (mqttClient.connected()) {
    mqttClient.loop();
  } else {
    mqtt_helper->ConnectToMQTTServer(mqtt_helper->mqttCB);
  }
  

}

void MQTT_HELPER_CLASS::ConnectToMQTTServer(callback_t cb) {
  
  Serial.println("Connecting to MQTT server");
  if (mqttClient.connect(MQTT::Connect(mqttClientID).set_auth(mqttUser, mqttPassword))) {
    Serial.println("Connected to MQTT server");

    // TO-DO // Create inject functions
    mqttClient.set_callback(cb);
    mqttClient.subscribe(mqttSubscriptionTopic);
  } else {
    Serial.println("Could not connect to MQTT server");
  }
  
}

/*
void MQTT_HELPER_CLASS::OnMessageReceive(MessageCallback msgCallback) {
  
}
*/


