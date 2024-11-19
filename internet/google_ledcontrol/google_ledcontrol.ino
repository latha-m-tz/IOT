#include <DHT.h>
#include <DHT_U.h>
#include "thingProperties.h"

#define LED_PIN D4        // Connection for status LED
#define DHTPIN D5         // Connection for DHT sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // DHT sensor initialization
  dht.begin();

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sendDHT11Data();
  }
}

void onLightChange() {
  if (light) {
    digitalWrite(LED_PIN, HIGH); 
    Serial.println("LED ON");
  } else {
    digitalWrite(LED_PIN, LOW); 
    Serial.println("LED OFF");
  }
}

void sendDHT11Data() {
  temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read data from temperature sensor");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}
