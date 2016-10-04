
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  while(!Serial);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("lkkk");
  delay(500);
}
