#include <ESP8266WiFi.h>
#include "wifi_setup.h"
#include "config.h"

void wifi_setup(struct wifi_settings_struct *settings){
  
	if (settings->Mode == CLIENT_MODE){
		WifiClient(settings);
	} else {
		WifiAP(settings);
	}  
}


void WifiClient(struct wifi_settings_struct *settings){
  
  char ssid_buff[settings->CLIENT_SSID.length()+1];
  char password_buff[settings->CLIENT_Password.length()+1];
  settings->CLIENT_SSID.toCharArray(ssid_buff,settings->CLIENT_SSID.length()+1);
  settings->CLIENT_Password.toCharArray(password_buff,settings->CLIENT_Password.length()+1);

  
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
    settings->Mode = CLIENT_MODE;

    settings->CLIENT_IP = WiFi.localIP();

    Serial.println("");
    Serial.println("WiFi Client connected");  
    Serial.println("IP address: ");
    Serial.println(settings->CLIENT_IP);    
  } else{
    settings->Mode = AP_MODE;

    Serial.println("WiFi Client not connected!!!");  
    wifi_setup(settings);
  }
}

void WifiAP(struct wifi_settings_struct *settings){
  char apssid_buff[settings->AP_SSID.length()+1];
  char appassword_buff[settings->AP_Password.length()+1];
  settings->AP_SSID.toCharArray(apssid_buff,settings->AP_SSID.length()+1);
  settings->AP_Password.toCharArray(appassword_buff,settings->AP_Password.length()+1);

  //Stop Client
  WiFi.disconnect(true);

  WiFi.mode(WIFI_AP);  
  WiFi.softAP((const char*)apssid_buff, (const char*)appassword_buff, 7); // Open connection  

  Serial.println("WiFi AP Started...");  

  settings->Mode = AP_MODE;
  settings->AP_IP = WiFi.softAPIP();
  
  Serial.println("IP address: ");
  Serial.println(settings->AP_IP); 
  
}
