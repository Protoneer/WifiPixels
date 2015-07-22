#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <NeoPixelBus.h>
#include <EEPROM.h>

// LED Settings
#define pixelCount 16
#define cycles 20
int LEDSettings[cycles][pixelCount][3] = {0};

int ledIndex;
int ledIndexMax;


// Wifi Settings
const char* ssid = "WifiPixels";
const char* password = "";
const int led = 0;



NeoPixelBus strip = NeoPixelBus(pixelCount, 12);
MDNSResponder mdns;
ESP8266WebServer server(80);

int blue=0;
int red=0;
int green=0;

void handleRoot(){
  digitalWrite(led, 0);

  if(server.args() > 0){
    String temp = "";

    // red
    temp = server.arg("red");
    if(temp.length() > 0){
      red = temp.toInt();
      EEPROM.write(0,red);
      EEPROM.commit();
    }

    // green
    temp = server.arg("green");
    if(temp.length() > 0){
      green = temp.toInt();
      EEPROM.write(1,green);
      EEPROM.commit();
    }
    
    // blue
    temp = server.arg("blue");
    if(temp.length() > 0){
      blue = temp.toInt();
      EEPROM.write(2,blue);
      EEPROM.commit();
    }
  }

  String body = 
  "<!DOCTYPE html>"
  "<html>"
  "<body>"
  "<form action=""index.html"">"
  "Red:<br><input type=""text"" name=""red"" value=""$R$""><br>"
  "Green:<br><input type=""text"" name=""green"" value=""$G$""><br>"
  "Blue:<br><input type=""text"" name=""blue"" value=""$B$""><br>"
  "<input type=""submit"" value=""Set"">"
  "</form>"
  "</body>"
  "</html>";

  body.replace("$R$",String(red));
  body.replace("$G$",String(green));
  body.replace("$B$",String(blue));  

  server.send(200, "text/html", body);
  digitalWrite(led, 1);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}


void setup()
{
  EEPROM.begin(512);
  red = EEPROM.read(0);
  green = EEPROM.read(1);
  blue = EEPROM.read(2);
  
  // this resets all the neopixels to an off state
  strip.Begin();
  SetAll(RgbColor(0,0, 0));
  strip.Show();

  ledIndex = 0;
  ledIndexMax = pixelCount-1;



  // Serial
  Serial.begin(115200);
  Serial.println("");

  // Wifi

  
  //WiFi.softAP(ssid,password);
  WiFi.softAP(ssid,password,7);  // Open connection

  // Wifi LED
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);

  // Routing Table
  server.on("/index.html", handleRoot);
  server.on("/", handleRoot);
  
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  ledIndex++;
  if(ledIndex > ledIndexMax){
    ledIndex = 0;
  }

  CyclePixels(ledIndex);
  server.handleClient();
}

void CyclePixels(int K){
    SetAll(RgbColor(0,0, 0));
    strip.SetPixelColor(K, RgbColor(red,green, blue));
    strip.Show();
    delay(20);
}

void SetAll(RgbColor colour){
  for(int K=0;K<pixelCount;K++){
    strip.SetPixelColor(K, colour);
  }
}
