/*
  UniboardArduinoEthernetMQTT.cpp - Uniboard MQTT client library for Arduino Ethernet.
  Created by Chuan Shao, 2018.
*/
#include "Arduino.h"
#include "UniboardArduinoEthernetMQTT.h"

class MQTTClientSystem: public MqttClient::System {
public:
    unsigned long millis() const {
        return ::millis();
    }
};

UniboardArduinoEthernetMQTT::UniboardArduinoEthernetMQTT()
{
    _token = "";
}

UniboardArduinoEthernetMQTT::UniboardArduinoEthernetMQTT(char* token)
{
    _token = token;
}

int UniboardArduinoEthernetMQTT::connectMQTT() {
    MqttClient::System *mqttSystem = new MQTTClientSystem;
    MqttClient::Logger *mqttLogger = new MqttClient::LoggerImpl<HardwareSerial>(Serial);
    MqttClient::Network *mqttNetwork = new MqttClient::NetworkClientImpl<Client>(_network, *mqttSystem);
    //// Make 128 bytes send buffer
    MqttClient::Buffer *mqttSendBuffer = new MqttClient::ArrayBuffer<128>();
    //// Make 128 bytes receive buffer
    MqttClient::Buffer *mqttRecvBuffer = new MqttClient::ArrayBuffer<128>();
    //// Allow up to 2 subscriptions simultaneously
    MqttClient::MessageHandlers *mqttMessageHandlers = new MqttClient::MessageHandlersImpl<2>();
    //// Configure client options
    MqttClient::Options mqttOptions;
    ////// Set command timeout to 10 seconds
    mqttOptions.commandTimeoutMs = 10000;
    //// Make client object
    _client = new MqttClient (
        mqttOptions, *mqttLogger, *mqttSystem, *mqttNetwork, *mqttSendBuffer,
        *mqttRecvBuffer, *mqttMessageHandlers
    );

    if (!_client->isConnected()) {
        _network.connect(_host, 1883);
        MqttClient::ConnectResult connectResult;
        {
            MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
            options.MQTTVersion = 4;
            if (_token[0] != '\0') {
                options.clientID.cstring = _token;
            } else {
                options.clientID.cstring = "DefaultClientID";
            }
            options.cleansession = true;
            options.keepAliveInterval = 15; // 15 seconds
            MqttClient::Error::type rc = _client->connect(options, connectResult);
            if (rc != MqttClient::Error::SUCCESS) {
                Serial.println("MQTT Connection error!");
            }
            return rc;
        }
    }
};

void UniboardArduinoEthernetMQTT::mqtt(char* topic, char* data)
{
    MqttClient::Message message;
    message.qos = MqttClient::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) data;
    message.payloadLen = strlen(data);
    _client->publish(topic, message);
}

void UniboardArduinoEthernetMQTT::disconnectMQTT() {
    _network.stop();
}