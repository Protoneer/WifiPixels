#ifndef eeprom_lib_h
#define eeprom_lib_h
#include "config.h"

void SaveClientSettings(wifi_settings_struct settings);
void LoadClientSettings(wifi_settings_struct * settings);

#endif
