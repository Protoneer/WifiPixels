#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "eeprom_lib.h"
#include "config.h"

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

void LoadClientSettings(wifi_settings_struct * settings){
  char ssid[32];
  char pw[32];
  if(!read_string(0,ssid,32))Serial.println("SSID Read Failed...");
  if(!read_string(33,pw,32))Serial.println("PW Read Failed...");


  settings->CLIENT_SSID = ssid;
  settings->CLIENT_Password = pw;
  settings->Mode = CLIENT_MODE;
  
}

void SaveClientSettings(wifi_settings_struct * settings){  
  if(!write_string(0,settings->CLIENT_SSID,32))Serial.println("SSID Not Saved");
  if(!write_string(33,settings->CLIENT_Password,32))Serial.println("PW Not Saved");
}


