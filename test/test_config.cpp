#include "gtest/gtest.h"
#include "config.h"

wifi_settings_struct      wifi_settings;
//mqtt_settings_struct      mqtt_settings;
//pixels_settings_struct    pixels_settings;


TEST(example, add)
{
    ASSERT_TRUE(wifi_settings.AP_SSID == "WifiPixels");
    ASSERT_TRUE(wifi_settings.AP_Password == "");
    ASSERT_TRUE(wifi_settings.CLIENT_SSID == "");
    ASSERT_TRUE(wifi_settings.CLIENT_Password == "");
    ASSERT_TRUE(wifi_settings.Mode == 1);

	//AP_IP     = IPAddress(192,168,4,1);  // Default Access point ip
	//CLIENT_IP   = IPAddress(127,0,0,1);    // Default assigned by Wifi router.	
}



