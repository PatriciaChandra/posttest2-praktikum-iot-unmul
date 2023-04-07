#include <ESP8266WiFi.h> 
#include <ThingerESP8266.h>

#define USERNAME "AcunCia"
#define DEVICE_ID "posttest_2"
#define DEVICE_CREDENTIAL "H9EWNOC9IUmmutV$"

#define SSID "Universitas Mulawarman" //Hotspot yang kita pakai
#define SSID_PASSWORD ""

#define TRIGGER_PIN D2
#define ECHO_PIN D3
#define BUZZER_PIN D5
#define LED_PIN D4

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["distance"] >> [](pson& out){
    out = measure_distance();
  };
}


void loop() {
  thing.handle();
}

int measure_distance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance < 30) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  return distance;
}
