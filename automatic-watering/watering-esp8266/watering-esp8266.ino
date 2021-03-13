#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

WiFiManager wifiManager;
StaticJsonDocument<64> input;
StaticJsonDocument<64> output;
ESP8266WebServer server(80);

bool isWatering = false;
bool hasWater = false;

void handleGet()
{
  output["hasWater"] = hasWater;
  output["isWatering"] = isWatering;
  String httpResponse;
  serializeJson(output, httpResponse);
  server.send(200, "text/json", httpResponse);
}

void handleNotFound()
{
  server.send(404, "text/plain", "Not found");
}

void handlePost()
{
  String body = server.arg("plain");
  DeserializationError error = deserializeJson(input, body);
  if (error)
  {
    server.send(400, "text/plain", "Can't deserialize body");
    return;
  }
  if (!input["duration"]) {
    server.send(400, "text/plain", "Missing duration");
    return;
  }
  if (!input["duration"].is<int>()) {
    server.send(400, "text/plain", "Duration must be a integer in second");
    return;
  }
  String message = "";
  message = message + "D" + input["duration"].as<int>();
  Serial.println(message);
  server.send(200, "text/json", body);
}

void setup()
{
  Serial.begin(57600);
  wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
  wifiManager.setDebugOutput(false);
  wifiManager.autoConnect("Garden", "WATER");

  server.on(F("/"), HTTP_GET, handleGet);
  server.on(F("/water"), HTTP_POST, handlePost);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop()
{
  if (Serial.available() > 0)
  {
    String message = Serial.readString();
    if (message.startsWith("HW")) {
      hasWater = message.substring(2, 3).toInt() == 1;
      isWatering = message.substring(5, 6).toInt() == 1;
    }
  }
  server.handleClient();
}
