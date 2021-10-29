# online-led-control
first real project of IOT that alows you to control the brightness of the RGB Led using web server

-to run server first you need to install Node.js
link: https://nodejs.org/en/download/
second run "server check.bat" for first time(press ctrl+d to continue)
then you can run server by run "start.bat"
open web page and type your ip or "localhost"

-to edit server or webpage you you can use visual studio code
link: https://code.visualstudio.com/download

-for aduino you need these libraries

1. for esp8266 and nodeMCU use these libraries :
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
2. for esp32 use these libraries
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <analogWrite.h>

-change these vlaues in (aruino-code.ino) depend on your server's settings:

//Wi-Fi settings:
const char *ssid = "Wireless Name";
const char *pass = "Your Password";

//server ip , port number and page URL
#define SERVER "192.168.43.170"
#define PORT 80
#define URL "/"

//pins that RGB Led connected to:
#define redPin 32
#define greenPin 33
#define bluePin 25
