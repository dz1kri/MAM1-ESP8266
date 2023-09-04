#include <ESP8266WiFi.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>

// Definisikan SSID dan Password untuk hotspot WiFi
const char *ssid = "NamaHotspot";
const char *password = "KataSandiHotspot";

// Inisialisasi objek WiFi
WiFiServer server(80);

// Inisialisasi objek MotorShield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Gunakan salah satu dari dua motor DC yang tersedia di MotorShield
Adafruit_DCMotor *motor = AFMS.getMotor(1);  // Gunakan motor 1

void setup() {
  // Mulai komunikasi serial
  Serial.begin(115200);

  // Koneksikan ke WiFi sebagai hotspot
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("IP Address Hotspot: ");
  Serial.println(myIP);

  // Inisialisasi MotorShield
  AFMS.begin();

  // Mulai server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client Terhubung");

    // Baca perintah dari klien
    String request = client.readStringUntil('\r');
    client.flush();

    // Kendalikan motor berdasarkan perintah dari klien
    if (request.indexOf("MUNDUR") != -1) {
      motor->setSpeed(255); // Atur kecepatan motor maksimum
      motor->run(BACKWARD);
    } else if (request.indexOf("MAJU") != -1) {
      motor->setSpeed(255); // Atur kecepatan motor maksimum
      motor->run(FORWARD);
    } else if (request.indexOf("STOP") != -1) {
      motor->setSpeed(0); // Motor berhenti
      motor->run(RELEASE);
    }

    // Balas kepada klien
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<body>");
    client.println("<h1>Motor DC Terkendali</h1>");
    client.println("</body>");
    client.println("</html>");

    // Tutup koneksi dengan klien
    client.stop();
    Serial.println("Client Terputus");
  }
}
