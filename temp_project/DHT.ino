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
#define ADC0 0
/********************************( Definieren der Objekte )********************************/                          
DHT dht(DHTPIN, DHTTYPE);

//LiquidCrystal_I2C lcd(0x27,16,2); 

/*global var*/
int ADC_value;    //resistance
float hum_dht11, temp_dht11;  //

int overtempLED=13;

/*global funcions*/

void func_overtemp(float temp){
  float overtemp=25; //°C
  
  if (temp>overtemp) digitalWrite(overtempLED,HIGH);
  if (temp<overtemp) digitalWrite(overtempLED,LOW);
  
}

float temp_calc(float R){
  float temp;
  /*
  float B = 4050;  //3500 //3950
  float RN= 4.7;   //kOhm
  float TN=298.15; //K
  float K2C = 273.15;
  
  temp=1.0/( (1.0/TN) + (1.0/B)*log(R/RN) );
  */
  float cal=6.8, offset=296;
  temp = (R-offset)/cal;
  
  return temp;// - K2C;
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
  
/*********************( Überprüfen ob alles richtig Ausgelesen wurde )*********************/
  /*if (isnan(hum_dht11) || isnan(temp_dht11) || isnan(ADC_value) || ADC_value == 0) {       
    Serial.println("Fehler beim auslesen des Sensors!");
    return;
  }*/

  // Nun senden wir die gemessenen Werte an den PC dise werden wir im Seriellem Monitor sehen
    Serial.print(hum_dht11);                   // Ausgeben der Luftfeuchtigkeit
    Serial.print(";");              
    Serial.print(temp_dht11);                  // Ausgeben der Temperatur
    Serial.print(";");
    Serial.print(ADC_value);
    Serial.print(";");              
    Serial.print(temp_calc(ADC_value));
    Serial.println(";");
    func_overtemp(temp_calc(ADC_value));
}
