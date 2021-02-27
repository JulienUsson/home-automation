# Automatic Watering

# Board 

[UNO+WiFi R3 ATmega328P+ESP8266, 32Mb flash, USB-TTL CH340G, Micro-USB](https://robotdyn.com/uno-wifi-r3-atmega328p-esp8266-32mb-flash-usb-ttl-ch340g-micro-usb.html)

## ATmega382P

To upload the sketch to the board switches 3 and 4 must be on, the others to off.

### Arduino IDE config

Board: Arduino UNO

## ESP8266

To upload the sketch to the board switches 5,6 and 7 must be on, the others to off.
To test it, you must only have switches 5 and 6 to on.

### Arduino IDE config

Board: Generic ESP8266 Module
Upload Speed: 115200
Flash Size: 4MB (FS:2MB)
Flash Mode: DIO
Reset Method: no dtr (aka ck)

# Dependencies

[Arduino JSON](https://arduinojson.org/)

[Wifi manager](https://github.com/tzapu/WiFiManager)

[ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)

# Starting

Switches 1 and 2 must be on, the others to off then turn the power on.

# How to configure wifi

Connect to wifi access point `Garden` with password `WATER`.
Connect to `http://192.168.1.1` and configure wifi.

# How to use

## Get infos

Send a GET request to `http://{board-ip}/` to get infos like if the water tank has water.

## Water garden
Send a POST request to `http://{board-ip}/water` with body `{duration: 1000}`. Duration is in second.