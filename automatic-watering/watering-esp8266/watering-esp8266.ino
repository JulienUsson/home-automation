#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

WiFiManager wifiManager;
StaticJsonDocument<64> input;
StaticJsonDocument<64> output;
ESP8266WebServer server(80);

void handleGet()
{
  String jsonStr;
  serializeJson(input, jsonStr);
  server.send(200, "text/json", jsonStr);
}

void handlePost()
{
  String body = server.arg("plain");
  DeserializationError error = deserializeJson(output, body);
  if (error)
  {
    server.send(400, "text/plain", "Can't deserialize body");
    return;
  }
  if (!output["duration"]) {
    server.send(400, "text/plain", "Missing duration");
    return;
  }
  Serial.println(body);
  server.send(200, "text/plain", body);
}

void setup()
{
  Serial.begin(115200);
  wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
  wifiManager.autoConnect("Garden", "WATER");

  server.on(F("/"), HTTP_GET, handleGet);
  server.on(F("/water"), HTTP_POST, handlePost);
  server.begin();
}

void loop()
{
  if (Serial.available() > 0)
  {
    String json = Serial.readString();
    deserializeJson(input, json);
  }
  server.handleClient();
}
