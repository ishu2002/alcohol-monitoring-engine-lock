#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(7, 8);
int alcoholPin = A0;
int relayPin = 9;
int alcoholValue = 0;
int threshold = 400;

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
  gsmSerial.begin(9600);
  delay(1000);
  sendSMS("Alcohol Detection System is Active");
}

void loop() {
  alcoholValue = analogRead(alcoholPin);
  if (alcoholValue > threshold) {
    digitalWrite(relayPin, LOW);
    sendSMS("Alcohol detected! Engine locked.");
    Serial.println("Alcohol detected! Engine locked.");
  } else {
    digitalWrite(relayPin, HIGH);
    Serial.println("No alcohol detected. Engine unlocked.");
  }
  delay(1000);
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1");
  delay(100);
  gsmSerial.println("AT+CMGS=\"+1234567890\"");
  delay(100);
  gsmSerial.println(message);
  delay(100);
  gsmSerial.write(26);
  delay(1000);
}
