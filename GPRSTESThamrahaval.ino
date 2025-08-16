#include <SoftwareSerial.h>

// تعریف پین‌های Rx و Tx برای اتصال به ماژول SIM800L
SoftwareSerial sim800l(D7, D8);  // Rx, Tx

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  // ارسال دستورات تنظیمات برای SIM800L
  sim800l.println("AT");
  delay(1000);
  sim800l.println("AT+CPIN?");
  delay(1000);
  sim800l.println("AT+CREG?");
  delay(1000);
  sim800l.println("AT+CGATT?");
  delay(1000);

  // تنظیمات APN بستگی به اپراتور شبکه می‌تواند متفاوت باشد
  sim800l.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(1000);
  sim800l.println("AT+SAPBR=3,1,\"APN\",\"mtnirancell\"");  //irancell
  // sim800l.println("AT+SAPBR=3,1,\"APN\",\"mciwip\""); // hamrahaval
  delay(1000);
  sim800l.println("AT+SAPBR=1,1");
  delay(3000);
  Serial.println("ready");
  GPRSGET("kir%to%hamechi");
}

void loop() {
  while (true) {
    if (Serial.available()) {
      GPRSGET(Serial.readString());
    }
  }
}

void GPRSGET(String message) {
  // اتصال به شبکه
  Serial.print("sending ");
  Serial.println(message);

  sim800l.println("AT+HTTPINIT");
  delay(1000);
  sim800l.println("AT+HTTPPARA=\"CID\",1");
  delay(1000);

  // تنظیم URL سرور
  String URL = String("http://pirooztech.freehost.io/?message=" + message + "/");
  // String URL = "http://pirooztech.freehost.io/?message=kir%khar/";
  // Serial.println(URL);
  // Serial.println("AT+HTTPPARA=\"URL\",\"" + URL + "\"");
  sim800l.println("AT+HTTPPARA=\"URL\",\"" + URL + "\"");
  // sim800l.println("AT+HTTPPARA=\"URL\",\"http://pirooztech.freehost.io/?message=kir/"); // بدون سریال مانیتور
  // while (sim800l.available()) {
  //   Serial.write(sim800l.read());
  // }
  delay(1000);  // انتظار برای پاسخ ماژول

  delay(1000);

  // ارسال درخواست GET به سرور
  sim800l.println("AT+HTTPACTION=0");
  delay(15000);

  // خاموش کردن اتصال HTTP
  sim800l.println("AT+HTTPTERM");
  delay(3000);
  Serial.println("send");

  delay(60000);  // تاخیر 60 ثانیه برای ارسال هر درخواست
}
