/* Created by Priyam Mehta */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "iot_projext";
const char* password = "1234567890";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)



IPAddress    apIP(10, 10, 10, 1);     

 
String page = "";
int LEDPin = 16;
int LEDPin2 = 5;

void setup(void){
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p><p><a href=\"LEDOn2\"><button>Turn LED2 ON</button></a>&nbsp;<a href=\"LEDOff2\"><button>Turn LED2 OFF</button></a></p>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  pinMode(LEDPin2, OUTPUT);
  digitalWrite(LEDPin, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00
  WiFi.softAP(ssid, password); //begin WiFi access point
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP()); 
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    Serial.println("command received");
    delay(1000);
  });
    server.on("/LEDOn2", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin2, HIGH);
    Serial.println("command received");
    delay(1000);
  });
    server.on("/LEDOff2", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin2, LOW);
    Serial.println("command received");
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    Serial.println("command received");
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
