#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "WiFi_Connection.h"
#include "helpers.h"
#include "SunS_interface.h"
#include <stdlib.h>

WiFiServer server(port);
WiFiClient serverClient;
bool should_be_connected = false;
size_t buff_size = 255;

SunS_Access SunS(0x44);
constexpr uint8_t IRQ = 5;


void setup(){
  Wire.pins(2, 14);
  Wire.begin();
  Serial.begin(115200);
  pinMode(IRQ, INPUT);

    //  wait some time
  delay(100);

  PRINTLND(" ");
  PRINTLND("Serilal begin");

  //  send msg that ESP8266 is present
  Serial.println("AT+ESP8266_MSG=PR");

  //  connect to WiFi network
  connectToWiFi();

  // start server
  startTCPServer();

  // send msg that ESP8266 is ready
  Serial.println("AT+ESP8266_MSG=RD");
}

void loop(){
  //  find out if client is still connected
  connectionCloseHandler();

  //  chceck for incomming connections
  //  and connect if there are
  connectionClientHandler(); 

  //  check client for data
  getDataFromClient();

  // check UART for data
  getDataFromUART();
}

void getDataFromClient() {
  if (serverClient && serverClient.connected()) {
    uint8_t current_char = 0;
    uint8_t len = 0;
    uint8_t sbuf[buff_size];

    do {
      if (serverClient.available()) {
        current_char = serverClient.read();
        sbuf[len] = current_char;
        len++;
      }
    } while ((current_char > 10) && (len < 255));

   if (len > 0) {
      Serial.write(sbuf, len);

      uint8_t params[3][50];
      uint8_t iter[3] = {0};
      uint8_t itime, gain;

      parseCommand(sbuf, 3, params, iter);
      params[1][iter[1]] = '\0';
      itime = atoi((const char*)params[1]);

      params[2][iter[2]] = '\0';
      gain = atoi((const char*)params[2]);

      PRINTLND(itime);
      PRINTLND(gain);

      SunS.triggerMeasurement(itime, gain);
      delay(10);
      PRINTLND("Measured 1");
      while(true == digitalRead(IRQ)) {
        PRINTD("+");
      };
      PRINTLND(" ");
      PRINTLND("Measured 2");
      SunS.printRegistersLineTCP();
      PRINTLND("Measured 3");
    }
  }
}

void getDataFromUART() {
  
  uint8_t sbuf[buff_size];
  uint8_t len = 0;

  while (Serial.available()) {
    delay(10);

    if(Serial.available() > 0) {
      //  read data from Serial
      sbuf[len] = Serial.read();
      len++;
    }
  }

  if (len > 0) {
    uint8_t params[3][50];
    uint8_t iter[3] = {0};
    uint8_t itime, gain;
    parseCommand(sbuf, 3, params, iter);

    //  push UART data to TCP/IP client
    if (serverClient && serverClient.connected()) {
      serverClient.write(sbuf, len);
    }
  }
}

void parseCommand(uint8_t sbuf[], uint8_t params_cnt, uint8_t params[][50], uint8_t params_len[]) {
  uint8_t offset = 0;
    for (int i = 0; i < params_cnt; i++) {
      params_len[i] = 0;
      while (sbuf[params_len[i]+offset] != ' ' && isalnum(sbuf[params_len[i]+offset])) {
          params[i][params_len[i]] = sbuf[params_len[i]+offset];
          params_len[i]++;
      }
      offset += params_len[i] + 1;
    }
}

