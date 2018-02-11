/*
  UniboardArduinoEthernetHTTP.h - Uniboard HTTP client library for Arduino Ethernet.
  Created by Chuan Shao, 2018.
*/
#ifndef UNIBOARD_ARDUINO_ETHERNET_HTTP
#define UNIBOARD_ARDUINO_ETHERNET_HTTP

#include "Arduino.h"
#include <EthernetClient.h>

class UniboardArduinoEthernetHTTP
{
  public:
    UniboardArduinoEthernetHTTP();
    UniboardArduinoEthernetHTTP(char* token);
    void http(char* deviceId, char* data);
    void disconnectHTTP();
  private:
    char* _token = "";
    const char* _host = "uniboard.io";
    EthernetClient _client;
};

#endif