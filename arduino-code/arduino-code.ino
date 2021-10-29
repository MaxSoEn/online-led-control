//#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <analogWrite.h>

WebSocketsClient wsc;

const char *ssid = "max";
const char *pass = "123456789";

#define SERVER "192.168.43.170"
#define PORT 80
#define URL "/"
#define redPin 32
#define greenPin 33
#define bluePin 25

void websocketEvent(WStype_t type, uint8_t *data, size_t length) {
  switch (type) {
  case (WStype_CONNECTED):
    Serial.printf("connected to server\n");
    break;
  case WStype_DISCONNECTED:
    Serial.printf("Disconnected!\n");
    break;
  case (WStype_TEXT):
    int value = 0;
    for (byte i = 1; i < length; i++) {
        value += (data[i] - '0') * pow(10, (length - 1) - (i));
    }
    value = map(value, 0, 255, 0, 1023);
    Serial.printf("%c fade: %d\n", data[0], value);
    if (data[0] == 'r') {
      analogWrite(redPin, value);
    } else if (data[0] == 'g') {
      analogWrite(greenPin, value);
    } else {
      analogWrite(bluePin, value);
    }
    break;
  }
}

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  Serial.print("conecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println(WiFi.SSID());
  Serial.println(WiFi.localIP());

  wsc.begin(SERVER, PORT, URL);
  wsc.onEvent(websocketEvent);
  // try ever 1000 again if connection has failed
  wsc.setReconnectInterval(1000);
}

void loop()
{
  wsc.loop();
}
