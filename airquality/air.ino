int Sensorwert;

void setup(){
  Serial.begin(9600);
  pinMode( 0 , INPUT);
}

void loop(){
      Sensorwert = analogRead(0);
      Serial.print("Der erfasste Wert lautet : "); 
      Serial.println(Sensorwert, DEC);
      Serial.println();

  delay(1000);                        
} 

