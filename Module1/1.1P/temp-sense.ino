// Include the libraries:
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2

#define DHTTYPE DHT22 

DHT dht = DHT(DHTPIN, DHTTYPE);
float maxtemp = 0;

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);

  // Setup sensor:
  dht.begin();

  // Init the built in LED
  pinMode(LED_BUILTIN, OUTPUT);

}

bool maxtemp_check(float currenttemp){
  
  if(currenttemp > maxtemp){
    maxtemp = currenttemp;
    digitalWrite(LED_BUILTIN, HIGH);
    return true;
  }
  digitalWrite(LED_BUILTIN, LOW);
  return false;
  
}

void loop() {
  
  // Wait a few seconds between measurements:
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  // Read the humidity in %:
  float h = dht.readHumidity();
  
  // Read the temperature as Celsius:
  float t = dht.readTemperature();
  
  // Is max temp?
   String maxtemp_string = maxtemp_check(t) ? "New max temp!" : "";

  // Check if any reads failed and exit early (to try again):
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Compute heat index in Celsius:
  float hic = dht.computeHeatIndex(t, h, false);


  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" \xC2\xB0");
  Serial.print("C | ");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" \xC2\xB0");
  Serial.print("C");
  Serial.println(" " + maxtemp_string);
  




}
