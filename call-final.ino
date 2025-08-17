#include <SoftwareSerial.h>

SoftwareSerial mySerial(D7, D8); // RX, TX

void setup() {
  Serial.begin(9600);
  while (!Serial);

  mySerial.begin(9600);
  delay(1000);

  Serial.println("Initializing...");
  delay(5000); // انتظار برای برقراری ارتباط با ماژول

  mySerial.println("ATD+989382631065;"); // شماره تلفن مورد نظر
  delay(10000); // انتظار برای برقراری تماس

  mySerial.println("AT+CMGF=1");    // sets the SMS mode to text
  delay(100);
  mySerial.println("AT+CMGS=\"+989382631065\""); // sets the phone number
  delay(100);
  mySerial.println("Hi, I am Pirooz!"); // the message
}

void loop() {
  

}
