#include <AWSWebSocketClient.h>
#include <IPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>
#include <ArduinoJSON.h>

ESP8266WiFiMulti WiFiMulti;
void setup_wifi()
{

  WiFiMulti.addAP(WLAN_SSID,WLAN_PASS);
  Serial.println("connecting to WiFi...");
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Successfully connected to ");
  Serial.print(WLAN_SSID);
  Serial.print(" IP address is ");
  Serial.print(WiFi.localIP());
}
