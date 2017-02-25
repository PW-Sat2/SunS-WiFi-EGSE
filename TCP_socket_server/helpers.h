#ifndef HELPERS_H_
#define HELPERS_H_


#define DEBUG

#ifdef DEBUG
#define PRINTLND Serial.println
#else
#define PRINTLND(text) ((void)0)
#endif

#ifdef DEBUG
#define PRINTD Serial.print
#else
#define PRINTD(text) ((void)0)
#endif

#include <stdarg.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

extern WiFiClient serverClient;

void Printf(char *fmt, ... ){
        char buf[255]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 255, fmt, args);
        va_end (args);
        Serial.print(buf);
}

void TCPPrintf(char *fmt, ... ){
        char buf[255]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 255, fmt, args);
        va_end (args);
        serverClient.print(buf);
}

#endif  // HELPERS_H_
