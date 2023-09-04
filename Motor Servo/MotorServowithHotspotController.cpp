#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "FJBKanayakanESP8266";     // Nama hotspot yang akan dibuat
const char* password = "...."; // Kata sandi hotspot

ESP8266WebServer server(80);
Servo myservo;
bool servoCommandSent = false;

void setup() {
  // Inisialisasi motor servo
  myservo.attach(D2); // Menggunakan pin D4 untuk servo
  myservo.write(90);  // Posisi awal servo

  // Inisialisasi koneksi WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  // Membuat halaman web untuk mengendalikan servo
  server.on("/", HTTP_GET, handleRoot);
  server.on("/servo", HTTP_GET, handleServo);
  server.on("/back", HTTP_GET, handleBack);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Control Servo via Hotspot</h1>";
  html += "<p><a href='/servo?angle=0'>Rotate Left</a></p>";
  html += "<p><a href='/servo?angle=90'>Center</a></p>";
  html += "<p><a href='/servo?angle=180'>Rotate Right</a></p>";

  // Tampilkan tombol "Kembali" jika perintah servo telah dikirim
  if (servoCommandSent) {
    html += "<p><a href='/back'>Kembali</a></p>";
    servoCommandSent = false; // Reset status perintah servo
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleServo() {
  String angleParam = server.arg("angle");
  int angle = angleParam.toInt();

  if (angle >= 0 && angle <= 180) {
    myservo.write(angle);
    servoCommandSent = true; // Set status perintah servo
    server.send(200, "text/plain", "Servo angle set to " + angleParam);
  } else {
    server.send(400, "text/plain", "Invalid angle");
  }
}

// Handler untuk tombol "Kembali"
void handleBack() {
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}
