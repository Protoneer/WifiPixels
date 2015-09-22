#ifndef wifi_setup_h
#define wifi_setup_h

	#include <ESP8266WiFi.h>
	#include <ESP8266WebServer.h>
  #include "config.h"
  
	void wifi_setup(struct wifi_settings_struct *settings);
  void WifiClient(struct wifi_settings_struct *settings);
  //void WifiAP(struct wifi_settings_struct *settings);
	
#endif
