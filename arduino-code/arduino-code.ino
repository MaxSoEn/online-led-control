//#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <analogWrite.h>

WebSocketsClient wsc;

const char *ssid = "max";
const char *pass = "123456789";

#define SERVER  "192.168.43.170"
#define PORT    80
#define URL     "/"
#define redPin 32
#define greenPin 33
#define bluePin 25


void websocketEvent(WStype_t type, uint8_t *data, size_t length){
  switch(type){
    case(WStype_CONNECTED):
      Serial.printf("connected to server\n");
      break;
    case WStype_DISCONNECTED:
      Serial.printf("Disconnected!\n");
      break;
    case(WStype_TEXT):
      int fr = 0, fg = 0, fb = 0;
      //Serial.printf("data: %s\n",data);
      if(data[0] == 'r'){
        for(byte i = 1; i < length; i++){
            fr += (data[i] - '0') * pow(10, (length - 1) - (i));
        }
        int v = map(fr, 0, 255, 0, 1024);
        analogWrite(redPin,v);
        Serial.printf("Red fade: %d\n", fr);
      }else if(data[0] == 'g'){
        for(byte i = 1; i < length; i++){
            fg += (data[i] - '0') * pow(10, (length - 1) - (i));
        }
        int v = map(fg, 0, 255, 0, 1024);
        analogWrite(greenPin, v);
        Serial.printf("green fade: %d\n", fg);
      }else if(data[0] == 'b'){
        for(byte i = 1; i < length; i++){
            fb += (data[i] - '0') * pow(10, (length - 1) - (i));
        }
        int v = map(fb,0,255,0,1024);
        analogWrite(bluePin,v);
        Serial.printf("blue fade: %d\n", fb);
      }
      
      break;
  }
}

void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  Serial.print("conecting");
  while(WiFi.status() != WL_CONNECTED){
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

void loop(){
  wsc.loop();
}
