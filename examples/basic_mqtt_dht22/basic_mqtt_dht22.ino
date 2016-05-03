#include <Arduino.h>
#include <MqttConnector.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

MqttConnector *mqtt;

#define MQTT_HOST     "mqtt.espert.io"
#define MQTT_PORT     1883
/**************************************************
/* AUTH
/**************************************************/
// #define MQTT_USERNAME "z7KXagr95sny6Zx"
// #define MQTT_PASSWORD "jPxRZFXfoshDxLHk79ChVFLu5/8="
/***************************************************/

/**************************************************
/* CLIENT_ID & PREFIX */
/*************************************************/
#define MQTT_CLIENT_ID    ""
#define MQTT_PREFIX       ""

/* DEVICE DATA & FREQUENCY */
#define DEVICE_NAME       "CMMC-001"
#define PUBLISH_EVERY     (10*1000)// every 10 seconds

/* WIFI INFO */
#ifndef WIFI_SSID
  #define WIFI_SSID        ""
  #define WIFI_PASSPHARSE  ""
#endif

#include "_publish.h"
#include "_receive.h"
#include "init_mqtt.h"

void init_hardware()
{
  Serial.begin(115200);
  delay(10);
  dht.begin();
  Serial.println();
  Serial.println("BEGIN");
}

void setup()
{
  WiFi.begin("Nat", "123456789");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("CONNECTING...");
    delay(300);
  }
  init_hardware();
  init_mqtt();
}

void loop()
{
  mqtt->loop();
}