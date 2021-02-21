#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

WiFiManager wifiManager;
StaticJsonDocument<64> doc;
ESP8266WebServer server(80);

void handleGet()
{
  String jsonStr;
  serializeJson(doc, jsonStr);
  server.send(200, "text/json", jsonStr);
}

void handlePost()
{
  String body = server.arg("plain");
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
    deserializeJson(doc, json);
  }
  server.handleClient();
}
