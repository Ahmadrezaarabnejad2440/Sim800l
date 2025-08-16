#include <SoftwareSerial.h>

// تعریف پین‌های Rx و Tx برای اتصال به ماژول SIM800L
SoftwareSerial sim800l(7, 8); // Rx, Tx

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
  setupGPRS()
}

void loop() {
  // اتصال به شبکه
  sim800l.println("AT+HTTPINIT");
  delay(1000);
  sim800l.println("AT+HTTPPARA=\"CID\",1");
  delay(1000);

  // تنظیم URL سرور
  sim800l.println("AT+HTTPPARA=\"URL\",\"your_server_url_here\"");
  delay(1000);

  // ارسال درخواست POST به سرور
  sim800l.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(1000);
  sim800l.println("AT+HTTPDATA=50,10000");
  delay(1000);
  sim800l.println("{\"key\":\"value\"}"); // داده‌های ارسالی به سرور
  delay(1000);
  sim800l.println("AT+HTTPACTION=1");
  delay(15000);

  // خاموش کردن اتصال HTTP
  sim800l.println("AT+HTTPTERM");
  delay(3000);

  delay(60000); // تاخیر 60 ثانیه برای ارسال هر درخواست
}


void setupGPRS() {
  // تنظیمات APN بستگی به اپراتور شبکه می‌تواند متفاوت باشد
  sim800l.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(1000);
  sim800l.println("AT+SAPBR=3,1,\"APN\",\"your_APN_here\"");
  delay(1000);
  sim800l.println("AT+SAPBR=1,1");
  delay(3000);
}
