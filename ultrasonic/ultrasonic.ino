// define PINs
#define PIN_TRIGGER 12 // Pin number to send a signal
#define PIN_ECHO    13 // Pin number to receive a signal
// constant variables
#define ZEROCNK 273.15
#define U0 331.3       // Speed of Sound at 0C
const int SENSOR_MAX_RANGE = 300; // in cm

// variables
unsigned long duration;
float distance;
float speedofsound = U0;

float calc_speedofsound(float temp){
  /*
   * Parameter:
   * temp : temperature in C
   * Returns:
   * Speed of Sound in m/s
   */
  return U0 + (0.5955 * temp);
}

float calc_distance(unsigned long duration, float speedofsound){
    /*
   * Parameter:
   * duration : duration in microsecounds
   * speedofsound : Speed of Sound in m/s
   * Returns:
   * distance in cm
   */
   return 0.5*( (float) duration * (speedofsound/10000));
}

void setup(){
  Serial.begin(9600); // start serial monitor/ouput
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop(){
  
  speedofsound = calc_speedofsound(20);

  // transmitter off
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(5);

  // send signal for 10 seconds
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  distance = calc_distance(duration, speedofsound);

  if (distance > SENSOR_MAX_RANGE || distance <= 0){
    Serial.println("Out of sensor range!");
  } else {
    Serial.println("Distance to object: " + String(distance) + " cm");
  }

  delay(1000);
}
