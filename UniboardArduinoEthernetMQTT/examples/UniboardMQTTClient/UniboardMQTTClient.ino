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
