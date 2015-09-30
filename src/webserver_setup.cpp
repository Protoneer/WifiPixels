#include "config.h"
#include "webserver_setup.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html_static_resources.h"
#include "webserver_setup.h"

ESP8266WebServer * webServer;

void webserver_url_routing(ESP8266WebServer * webserver){
  webServer = webserver;
  webserver->onNotFound(NotFound);
  
  // Setup URL's
  webserver->on("/wifisetup.html", WifiSetup);
  webserver->on("/", WifiSetup);
  
  // API URL'scan
  webserver->on("/api/v1/access_points.json",  HTTP_GET,  GetAccessPoints);   // List of available Wifi Networks
  
  webserver->on("/api/v1/current_animation",   HTTP_GET,  GetCurrentAnimation); // Get the selected animation 0-3
  webserver->on("/api/v1/current_animation",   HTTP_POST, SetCurrentAnimation); // Set the selected animation 0-3 [0=disabled]

  webserver->on("/api/v1/animation_frame",   HTTP_GET,  GetAnimationFrame);   // Get frame , frame=???
  webserver->on("/api/v1/animation_frame",   HTTP_POST,   SetAnimationFrame);   // Set frame , post data -> frameNumber=0;frameData="???";
  
  webserver->on("/api/v1/uptime",   		HTTP_GET,   GetUpTime);   // Get the time ticks since start-up
  
  
};

String IPtoString(IPAddress IPaddr){
  return String(IPaddr[0]) + '.' + String(IPaddr[1])  + '.' + String(IPaddr[2])  + '.' + String(IPaddr[3]);
}

void NotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webServer->uri();
  message += "\nMethod: ";
  message += (webServer->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webServer->args();
  message += "\n";
  for (uint8_t i = 0; i < webServer->args(); i++) {
    message += " " + webServer->argName(i) + ": " + webServer->arg(i) + "\n";
  }
  webServer->send(404, "text/plain", message);
}

void GetAccessPoints(){
  int n = WiFi.scanNetworks();
  String result = "";
  if(n==0){
    result = "[]";
  } else{
    result="[";
    for (int i = 0; i < n; ++i)
    {
      result += "\"" + String(WiFi.SSID(i)) + "\"";
      if(i!=n-1)
        result += ",";
    }
    result+="]";
  }
  webServer->send(200, "application/json", result);
};

void WifiSetup(){
  // Check for args with connection settings
  if(webServer->args() > 0){
    String temp = "";
    
    temp = webServer->arg("ap");
    if(temp.length() > 0){
      wifi_settings.CLIENT_SSID = temp;
    }else{
      wifi_settings.CLIENT_SSID = "";
    }

    temp = webServer->arg("pw");
    if(temp.length() > 0){
      wifi_settings.CLIENT_Password = temp;
    }else{
      wifi_settings.CLIENT_Password = "";
    }

    // Save Settings
    //wifi_settings.SaveClientSettings();
    // TODO: EEPROM write
    

    wifi_settings.Mode = CLIENT_MODE;
    //wifi_helper->wifiSetup();
  }  
  
  String body = wifi_html;
    
  body.replace("$Network$",String(wifi_settings.Mode == CLIENT_MODE ? wifi_settings.CLIENT_SSID : wifi_settings.AP_SSID));
  body.replace("$Status$",String(wifi_settings.Mode == CLIENT_MODE ? "N/A" : "N/A"));
  body.replace("$IP$",String(IPtoString(wifi_settings.Mode == CLIENT_MODE ? wifi_settings.CLIENT_IP : wifi_settings.AP_IP)));
  body.replace("$Mode$",String(wifi_settings.Mode == CLIENT_MODE ? "Wifi Client" : "Access Point"));

  webServer->send(200, "text/html", body);
};

void GetCurrentAnimation(){
    String result = "[" + String(pixels_settings.currentAnimation) + "]";
	webServer->send(200, "text/plain", result);
};

void SetCurrentAnimation(){    
	// Need Animation number
	
  webServer->send(200, "text/plain", "api/v1/current_animation");
};


String GetFrameString(ANIMATION *ani, int frameIndex, int maxFrameSlots){
	String result = "[";
	char seporator;
	for(int K=0;K<maxFrameSlots;K++)
	{
		result += seporator + "[" + String(ani->Frames[frameIndex][K].R) + "," + String(ani->Frames[frameIndex][K].G) + "," + String(ani->Frames[frameIndex][K].B) + "]";
		seporator = ',';
	}
	result += "]";
	return result;	
}

void GetAnimationFrame(){
	// Need animation frame number
	int frameNumber = 0;
    
    webServer->send(200, "text/plain", GetFrameString(&animations[pixels_settings.currentAnimation],frameNumber,pixel_count));
};

void SetAnimationFrame(){
	// Need frame data.
	
  webServer->send(200, "text/plain", "/api/v1/animation_frame");
};

void GetUpTime(){
	webServer->send(200, "text/plain", millis());
}

