// Define the pin connected to the LED
#define PIN_LED 13 // Pin number of connection to LED

void setup() {
  // Set the LED pin into output mode
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(PIN_LED, HIGH);
  delay(1000); // Wait for 1 second (1000 milliseconds)

  // Turn the LED off
  digitalWrite(PIN_LED, LOW);
  delay(1000); // Wait for 1 second (1000 milliseconds)
}
