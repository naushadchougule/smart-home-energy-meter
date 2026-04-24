#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial espSerial(10, 11);

const int currentPin = A1;
const float sensitivity = 0.1;   // ACS712-20A: 100mV/A
const float offsetV = 2.5;       // Midpoint voltage
const int SAMPLES = 1000;
const float VOLTAGE = 220.0;     // Mains voltage

String apiKey = "YOUR_THINGSPEAK_API_KEY";
String ssid   = "YOUR_WIFI_NAME";
String pass   = "YOUR_WIFI_PASSWORD";

// Function to calculate RMS current
float readRMSCurrent() {
  float sumSq = 0;
  for (int i = 0; i < SAMPLES; i++) {
    float v = (analogRead(currentPin) * 5.0 / 1023.0) - offsetV;
    sumSq += (v / sensitivity) * (v / sensitivity);
    delayMicroseconds(200);
  }
  return sqrt(sumSq / SAMPLES);
}

// Function to send AT commands
void sendAT(String cmd, int wait = 2000) {
  espSerial.println(cmd);
  delay(wait);
  while (espSerial.available()) {
    Serial.write(espSerial.read());
  }
}

// Upload data to ThingSpeak
void uploadThingSpeak(float I, float P) {
  sendAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");

  String req = "GET /update?api_key=" + apiKey +
               "&field1=" + String(I, 3) +
               "&field2=" + String(P, 1) +
               " HTTP/1.1\r\nHost: api.thingspeak.com\r\n\r\n";

  sendAT("AT+CIPSEND=" + String(req.length()));
  espSerial.print(req);
  delay(1500);
  sendAT("AT+CIPCLOSE");
}

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  lcd.init();
  lcd.backlight();

  sendAT("AT+RST", 3000);
  sendAT("AT+CWMODE=1");
  sendAT("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"", 8000);

  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
}

void loop() {
  float I = readRMSCurrent();
  float P = I * VOLTAGE;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("I=" + String(I, 2) + "A");

  lcd.setCursor(0, 1);
  lcd.print("P=" + String(P, 1) + "W");

  uploadThingSpeak(I, P);

  delay(30000); // 30 seconds delay
}
