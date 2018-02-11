/*
  UniboardArduinoEthernetHTTP.cpp - Uniboard HTTP client library for Arduino Ethernet.
  Created by Chuan Shao, 2018.
*/
#include "Arduino.h"
#include "UniboardArduinoEthernetHTTP.h"

UniboardArduinoEthernetHTTP::UniboardArduinoEthernetHTTP()
{
  _token = "";
}

UniboardArduinoEthernetHTTP::UniboardArduinoEthernetHTTP(char* token)
{
  _token = token;
}

void UniboardArduinoEthernetHTTP::http(char* deviceId, char* data)
{
  if (!_client.connected()) {
    _client.connect(_host, 80);
  }

  _client.print("POST /data_api/device/");
  _client.print(deviceId);
  _client.println(" HTTP/1.1");
  _client.println("Host: uniboard.io");
  if (_token[0] != '\0') {
    _client.print("X-Uniboard-Token: ");
    _client.println(_token);
  }
  _client.println("Content-Type: application/json");
  _client.print("Content-Length: ");
  _client.println(strlen(data));
  _client.println("Connection: keep-alive");
  _client.println();
  _client.println(data);
}

void UniboardArduinoEthernetHTTP::disconnectHTTP() {
  _client.stop();
}