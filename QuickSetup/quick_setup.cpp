#include "quick_setup.h"
#include <EEPROM.h>
#include "webinterface.h"
#include "wifi_helper.h"

QUICK_SETUP_CLASS * quick_setup;

//read a string 
//a string is multibyte + \0, this is won't work if 1 char is multibyte like chinese char 
bool read_string(word pos, char byte_buffer[], word size_max)
{
  //check if parameters are acceptable
  if (size_max==0 ||  pos+size_max+1 > EEPROM_SIZE || byte_buffer== NULL)return false;
  byte b=0;
  word i=0;
  //read first byte
  b = EEPROM.read(pos + i);
  byte_buffer[i]=b;
  i++;
  //read until max size is reached or \0 is found
  while (i<size_max+1 && b!=0)
  {
    b = EEPROM.read(pos+i);
    byte_buffer[i]=b; 
    i++;
  } 
  //if it is a string be sure there is an 0 at the end
  if (b!=0)byte_buffer[i-1]=0x00; 
  return true;
}

//write a string (array of byte with a 0x00  at the end)
bool write_string(word pos, String value, word size_buffer)
{
  char byte_buffer[value.length()+1];
  value.toCharArray(byte_buffer, value.length()+1);
  
  //check if parameters are acceptable
  if (size_buffer==0 ||  pos+size_buffer+1 > EEPROM_SIZE || byte_buffer== NULL)return false;
  //copy the value(s)
  for (word i = 0; i < size_buffer; i++) {
    EEPROM.write(pos + i, byte_buffer[i]);
  }
  
  //0 terminal
  EEPROM.write(pos + size_buffer, 0x00);
  EEPROM.commit();
  return true;
}



void QUICK_SETUP_CLASS::Start(){
  wifi_helper = new WIFI_HELPER_CLASS();
  wifi_helper->wifiSetup();

  
  web_interface = new WEBINTERFACE_CLASS(); 
  web_interface->WebServer();
}

void QUICK_SETUP_CLASS::Handle_Requests(){
  web_interface->handleClient();
}

void QUICK_SETUP_CLASS::LoadClientSettings(){
  char ssid[32];
  char pw[32];
  if(!read_string(0,ssid,32))Serial.println("SSID Read Failed...");
  if(!read_string(33,pw,32))Serial.println("PW Read Failed...");


  quick_setup->CLIENT_SSID = ssid;
  quick_setup->CLIENT_Password = pw;
  quick_setup->Mode = CLIENT_MODE;
  
}

void QUICK_SETUP_CLASS::SaveClientSettings(){  
  if(!write_string(0,quick_setup->CLIENT_SSID,32))Serial.println("SSID Not Saved");
  if(!write_string(33,quick_setup->CLIENT_Password,32))Serial.println("PW Not Saved");
}
