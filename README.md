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
## [#ShowYourStripes](https://showyourstripes.info/s/globe)

<h4 align="center">
  <a href="https://showyourstripes.info/s/europe/germany/all">
    <img src="https://raw.githubusercontent.com/ed-hawkins/show-your-stripes/master/2022/EUROPE-%3CAll%20of%20Europe%3E--1850-2022-BK.png"
         height="50" width="800"
         alt="#showyourstripes Europe 1850-2022"></a>
</h4>

**Graphics and Lead Scientist**: [Ed Hawkins](https://www.met.reading.ac.uk/~ed/home/index.php), National Centre for Atmospheric Science, University of Reading.

**Data**: Berkeley Earth, NOAA, UK Met Office, MeteoSwiss, DWD, SMHI, UoR, Meteo France & ZAMG.

<p>
<a href="https://showyourstripes.info/s/globe">#ShowYourStripes</a> is distributed under a
<a href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>
<a href="https://creativecommons.org/licenses/by/4.0/">
  <img src="https://i.creativecommons.org/l/by/4.0/80x15.png" alt="creative-commons-by" style="border-width:0"></a>
</p>
