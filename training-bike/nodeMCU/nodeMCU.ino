int HEART_BEAT_SENSOR_PIN = A0;
int PEDAL_PIN = D5;
int BUTTON_PIN = D6;

void setup() {
  Serial.begin(9600);
  pinMode(PEDAL_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  int heartbeat = analogRead(HEART_BEAT_SENSOR_PIN);
  int hasDonePedalTurn = digitalRead(PEDAL_PIN) == LOW;
  int buttonPressed = digitalRead(BUTTON_PIN) == LOW;

  Serial.print("heartbeat ");
  Serial.print(heartbeat);
  Serial.print(" done turn ");
  Serial.print(hasDonePedalTurn);
  Serial.print(" button ");
  Serial.print(buttonPressed);
  Serial.println("");

  delay(333);
}
