#include <AWSWebSocketClient.h>
#include <IPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>
#include <ArduinoJSON.h>

const int maxMQTTpackageSize = 512;
const int maxMQTTMessageHandlers = 1;
AWSWebSocketClient websocketCliet(1000);
ESP8266WiFiMulti WiFiMulti;

IPStack ipstack(websocketCliet);
MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers> *client = NULL;
long connection = 0;
void setup_awsiot()
{
  websocketCliet.setAWSRegion(AWS_REGION);
  websocketCliet.setAWSDomain(AWS_ENDPOINT);
  websocketCliet.setAWSKeyID(AWS_KEY_ID);
  websocketCliet.setAWSSecretKey(AWS_KEY_SECRET);
  websocketCliet.setUseSSL(true);
}
void setup_wifi()
{
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID,WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
char* generateClientID()
{
  char* cID = new char[23]();
  for (int i=0; i<22; i+=1) {
    cID[i]=(char)random(1, 256);
  }
  return cID;
}

bool connect()
{
  if (client == NULL)
  {
    client = new MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers>(ipstack);
  }
  else
  {
    if (client->isConnected())
    {
      client->disconnect();
    }
    delete client;
    client = new MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers>(ipstack);
    delay(1000);
    Serial.print(millis());
    Serial.print(" - conn: ");
    Serial.print(++connection);
    Serial.print(" - (");
    Serial.print(ESP.getFreeHeap());
    Serial.println(")");
    int rc = ipstack.connect(AWS_ENDPOINT,AWS_SERVERPORT);
    if (rc!=1)
    {
      Serial.println("error connection to the websocket server");
      return false;
    }
    else
    {
      Serial.println("websocket connected");
    }
    Serial.println("MQTT connecting");
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    char* clientID = generateClientID();
    data.clientID.cstring = clientID;
    rc = client->connect(data);
    delete[] clientID;

    if (rc!=0)
    {
      Serial.print("error connection to MQTT server");
      Serial.print(rc);
      return false;
    }
    Serial.print("MQTT connected");
    return true;
  }
}
