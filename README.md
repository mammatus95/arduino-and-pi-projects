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
 void setup() { // put your setup code here, to run once:
   // Set LED pin into output mode
   pinMode(LED_BUILTIN, OUTPUT);
 }

 void loop() { // put your main code here, to run repeatedly:
   digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on
   delay(1000);                       // wait one second
   digitalWrite(LED_BUILTIN, LOW);    // Turn the LED on
   delay(1000);                       // wait one second
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

## Install Conda environment

```bash
conda env create -f environment.yml

conda activate pipy
```
