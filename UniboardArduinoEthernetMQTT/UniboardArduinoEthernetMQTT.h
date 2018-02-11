/*
  UniboardArduinoEthernetMQTT.h - Uniboard MQTT client library for Arduino Ethernet.
  Created by Chuan Shao, 2018.
*/
#ifndef UNIBOARD_ARDUINO_ETHERNET_MQTT
#define UNIBOARD_ARDUINO_ETHERNET_MQTT

#include "Arduino.h"
#include <EthernetClient.h>
#include <MqttClient.h>

class UniboardArduinoEthernetMQTT
{
  public:
    UniboardArduinoEthernetMQTT();
    UniboardArduinoEthernetMQTT(char* token);
    int connectMQTT();
    void mqtt(char* topic, char* data);
    void disconnectMQTT();
    ~UniboardArduinoEthernetMQTT() {
        delete _client;
    }
  private:
    char* _token = "";
    const char* _host = "uniboard.io";
    EthernetClient _network;
    MqttClient *_client;
};

#endif