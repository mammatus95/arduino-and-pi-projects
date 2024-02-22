#define PIN_INPUT 0 // Pin number of input
int Sensorwert;

void setup(){
  Serial.begin(9600);
  pinMode( PIN_INPUT , INPUT);
}

void loop(){
  Sensorwert = analogRead(PIN_INPUT);
  Serial.print("Der erfasste Wert lautet : "); 
  Serial.println(Sensorwert, DEC);
  Serial.println();

  delay(1000);                        
} 
