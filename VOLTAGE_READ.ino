void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  float volts = sensorValue*(5.0/1023.0);
  Serial.println(volts);
  delay(1000); 
}
