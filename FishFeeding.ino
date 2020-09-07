#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>
const char *ssid = "redmi";
const char *password = "12340987";
Servo motor1;
const long utcOffsetInSeconds = 3600;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday","Thursday",
"Friday", "Saturday"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
void setup(){
Serial.begin(115200);
delay(10);
motor1.attach(D1);
WiFi.begin(ssid, password);
while ( WiFi.status() != WL_CONNECTED ) {
delay ( 500 );
Serial.print ( "WIFI NOT CONNECTED" );
}
timeClient.begin();
}
void loop() {
timeClient.update();
int hour = timeClient.getHours();
int min = timeClient.getMinutes();
int second = timeClient.getSeconds();
Serial.print(daysOfTheWeek[timeClient.getDay()]);
Serial.print(", ");
Serial.print(hour);
Serial.print(":");
Serial.print(min);
Serial.print(":");
Serial.print(second);
if((hour == 7 && min == 16 && second == 55) || (hour == 7 && min == 16 && second ==
56 ) ){
motor1.write(180);
delay(500);
motor1.write(0);
}
else{
motor1.write(0);
}
}
delay(1000);
}
