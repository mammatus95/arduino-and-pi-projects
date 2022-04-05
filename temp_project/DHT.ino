/*******************************************************************************************
 *******************************************************************************************
 **                                www.bastelgarage.ch                                    **    
 ** Der Onlineshop mit Videoanleitungen und kompletten Bausätzen für Anfänger und Profis! **  
 *******************************************************************************************
 *******************************************************************************************
 ** Mit diesem einfachen Testprogramm möchten wir dir zeigen wie einfach du mit einem     **
 ** Arduino UNO die Temperatur und Luftfeuchtigkeit eines DHT11 oder DHT22 Sensors        ** 
 ** auslessen kanns.                                                                      **
 **                                                                                       **
 ** Autor: Philippe Keller                                                                **
 ** Datum: April 2016                                                                     **
 ** Version: 1.1                                                                          **
 ** Edit:                                                                                 **
 ** Morten Kretschmer  Oktober 2021  add capacity/resistance temperature measurement and  **
 **                                  serial output
 * *****************************************************************************************
*/

/************************( Importieren der genutzten Bibliotheken )************************/
#include "DHT.h"
#include "Wire.h" 
//#include "LiquidCrystal_I2C.h"

#define DHTPIN 2          // Hier die Pin Nummer eintragen wo der Sensor angeschlossen ist
#define DHTTYPE DHT11     // Hier wird definiert was für ein Sensor ausgelesen wird. In 
                          // unserem Beispiel möchten wir einen DHT11 auslesen, falls du 
                          // ein DHT22 hast einfach DHT22 eintragen
#define ADC0 0            // Analog pin für ntc
#define ZEROCNK 273.15    // Zero Celsius in Kelvins
#define MAXANALOGREAD 1023.0

#define T0 298.15         // Nenntemperatur des NTC-Widerstands in K
#define R0 4700.0         // Nennwiderstand des NTC-Sensors in Ohm
#define RV 4000.0         // Vorwiderstand in Ohm 

/********************************( Definieren der Objekte )********************************/                          
DHT dht(DHTPIN, DHTTYPE);

/*global var*/
int ADC_value;
float resistance, temp_ntc;
float hum_dht11, temp_dht11;

int overtempLED=13;


/*global funcions*/

void func_overtemp(float temp){
  float overtemp=25; //°C
  
  if (temp>overtemp) digitalWrite(overtempLED,HIGH);
  if (temp<overtemp) digitalWrite(overtempLED,LOW);
  
}

float calc_resistance(float VA_VB){
  /*
  VB : Betriebsspannung des Arduino (irgendwo bei ca. 5V)
  RV : Vorwiderstand
  RN : Widerstand des NTC (temperaturabhängig!)
  VA : Spannung am Arduino-Messeingang
  VA_VB : Spannungsverhältnis "Spannung am NTC zu Betriebsspannung"
  Returns:
  RN = Widerstand des NTC (temperaturabhängig!)

  How:
  Dann gilt jeweils das Ohmsche Gesetz (U=R*I):

  VA = RN*I
  VB = (RV+RN)*I |Gleichungen dividieren

  VA/VB= (RN*I)/((RV+RN)*I) |I kürzen

  VA/VB= RN/(RV+RN) |*(RV+RN)

  VA/VB*(RV+RN)= RN |weiter umformen

  RV*VA/VB + RN*VA/VB = RN

  RV*VA/VB = RN - RN*VA/VB

  RV*VA/VB = RN*(1-VA/VB) |:(1-VA/VB)
 
  RN= RV*VA/VB / (1-VA/VB) ==> Formel für den Widerstand des NTC-Widerstands!

  */
  float RN = RV*VA_VB / (1-VA_VB); // aktueller Widerstand des NTC
  return RN;
}

float temperature_NTCB(float B, float RN){
  /*
  Ermittlung der Temperatur mittels NTC-Widerstand
  Version der Funktion bei gegebener Materialkonstante B
  Erklärung der Parameter:
  RN : Widerstand des NTC (temperaturabhängig!)
  T0 : Nenntemperatur des NTC-Widerstands in K
  R0 : Nennwiderstand des NTC-Sensors in Ohm
  B  : Materialkonstante B
  Returs:
  -------
  Rückgabewert : Temperatur in C
  */
 
  return (T0 * B) / (B + T0 * log(RN / R0)) -ZEROCNK;
}



void setup() {
  Serial.begin(9600);
  //Serial.println("DHT11 & NHC 4k7 Testprogramm");
  dht.begin();
  pinMode(overtempLED, OUTPUT);
}

void loop() {

  // Wait a few seconds between measurements.
  delay(2000);                     // Hier definieren wir die Verweilzeit die gewartet wird  
                                   // bis der Sensor wieder ausgelesen wird. Da der DHT11  
                                   // auch ca. 2 Sekunden hat um seine Werte zu aktualisieren
                                   // macht es keinen sinn ihn schneller auszulesen!
                                    
  hum_dht11 = dht.readHumidity();     // Lesen der Luftfeuchtigkeit und speichern in die Variable h
  temp_dht11 = dht.readTemperature(); // Lesen der Temperatur in °C und speichern in die Variable t
  ADC_value = analogRead(ADC0);
  resistance = calc_resistance(ADC_value/MAXANALOGREAD); // Calculate resistance
  
  temp_ntc=temperature_NTCB(4050, resistance);

  // Nun senden wir die gemessenen Werte an den PC dise werden wir im Seriellem Monitor sehen
    Serial.print(hum_dht11);                   // Ausgeben der Luftfeuchtigkeit
    Serial.print(";");              
    Serial.print(temp_dht11);                  // Ausgeben der Temperatur
    Serial.print(";");
    Serial.print(resistance);
    Serial.print(";");              
    Serial.print(temp_ntc);
    Serial.println(";");
    func_overtemp(temp_ntc);
}
