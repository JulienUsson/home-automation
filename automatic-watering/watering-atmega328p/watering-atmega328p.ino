int WATER_LEVEL_PIN = 7;
int WATER_PUMP_PIN = 8;
int WATER_VALVE_PIN = 9;

int wateringTimeRemaining = 0;
bool isWatering = false;
bool hasWater = false;

void setup()
{
  Serial.begin(57600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(WATER_LEVEL_PIN, INPUT_PULLUP);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(WATER_VALVE_PIN, OUTPUT);

  // Init state
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(WATER_PUMP_PIN, HIGH);
  digitalWrite(WATER_VALVE_PIN, HIGH);

  // clear serial after 2s to let the ESP8266 start
  delay(2000);
  while (Serial.available() > 0)
  {
    Serial.read();
  }
}

void loop()
{
  bool hasWaterNow = digitalRead(WATER_LEVEL_PIN) == LOW;
  bool isWateringNow = wateringTimeRemaining > 0;

  if (hasWaterNow != hasWater || isWateringNow != isWatering) {
    hasWater = hasWaterNow;
    isWatering = isWateringNow;

    if (hasWater)
    {
      // Turn on led and water pump
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(WATER_PUMP_PIN, LOW);
    }
    else
    {
      // Turn off led and water pump
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(WATER_PUMP_PIN, HIGH);
    }

    if (!isWatering) {
      // Stop watering
      digitalWrite(WATER_VALVE_PIN, HIGH);
    }

    // Message to send to the ESP8266
    String message = "";
    message = message + "HW" + (hasWater ? "1" : "0");
    message = message + "IW" + (isWatering ? "1" : "0");
    Serial.println(message);
  }

  // Listen message from the ESP8266
  if (Serial.available() > 0)
  {
    String duration = Serial.readString();
    if (hasWater && duration.startsWith("D")) {
      int durationTime = duration.substring(1).toInt() * 1000;
      // Start watering
      digitalWrite(WATER_VALVE_PIN, LOW);
      wateringTimeRemaining = durationTime;
    }
  }

  // Wait
  delay(333);

  if (wateringTimeRemaining > 0) {
    wateringTimeRemaining -= 333;
  }
}
