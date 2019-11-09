#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <FirebaseArduino.h>


#define DHTPIN D2
#define DHTTYPE DHT11
#define FIREBASE_HOST "your firebase project address"                         // the project name address from firebase id
#define FIREBASE_AUTH "your firebase secret key"                    // the secret key generated from firebase

DHT dht(DHTPIN,DHTTYPE);


const char* ssid = "Lemongrasstech";// 
const char* password = "lGt12345";

WiFiClient client;    

float h;
float t;

void setup()
{
 Serial.begin(115200);
  delay(10);
  dht.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  Serial.print(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
 }
void loop()
{ 
  h = dht.readHumidity();
  t = dht.readTemperature(); 
  Firebase.setString("Temperature", String(t));
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
  Firebase.setString("Humidity", String(h));
  Serial.print("Humidity : ");
  Serial.print(h);
  Serial.print(" %");
  if (Firebase.failed()) { 
      Serial.print("setting /message failed:"); 
      Serial.println(Firebase.error());   
      return; 
   } 
  delay(30000); // interval
 }
