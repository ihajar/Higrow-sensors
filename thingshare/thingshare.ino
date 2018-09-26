//Netwrok credentials
const char* ssid = "************";  //your wifi network name
const char* password = "*************";  // password  



//Thingspeak
//status four write api keys and channels IDs 

const char * apiKey1 = "***********"; // Put your ApiKey1 here
const char * apiKey2 = "***************"; // Put your ApiKey2 here
const char * apiKey3 = "***************"; // Put your ApiKey3 here
const char * apiKey4 = "************"; // Put your ApiKey4 here

long channel1 = 476599; //channel1 ID
long channel2 = 494831; //channel2 ID
long channel3 = 494238; //channel3 ID
long channel4 = 494239; //channel4 ID

const char* server = "api.thingspeak.com";

#include "DHT.h"
#include <WiFi.h>
#include "ThingSpeak.h"

//DHT
//Air temperature and humidity
#define DHTTYPE DHT11
const int DHTPin = 22;
DHT dht(DHTPin, DHTTYPE);
int t = 0;
int h = 0;

//soil moisture and light
const int soilpin = 32;
const int LIGHT_PIN = 33;


//timer
long writeTimingSeconds = 17; // define sample time in seconds to send data
long startWriteTiming = 0;
long elapsedWriteTime = 0;

boolean error;

//Initialize the client library
WiFiClient client;

//setup 
void setup()
{
  Serial.begin(115200);
  Serial.println("Attempting to connect to WPA network ...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  dht.begin(); //set DHT
  startWriteTiming = millis();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);
}

void loop()
{
  start:
  error=0;

  elapsedWriteTime = millis()-startWriteTiming;

  if (elapsedWriteTime > (writeTimingSeconds*1000))
  {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int soilMos = analogRead(soilpin);
    int light = analogRead(LIGHT_PIN);
    soilMos = map(soilMos, 0, 4095, 0, 1023);
    light = map(light, 0, 4095, 0, 1023);
    
    if (isnan(h) || isnan(t))
    {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }
    
    if (client.connect(server,80))
    {
      float t = dht.readTemperature();
      ThingSpeak.setField(1,t);
      ThingSpeak.setField(2,t);
      ThingSpeak.writeFields(channel1, apiKey1);

      float h = dht.readHumidity();
      ThingSpeak.setField(1,h);
      ThingSpeak.setField(2,h);
      ThingSpeak.writeFields(channel2, apiKey2);

      int light = analogRead(LIGHT_PIN);
      ThingSpeak.setField(1,light);
      ThingSpeak.setField(2,light);
      ThingSpeak.writeFields(channel3, apiKey3);

      int soilMos = analogRead(soilpin);
      ThingSpeak.setField(1,soilMos);
      ThingSpeak.setField(2,soilMos);
      ThingSpeak.writeFields(channel4, apiKey4);

      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" *C\n Humidity: ");
      Serial.print(h);
      Serial.print(" %\n Soil Moisture : ");
      Serial.print(soilMos);
      Serial.print("m3\n light level: ");
      Serial.print(light);
      Serial.print("lx\n ");
      Serial.print("Sending data to Thingspeak: ");
   delay(900000); // delay(900000) each 15 minutes send data to Thingspeak
    }
   
  }
}


