// Real Time Clock (RTC)

#include "RTClib.h"

RTC_DS3231 rtc;

char* daysOfTheWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void setup() {
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        abort();
    }
    
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");

        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}


void loop() {
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");




    // get temperature
    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");
}
