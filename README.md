# arduino-and-pi-projects

## Install Arduino IDE

```bash
sudo snap install arduino
```
Run this command, as well:
```bash
sudo usermod -a -G dialout $USER
```
## Programming with Arduino IDE

- Select Your Board: Go to `Tools > Board` and select the Arduino board model you are using.
- Select Your Port: `Tools > Port`


```C
// Define the pin connected to the LED
const int ledPin = 13;

void setup() {
  // Set the LED pin as an output
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
```

- Verify/Compile Your Sketch
- Upload Your Sketch
- Open the Serial Monitor (Optional)

Take look on the led subfolder for more details about the circuit.

## Install Raspberry Pi OS

https://www.raspberrypi.com/software/

```bash
sudo apt install rpi-imager
```
