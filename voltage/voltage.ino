// define PINs
#define SENSOR_PIN        A0
#define OPERATING_VOLTAGE 5.0f
const float R1 = 30000.0f; // resistance one as port of the sensor
const float R2 = 7500.0f;  // resistance two as part of the sensor
const float MAX_VIN = OPERATING_VOLTAGE;

void setup(){
   Serial.begin(9600);

   pinMode(SENSOR_PIN, INPUT);
}

void loop(){
  float vin = analogRead(SENSOR_PIN) * (MAX_VIN / 1024.0f);
  // U = (U2 * (R1 + R2)) / R2
  float valc = (vin * (R1 + R2)) / R2;
   
  Serial.print("Eingangsspannung: ");
  Serial.print(valc, 2);
  Serial.println("V");

  delay(500);
}
