# SunS-EM3-WiFi-EGSE
ESP8266-based WiFi EGSE code for SunS-EM3

## Warning!
Written in Arduino library for ESP8266 ver. 2.3.0. The library needs a fix in the file:
```
AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\libraries\Wire
```
the define `#define BUFFER_LENGTH` must be `88` or greater (e.g. 255). Note that default value is `32`.

## Joining WiFi network
The settings for WiFi connection are defined in `credentials.h` file. They can be changed according to actual demands:
```
const char* ssid = "SKA.PW";
const char* password = "********";
const uint8_t port = 23;
```

## Verbose debug output via UART
The debug verbose output can be turned on by a define:
```#define DEBUG```
