#ifndef WIFI_CONNECTION_H_
#define WIFI_CONNECTION_H_

//  include info about SSID and PASS
#include "credentials.h"
#include "helpers.h"

extern WiFiServer server;
extern WiFiClient serverClient;
extern bool should_be_connected;

void connectToWiFi(void) {
  WiFi.begin(ssid, password);
  PRINTLND("WiFi begin");

  uint8_t conn_count = 0;
  //  wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    conn_count++;
    PRINTD(".");

    // restart the CPU if cannot connect to the WiFi
    if (conn_count > 40) {
      PRINTLND("\r\nESP8266 can not connect to the WiFi and is about restarting.");
      ESP.restart();
    }
  }
  
  PRINTLND(".");

  PRINTD("Connected to: ");
  PRINTLND(ssid);
  
  PRINTD("IP address: ");
  PRINTLND(WiFi.localIP());

  PRINTD("Port: ");
  PRINTLND(port);

  //  print end of configuration characters
  PRINTLND("Connection estabilished");  
}

void startTCPServer(void) {
  server.setNoDelay(true);
  server.begin();
  PRINTLND("Serever started");
}

void connectionCloseHandler(void) {
  if(!serverClient.connected() && should_be_connected) {
    serverClient.stop();
    should_be_connected = false;

    // send msg that client has disconnected
    Serial.println("AT+ESP8266_MSG=CD");
    PRINTLND("Client disconnected");
  }
}

void connectionClientHandler(void) {
  if (server.hasClient()) {
      //  check if there are any new clients
      serverClient = server.available();
      should_be_connected = true;
      PRINTLND("Client connected");

      // send msg that client has connected
      Serial.println("AT+ESP8266_MSG=CC");

      //  send hello message via TCP connection 
      //  (just after estabilishing with a client)
      const char tcp_msg[] = "AT+ESP8266_MSG=HI\r\n";
      serverClient.write(tcp_msg, strlen(tcp_msg));
  }
}

#endif // WIFI_CONNECTION_H_