#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> // Tambahkan library ESP8266WebServer

const char* ssid = "Praktikum1-PoinB";   // Nama hotspot Wi-Fi yang akan Anda buat
const char* password = "10987654321";   // Password untuk hotspot Wi-Fi

ESP8266WebServer server(80); // Inisialisasi objek server dengan port 80

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Inisialisasi pin LED_BUILTIN sebagai output
  digitalWrite(LED_BUILTIN, LOW); // Pastikan LED dimatikan saat perangkat pertama kali dinyalakan

  // Mulai membuat hotspot Wi-Fi
  Serial.begin(115200);
  delay(10);

  // Membuat hotspot Wi-Fi dengan SSID dan password yang telah ditentukan
  WiFi.softAP(ssid, password);

  // Menampilkan informasi SSID pada serial monitor
  Serial.print("Hotspot SSID: ");
  Serial.println(ssid);

  // Mulai server web untuk menampilkan status LED
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

void loop() {
  // Kode yang mengatur LED seperti sebelumnya
  digitalWrite(LED_BUILTIN, HIGH);  // Mematikan LED

  // Layani permintaan HTTP
  server.handleClient();
}

void handleRoot() {
  // Membaca status LED dan mengirimkannya sebagai respons HTTP
  String statusLED = (digitalRead(LED_BUILTIN) == LOW) ? "ON" : "OFF";
  String html = "<html><body>";
  html += "<h1>Status LED: " + statusLED + "</h1>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
