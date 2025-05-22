// Pin Definitions
const int buzzerPin = 10;
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin,    OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Turn on the LED and activate the buzzer
  digitalWrite(ledPin,   HIGH);
  // Comment out the line below this one to silence the buzzer
  analogWrite(buzzerPin, 127);
  

  // Wait one second
  delay(1000);

  // Turn off the LED and buzzer
  analogWrite(buzzerPin,   0);
  digitalWrite(ledPin,   LOW );

  // Wait one second
  delay(1000);
}
