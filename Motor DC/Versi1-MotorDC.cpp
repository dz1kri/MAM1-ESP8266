#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Nama dan kata sandi hotspot yang ingin Anda buat
const char* ssid = "NamaHotspot";
const char* password = "KataSandiHotspot";

// Pin yang terhubung ke driver motor DC (L298N)
const int motorPin1 = D1; // IN1 pada L298N
const int motorPin2 = D2; // IN2 pada L298N
const int enablePin = D3; // ENABLE pada L298N (modul PWM)

ESP8266WebServer server(80);

int motorSpeed = 0; // Variabel untuk menyimpan kecepatan motor (0 - 255)

void setup() {
  // Inisialisasi motor pins sebagai output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Inisialisasi pin ENABLE sebagai output
  pinMode(enablePin, OUTPUT);
  
  // Mulai serial communication
  Serial.begin(115200);

  // Menghubungkan ke hotspot yang dibuat
  WiFi.softAP(ssid, password);

  // Menampilkan IP address hotspot pada Serial Monitor
  Serial.print("Hotspot IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Mengatur rute untuk antarmuka web
  server.on("/", HTTP_GET, handleRoot);
  server.on("/control", HTTP_POST, handleControl);
  server.begin();
}

void loop() {
  server.handleClient();
  // Tambahkan logika kendali motor sesuai kebutuhan Anda
}

void handleRoot() {
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<title>Kendalikan Motor DC</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; }";
  html += ".button { display: inline-block; padding: 10px 20px; font-size: 18px; background-color: #3498db; color: #fff; border: none; cursor: pointer; margin: 10px; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Kendalikan Motor DC</h1>";
  html += "<label for='speedSlider'>Kecepatan:</label>";
  html += "<input type='range' min='0' max='255' value='0' class='slider' id='speedSlider'>";
  html += "<br>";
  html += "<button class='button' onclick='forward()'>Maju</button>";
  html += "<button class='button' onclick='reverse()'>Mundur</button>";
  html += "<button class='button' onclick='stopMotor()'>Berhenti</button>";
  html += "<script>";
  html += "function sendCommand(command, speed) {";
  html += "var xhr = new XMLHttpRequest();";
  html += "xhr.open('POST', '/control', true);";
  html += "xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');";
  html += "xhr.send('command=' + command + '&speed=' + speed);";
  html += "}";
  html += "function forward() {";
  html += "var speed = document.getElementById('speedSlider').value;";
  html += "sendCommand('forward', speed);";
  html += "}";
  html += "function reverse() {";
  html += "var speed = document.getElementById('speedSlider').value;";
  html += "sendCommand('reverse', speed);";
  html += "}";
  html += "function stopMotor() {";
  html += "sendCommand('stop', 0);";
  html += "}";
  html += "</script>";
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

void handleControl() {
  String command = server.arg("command");
  int speed = server.arg("speed").toInt();

  // Mengatur kecepatan motor berdasarkan nilai speed
  analogWrite(enablePin, speed);

  // Tambahkan logika untuk mengontrol motor DC berdasarkan perintah yang diterima
  if (command == "forward") {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } else if (command == "reverse") {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  } else if (command == "stop") {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  } else {
    // Tangani perintah yang tidak dikenali
  }

  server.send(200, "text/plain", "OK");
}
