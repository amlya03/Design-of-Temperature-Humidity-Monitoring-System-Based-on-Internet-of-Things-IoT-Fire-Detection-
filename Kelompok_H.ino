#include <WiFiClient.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <MQ2.h>
#define DHTTYPE DHT11
#define buzerPin D2
#define pumpPin D3
#define fanPin D4
#define dht_pin D5
#define pinFlame D6
DHT dht(dht_pin,DHTTYPE);

int pinmq2 = A0;
int lpg;

char auth[] = "uCIesRcB-2t5Qip4FLW4CrYCwyhVNY0Y";
char ssid[] = "Rohmi";
char pass[] = "wifinelemotmas";
//char ssid[] = "koscantik";
//char pass[] = "terserahkamu";

WidgetLED led1(V4); 
WidgetLED led2(V5);
WidgetLED led3(V6); 

MQ2 mq2(pinmq2);

void SensorFunction(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  lpg = mq2.readLPG();
  int api = digitalRead(pinFlame);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, lpg);
  Blynk.virtualWrite(V3, api);

  if( api == HIGH ){
    digitalWrite(buzerPin, LOW);
    digitalWrite(pumpPin, LOW);
    led1.on(); 
    }
  if(lpg > 500000){
    digitalWrite(buzerPin, HIGH);
    delay(1000);
    digitalWrite(buzerPin, LOW);
    delay(500);
    led2.on(); 
    }
  if(api==LOW){
    digitalWrite(buzerPin, HIGH);
    digitalWrite(pumpPin, HIGH); 
    led2.off();
    led1.off();
    }
    
  if( h > 50 ){
    digitalWrite(fanPin, LOW);
    led3.on(); 
    }
  else{
    digitalWrite(fanPin, HIGH); 
    led3.off(); 
    }     
}
void setup() {
  Serial.begin(9600);
  dht.begin();
  mq2.begin();
  Blynk.begin(auth,ssid,pass,"blynk-cloud.com", 8080);
  pinMode(buzerPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
}

void loop() {
 Blynk.run(); 
 SensorFunction();
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float* values= mq2.read(true);
 lpg = mq2.readLPG();
 int api = digitalRead(pinFlame);
  
 Serial.print("Suhu =");
 Serial.print(t);
 Serial.print("\n");
 Serial.print("Kelembaban =");
 Serial.print(h);
 Serial.print("\n");
 Serial.print ("Lpg Gas: ");
 Serial.println(lpg);
 
 Blynk.virtualWrite(V0, t);
 Blynk.virtualWrite(V1, h);
 Blynk.virtualWrite(V2, lpg);
 Blynk.virtualWrite(V3, api);
 delay(1000);
}
