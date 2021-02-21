#include <ArduinoJson.h>

int WATER_LEVEL_PIN = 0;
int WATER_PUMP_PIN = 2;
int WATER_VALVE_PIN = 3;

StaticJsonDocument<64> output;
StaticJsonDocument<64> input;

bool isWatering = false;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(WATER_LEVEL_PIN, INPUT_PULLUP);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(WATER_VALVE_PIN, OUTPUT);

  // INIT relay
  digitalWrite(WATER_PUMP_PIN, HIGH);
  digitalWrite(WATER_VALVE_PIN, HIGH);

  output["isAlive"] = true;
}

void loop()
{
  int hasWater = digitalRead(WATER_LEVEL_PIN);
  if (hasWater == LOW)
  {
    output["hasWater"] = true;
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(WATER_PUMP_PIN, LOW);
  }
  else
  {
    output["hasWater"] = false;
    digitalWrite(WATER_PUMP_PIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
  }
  output["isWatering"] = isWatering;
  serializeJson(output, Serial);

  if (Serial.available() > 0)
  {
    String json = Serial.readString();
    DeserializationError error = deserializeJson(input, json);
    if (!error)
    {
      digitalWrite(WATER_VALVE_PIN, HIGH);
      delay(input["duration"]);
      digitalWrite(WATER_VALVE_PIN, LOW);
    }
  }

  delay(333);
}
