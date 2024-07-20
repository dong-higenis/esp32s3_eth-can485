 /*            
 *   UDP 사용시 아래의 링크를 참고해 ESP32 아두이노 라이브러리 코드 수정 필요
 *            https://github.com/Xinyuan-LilyGO/LilyGO-T-ETH-Series/issues/49
 */

#include "ethTest.h"

EthTest* EthTest::instance = nullptr;

void EthTest::setup()
{
  WiFi.onEvent(EthTest::onEthEvent);

  if (!ETH.beginSPI(ETH_MISO_PIN, ETH_MOSI_PIN, ETH_SCLK_PIN, ETH_CS_PIN, ETH_RST_PIN, ETH_INT_PIN)) {
      Serial.println("ETH start Failed!");
  } else {
    Serial.println("ETH OK");
  }
}


void EthTest::loop()
{
  if (eth_connected && !udp.connected()) {
    if (udp.listen(udpPort)) {
      Serial.print("UDP Listening on IP: ");
      Serial.println(ETH.localIP());
      udp.onPacket([](AsyncUDPPacket packet) {
        Serial.print("UDP Packet Type: ");
        Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
        Serial.print(", From: ");
        Serial.print(packet.remoteIP());
        Serial.print(":");
        Serial.print(packet.remotePort());
        Serial.print(", To: ");
        Serial.print(packet.localIP());
        Serial.print(":");
        Serial.print(packet.localPort());
        Serial.print(", Length: ");
        Serial.print(packet.length());
        Serial.print(", Data: ");
        Serial.write(packet.data(), packet.length());
        Serial.println();
        //reply to the client
        packet.printf("Got %u bytes of data", packet.length());
      });
    }
  }
}


void EthTest::onEthEvent(WiFiEvent_t event)
{
        Serial.print("onEthEvent");
        Serial.print(event);
        Serial.printf(" instance %p\n",instance);

  if(instance) {
    switch (event) {
    case ARDUINO_EVENT_ETH_START:
        Serial.println("ETH Started");
        //set eth hostname here
        ETH.setHostname("esp32-ethernet");
        break;
    case ARDUINO_EVENT_ETH_CONNECTED:
        Serial.println("ETH Connected");
        break;
    case ARDUINO_EVENT_ETH_GOT_IP:
        Serial.print("ETH MAC: ");
        Serial.print(ETH.macAddress());
        Serial.print(", IPv4: ");
        Serial.print(ETH.localIP());
        if (ETH.fullDuplex()) {
            Serial.print(", FULL_DUPLEX");
        }
        Serial.print(", ");
        Serial.print(ETH.linkSpeed());
        Serial.println("Mbps");
        instance->eth_connected = true;
        break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
        Serial.println("ETH Disconnected");
        instance->eth_connected = false;
        break;
    case ARDUINO_EVENT_ETH_STOP:
        Serial.println("ETH Stopped");
        instance->eth_connected = false;
        break;
    default:
        break;
    }
  }
}