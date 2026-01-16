#include <Arduino.h>
#include <DHT.h>
#include "NewPing.h"
#include <ESP32Servo.h>

// define DHT11 sensor pin
#define DHT_PIN   4

#define DHT_TYPE DHT11
DHT dht11(DHT_PIN, DHT_TYPE);

//define pins (only available pins on development board: 1/2/4/5/6/7/15/16)
#define LED 1
#define TRIG_PIN 5
#define ECHO_PIN  6
#define BUZZER_PIN 35
#define Servo_PIN 7

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// create servo object
Servo servo;



void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  // initialize the DHT11 sensor
  dht11.begin();
  //attach servo pin
  servo.attach(Servo_PIN);
  // config the pin mode of each pin
  pinMode(LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // initialize servo to stopped position
  servo.write(0);
  // ensure LED and buzzer are off initially
  digitalWrite(LED, LOW);
  noTone(BUZZER_PIN);
}

void loop() {

  // read humidity
  float humi  = dht11.readHumidity();
  // read temperature in Celsius
  float tempC = dht11.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht11.readTemperature(true);

  // check whether the reading is successful or not
  if (isnan(tempC) || isnan(tempF) || isnan(humi)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else if (tempC <= 30) {

      // servo motor stop
      servo.write(90);
      // Serial Monitor show Safe
      Serial.println("Safe: Temperature <= 30°C");
      // buzzer no sound
      noTone(BUZZER_PIN);
      digitalWrite(LED, LOW);
  } else if (humi >= 30) {
      // servo motor stop
      servo.write(0);
      // Serial Monitor show Caution
      Serial.println("Caution: Humidity >= 30%");
      // buzzer continuously alarm
      tone(BUZZER_PIN, 1000);
      digitalWrite(LED, HIGH);
      // report heat source distance from Ultrasonic sensor
      delay(50);
      unsigned int distance = sonar.ping_cm();
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
    else if (humi < 30)  {
      // servo motor run
      servo.write(0);
      // Serial Monitor show Dangerous
      Serial.println("Dangerous: Humidity < 30%");
      // buzzer beep
      tone(BUZZER_PIN, 2000);
      delay(100);
      noTone(BUZZER_PIN);
      delay(100);
      digitalWrite(LED, HIGH);
  }
  

  // wait a 2 seconds between readings
  delay(2000);
}
