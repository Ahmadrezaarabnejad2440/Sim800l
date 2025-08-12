#include <SoftwareSerial.h>

#define SIM800_TX_PIN D7
#define SIM800_RX_PIN D8

SoftwareSerial sim800l(SIM800_TX_PIN, SIM800_RX_PIN);

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);

  delay(2000);

  Serial.println("Initializing SIM800L...");
  sendATCommand("AT\r\n");  // Check the presence of the module
  delay(2000);

  Serial.println("Setting SMS mode...");
  sendATCommand("AT+CMGF=1\r\n");  // Set SMS mode
  delay(2000);

  // Comment out or remove the following line if setting SMSC is not necessary
  Serial.println("Setting SMSC number...");
  // sendATCommand("AT+CSCA=\"+9891100500\"\r\n");//شماره مرکز پیامک ایرانسل یا همراه اول 
  sendATCommand("AT+CSCA=\"+989101000444\"\r\n");//شماره مرکز پیامک ایرانسل یا همراه اول 
  delay(2000);

  Serial.println("Sending SMS...");
  sendSMS("+989382631065", "slam");  // Set recipient number and message
}

void loop() {
  // Other operations
}

void sendATCommand(String command) {
  sim800l.println(command);
  delay(2000);
  while (sim800l.available()) {
    String response = sim800l.readString();
    Serial.println(response);  // Print responses for debugging
  }
}

void sendSMS(String recipient, String message) {
  sim800l.print("AT+CMGS=\"");
  sim800l.print(recipient);
  sim800l.print("\"\r\n");
  delay(2000);

  sim800l.print(message);
  sim800l.write(26);
  delay(2000);

  while (sim800l.available()) {
    String response = sim800l.readString();
    Serial.println(response);  // Print responses for debugging
  }
}
