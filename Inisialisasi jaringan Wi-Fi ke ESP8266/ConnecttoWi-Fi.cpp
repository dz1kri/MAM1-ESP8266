#include <ESP8266WiFi.h>

const char* ssid = "NamaSSID"; // Ganti dengan SSID jaringan Wi-Fi yang ingin Anda hubungkan atau nama hotspot yang ingin Anda buat
const char* password = "KataSandi"; // Ganti dengan kata sandi Wi-Fi jika diperlukan

void setup() {
  Serial.begin(115200);
  
  // Menghubungkan NodeMCU ke jaringan Wi-Fi
  Serial.println();
  Serial.print("Menghubungkan ke: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Terhubung ke Wi-Fi");
  Serial.println("Alamat IP: " + WiFi.localIP().toString());
}

void loop() {
  // Kode Anda dapat diletakkan di sini
  // NodeMCU akan menjalankan kode ini setelah berhasil terhubung ke Wi-Fi
}
