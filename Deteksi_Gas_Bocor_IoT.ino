#define BLYNK_PRINT Serial //mendefinisikan penggunaan Blynk
#include <ESP8266WiFi.h> // library untuk menghubungkan dengan modul Wifi ESP8266
#include <BlynkSimpleEsp8266.h> // library untuk menghubungkan perangkat dengan Blynk

char auth[] = "0gnn1Ik8n00pc-7r1J9eL6Ruu2dxy3PC"; // kode token proyek pada Blynk

#include <LiquidCrystal_I2C.h> // library untuk LCD dan modul I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // set address I2C dan besar karakter untuk lcd 16×2
char ssid[] = "TP-Link_1A62"; // SSID Wifi
char pass[] = "66092834"; // Password Wifi
 
int buzzer = D2; //buzzer
int sensor = A0; //sensor

int sensor_limit = 880; // nilai batas sensor
 
void setup() //mengeksekusi bagian program yang hanya dijalankan sekali di awal program
{
lcd.begin(); // memulai penggunaan LCD 
lcd.backlight(); //menyalakan backlight LCD
lcd.setCursor(0, 0); // mengatur posisi kursor LCD pada baris 1 posisi 0
lcd.print("    DETEKSI "); // menampilkan karakter berupa huruf pada LCD
lcd.setCursor(0, 1); // mengatur posisi kursor LCD pada baris 2 posisi 0
 lcd.print("GAS BOCOR BLYNK"); // menampilkan karakter berupa huruf pada LCD
delay(2000); // menunda selama 2000 milidetik
pinMode(buzzer, OUTPUT); // menetapkan buzzer sebagai output
pinMode(sensor, INPUT); // menetapkan sensor sebagai input
Serial.begin(9600); // kecepatan pengiriman dan penerimaan data
Blynk.begin(auth, ssid, pass); // konfigurasi Blynk
}
 
void loop() // mengeksekusi bagian program yang akan dijalankan berulang-ulang
{
int sensor_value = analogRead(sensor); // membaca nilai sensor
Serial.print("Gas Level: "); // menampilkan  karakter berupa huruf di serial monitor
Serial.println(sensor_value); //  menampilkan karakter berupa huruf pada baris baru di serial monitor
Blynk.virtualWrite(V1, sensor_value); // menampilkan nilai sensor pada input V1 Aplikasi Blynk

if (sensor_value > sensor_limit) // kondisi nilai sensor lebih besar dari nilai batas sensor
{
digitalWrite(buzzer, HIGH); // memberikan nilai high pada buzzer
delay(500); // menunda selama 500 milidetik
digitalWrite(buzzer, LOW); // memberikan nilai low pada buzzer
lcd.clear(); // menghapus tampilan LCD
lcd.setCursor(0, 0); // mengatur posisi kursor LCD pada baris 1 posisi 0
lcd.print("ADA GAS BOCOR!!!"); // menampilkan karakter berupa huruf pada LCD
Blynk.notify("PERINGATAN: ADA GAS BOCOR!!!"); // mengirim notifikasi berupa tulisan pada Aplikasi Blynk
}
else // kondisi lainnya
{
 lcd.clear(); // menghapus tampilan LCD
 lcd.setCursor(0, 0); // mengatur posisi kursor LCD pada baris 1 posisi 0
 lcd.print("     TIDAK   "); // menampilkan karakter berupa huruf pada LCD
 lcd.setCursor(0, 1); // mengatur posisi kursor LCD pada baris 2 posisi 0
 lcd.print("  ADA GAS BOCOR "); // menampilkan karakter berupa huruf pada LCD
 delay(300); // menunda selama 300 milidetik
digitalWrite(buzzer, LOW); // memberikan nilai low pada buzzer
}
delay(100); // menunda selama 100 milidetik
Blynk.run(); // memproses perintah masukan dan melakukan pemeliharaan koneksi blynk
}
