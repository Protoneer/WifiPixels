# QuickSetup

Easy way to connect an ESP8266 IOT device to a Wifi Network.

* When the device is powered the first time it will start as an Access Point. (IP:10.0.0.1)
* The Access Point can be connected to, from the above IP the device can be connected to a Wifi Network as a Client
* On the first connection as a client the Access Point will be switched off.
* Should the Wifi Connection fail after 3 attempts the unit will go in recovery mode and swith back to an Access Point. From where it can be connected to a network again.

External Libs:
* https://github.com/Imroy/pubsubclient
* https://github.com/Makuna/NeoPixelBus
