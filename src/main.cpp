#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "config.h"
#include "awsiot.h"

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  setup_awsiot();
  connect();
  if (connect())
  {
    Serial.print("OK");
  }
}

void loop()
{

}
