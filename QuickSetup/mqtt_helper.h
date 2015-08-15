#include <ESP8266WiFi.h>

//typedef void (*MessageCallback)  (const MQTT::Publish& pub); 

class MQTT_HELPER_CLASS
{
  public:
    void mqttSetup(String server,int port,String user,String password,String clientID);
    void mqttLoop();
    //void OnMessageReceive();
    //void ConnectToMQTTServer(MessageCallback msgCallback);
    void ConnectToMQTTServer();
    String mqttServer;
    int mqttPort;
    String mqttUser;
    String mqttPassword;
    String mqttClientID;
};

extern MQTT_HELPER_CLASS * mqtt_helper;
