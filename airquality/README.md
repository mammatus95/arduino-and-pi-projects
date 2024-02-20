# Air Quality

## Example Sketch

```C

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

```

**Components**
- MQ-135 Sensor : https://github.com/GeorgK/MQ135/blob/master/MQ135.h

**Circuit**
#![Circuit](circuit/.png)


