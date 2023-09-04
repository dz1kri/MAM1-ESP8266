#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "NamaHotspot"; // Nama Hotspot Anda
const char* password = "PasswordHotspot"; // Password Hotspot Anda

ESP8266WebServer server(80);

int led1Pin = D1; // Pin untuk LED 1
int led2Pin = D2; // Pin untuk LED 2

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  // Menghubungkan ESP8266 ke WiFi sebagai hotspot
  WiFi.softAP(ssid, password);
  
  // Mengatur rute pada server web
  server.on("/", HTTP_GET, handleRoot);
  server.on("/led1/on", HTTP_GET, handleLED1On);
  server.on("/led1/off", HTTP_GET, handleLED1Off);
  server.on("/led2/on", HTTP_GET, handleLED2On);
  server.on("/led2/off", HTTP_GET, handleLED2Off);

  // Memulai server
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Control LEDs</h1>";
  html += "<p><a href='/led1/on'>Turn LED 1 On</a></p>";
  html += "<p><a href='/led1/off'>Turn LED 1 Off</a></p>";
  html += "<p><a href='/led2/on'>Turn LED 2 On</a></p>";
  html += "<p><a href='/led2/off'>Turn LED 2 Off</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLED1On() {
  digitalWrite(led1Pin, HIGH);
  server.send(200, "text/plain", "LED 1 On");
}

void handleLED1Off() {
  digitalWrite(led1Pin, LOW);
  server.send(200, "text/plain", "LED 1 Off");
}

void handleLED2On() {
  digitalWrite(led2Pin, HIGH);
  server.send(200, "text/plain", "LED 2 On");
}

void handleLED2Off() {
  digitalWrite(led2Pin, LOW);
  server.send(200, "text/plain", "LED 2 Off");
}
