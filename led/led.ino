// Define the pin connected to the LED
const int ledPin = 13;

void setup() {
  // Set the LED pin into output mode
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  delay(1000); // Wait for 1 second (1000 milliseconds)

  // Turn the LED off
  digitalWrite(ledPin, LOW);
  delay(1000); // Wait for 1 second (1000 milliseconds)
}
