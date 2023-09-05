#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Hotspot_LED_Control"; // Nama hotspot Wi-Fi yang akan Anda buat
const char* password = "Password_Hotspot"; // Password untuk hotspot Wi-Fi

ESP8266WebServer server(80);

const char* style = "<style>"
                    "body { font-family: Arial, sans-serif; text-align: center; }"
                    "h1 { color: #3333cc; }"
                    "a { display: block; margin: 20px; padding: 10px; background-color: #3333cc; color: #fff; text-decoration: none; border-radius: 5px; }"
                    "a:hover { background-color: #5555ff; }"
                    "</style>";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Matikan LED saat perangkat pertama kali dinyalakan
  Serial.begin(115200);
  delay(10);

  // Membuat hotspot Wi-Fi dengan SSID dan password yang telah ditentukan
  WiFi.softAP(ssid, password);

  // Menampilkan informasi SSID pada serial monitor
  Serial.print("Hotspot SSID: ");
  Serial.println(ssid);

  // Mulai server web untuk mengontrol LED
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleLEDOn);
  server.on("/off", HTTP_GET, handleLEDOff);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head>";
  html += "<title>Kendalikan LED</title>";
  html += style;
  html += "</head><body>";
  html += "<h1>Kendalikan LED</h1>";
  html += "<a href='/on'>Hidupkan LED</a>";
  html += "<a href='/off'>Matikan LED</a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(LED_BUILTIN, LOW); // Hidupkan LED
  server.send(200, "text/plain", "LED telah dihidupkan.");
}

void handleLEDOff() {
  digitalWrite(LED_BUILTIN, HIGH); // Matikan LED
  server.send(200, "text/plain", "LED telah dimatikan.");
}

