#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "FJBKanayakanESP8266";     // Nama hotspot yang akan dibuat
const char* password = ""; // Kata sandi hotspot

ESP8266WebServer server(80);
Servo myservo;
bool servoCommandSent = false;

void setup() {
  // Inisialisasi motor servo
  myservo.attach(D2); // Menggunakan pin D2 untuk servo
  myservo.write(0);  // Posisi awal servo

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
  String html = "<html><head>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; }";
  html += ".container { text-align: center; margin-top: 20px; }";
  html += ".button { display: inline-block; padding: 10px 20px; font-size: 18px; text-decoration: none; margin: 10px; background-color: #3498db; color: #ffffff; border-radius: 5px; }";
  html += "</style>";
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>Control Servo via Hotspot</h1>";
  html += "<a class='button' href='/servo?angle=0'>Rotate Left</a>";
  html += "<a class='button' href='/servo?angle=90'>Center</a>";
  html += "<a class='button' href='/servo?angle=180'>Rotate Right</a>";

  html += "</div></body></html>";
  server.send(200, "text/html", html);
}

void handleServo() {
  String angleParam = server.arg("angle");
  int angle = angleParam.toInt();

  if (angle >= 0 && angle <= 180) {
    myservo.write(angle);
    servoCommandSent = true; // Set status perintah servo
    String response = "Servo angle set to " + angleParam;

    // Tambahkan tombol "Kembali" ke halaman pernyataan
    response += "<br><a href='/'>Kembali</a>";
    
    server.send(200, "text/html", response);
  } else {
    server.send(400, "text/plain", "Invalid angle");
  }
}
// Handler untuk tombol "Kembali"
void handleBack() {
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}
