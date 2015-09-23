#include "config.h"
#include <ESP8266WiFi.h>
#include "wifi_setup.h"



void wifi_setup(){
	if (wifi_settings.Mode == CLIENT_MODE){
		WifiClient();
	} else {
		WifiAP();
	}  
}


void WifiClient(){
  
  char ssid_buff[wifi_settings.CLIENT_SSID.length()+1];
  char password_buff[wifi_settings.CLIENT_Password.length()+1];
  wifi_settings.CLIENT_SSID.toCharArray(ssid_buff,wifi_settings.CLIENT_SSID.length()+1);
  wifi_settings.CLIENT_Password.toCharArray(password_buff,wifi_settings.CLIENT_Password.length()+1);

  
  Serial.println("Connecting with...");
  Serial.print('[');
  Serial.print(ssid_buff);
  Serial.println(']');
  Serial.print('[');
  Serial.print(password_buff);
  Serial.println(']');
  

  
  WiFi.mode(WIFI_STA);
  WiFi.begin((const char*)ssid_buff, (const char*)password_buff);

  if (WiFi.waitForConnectResult() == WL_CONNECTED){
    wifi_settings.Mode = CLIENT_MODE;

    wifi_settings.CLIENT_IP = WiFi.localIP();

    Serial.println("");
    Serial.println("WiFi Client connected");  
    Serial.println("IP address: ");
    Serial.println(wifi_settings.CLIENT_IP);    
  } else{
    wifi_settings.Mode = AP_MODE;

    Serial.println("WiFi Client not connected!!!");  
    wifi_setup();
  }
}

void WifiAP(){
  char apssid_buff[wifi_settings.AP_SSID.length()+1];
  char appassword_buff[wifi_settings.AP_Password.length()+1];
  wifi_settings.AP_SSID.toCharArray(apssid_buff,wifi_settings.AP_SSID.length()+1);
  wifi_settings.AP_Password.toCharArray(appassword_buff,wifi_settings.AP_Password.length()+1);

  //Stop Client
  WiFi.disconnect(true);

  WiFi.mode(WIFI_AP);  
  WiFi.softAP((const char*)apssid_buff, (const char*)appassword_buff, 7); // Open connection  

  Serial.println("WiFi AP Started...");  

  wifi_settings.Mode = AP_MODE;
  wifi_settings.AP_IP = WiFi.softAPIP();
  
  Serial.println("IP address: ");
  Serial.println(wifi_settings.AP_IP); 
  
}
