# uniboard-arduino-ethernet
[Uniboard](https://uniboard.io) client library for [Arduino](https://www.arduino.cc/) with [Ethernet shield](https://www.arduino.cc/en/Main/ArduinoEthernetShield), or for [Arduino Ethernet](https://store.arduino.cc/usa/arduino-ethernet-rev3-without-poe) chip.

`UniboardArduinoEthernetHTTP.h` is the Uniboard HTTP client library, while `UniboardArduinoEthernetMQTT.h` is the Uniboard MQTT client library. With UniboardArduinoEthernetHTTP or UniboardArduinoEthernetMQTT, sending data to Uniboard system through HTTP or MQTT protocol would be pretty easy and simple.

## Usage of UniboardArduinoEthernetHTTP
1. Install `UniboardArduinoEthernetHTTP.zip` in Arduino IDE, and install [Ethernet](http://www.arduino.cc/en/Reference/Ethernet) or [Ethernet2](https://github.com/adafruit/Ethernet2) library in Arduino IDE's Library Manager for corresponding chip requirement.

2. Include `UniboardArduinoEthernetHTTP.h` and send HTTP data:
```c
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet2.h>
#include <UniboardArduinoEthernetHTTP.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 29, 109);

UniboardArduinoEthernetHTTP httpClient("25f6db34-9ff1-47f4-b7bb-3721cafb2e23");

void setup()
{
  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip); // Failed to use DHCP, switch to static IP config.
  }
  delay(1000);
}

void loop()
{
  httpClient.http("59db5cd3d6021211cb346b0b", "{\"temp\":88.2, \"humidity\":29.8}");
  delay(5000);
}
```

## Usage of UniboardArduinoEthernetMQTT
1. Install `UniboardArduinoEthernetMQTT.zip` in Arduino IDE, and install [Ethernet](http://www.arduino.cc/en/Reference/Ethernet) or [Ethernet2](https://github.com/adafruit/Ethernet2) library in Arduino IDE's Library Manager for corresponding chip requirement. Also, install [ArduinoMqtt](https://github.com/monstrenyatko/ArduinoMqtt) by Oleg Kovalenko in Arduino IDE's Library Manager, UniboardArduinoEthernetMQTT is based on [ArduinoMqtt](https://github.com/monstrenyatko/ArduinoMqtt).

2. Include `UniboardArduinoEthernetMQTT.h` and send MQTT data:
```c
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet2.h>

#include <UniboardArduinoEthernetMQTT.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 29, 109);

UniboardArduinoEthernetMQTT mqttClient("25f6db34-9ff1-47f4-b7bb-3721cafb2e23");
bool mqttConnected = false;

void setup() {
	Serial.begin(9600);

  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip); // Failed to use DHCP, switch to static IP config.
  }
  delay(1000);

  mqttConnected = mqttClient.connectMQTT() == 0;
}

void loop() {
    if (mqttConnected) {
        mqttClient.mqtt("/data_api/device/59db5cd3d6021211cb346b0b", "{\"temp\":32.2, \"humidity\":49.8}");
    }
    delay(5000);
}
```