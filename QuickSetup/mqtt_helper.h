#ifndef MQTT_H
#define MQTT_H
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

typedef void(*callback_t)(const MQTT::Publish&);

class MQTT_HELPER_CLASS
{
  public:
    void mqttSetup(String server,int port,String user,String password,String clientID,callback_t cb,String topic);
    void mqttLoop();
    void ConnectToMQTTServer(callback_t cb);
    String mqttServer;
    int mqttPort;
    String mqttUser;
    String mqttPassword;
    String mqttClientID;
    callback_t mqttCB;
    String mqttSubscriptionTopic;    
};

extern MQTT_HELPER_CLASS * mqtt_helper;

#endif
