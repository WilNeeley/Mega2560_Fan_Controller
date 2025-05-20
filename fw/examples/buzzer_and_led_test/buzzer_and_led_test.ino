const int buzzerPin = 10;
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin,    OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(buzzerPin, 127);
  digitalWrite(ledPin,   HIGH);
  delay(1000);
  analogWrite(buzzerPin,   0);
  digitalWrite(ledPin,   LOW );
  delay(1000);
}
