/* replace ? and add code in ???*/
#include "pitches.h"
#include "Arduino.h"
#include "NewPing.h"

// define ultrasonic pins
#define TRIG_PIN   9
#define ECHO_PIN    10

// define buzzer pin (built-in on development board)
#define BUZZER_PIN  36

//Define Built-in LED pin (LED1 on development board)
#define LED 1

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

//*** Define distance as a variable ***
float distance;  

//jingle bells high_tone

int melody_high[] = {
  
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
  NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4,
  NOTE_D4, NOTE_G4
};

int noteDurations_high[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8, 2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};
  //jingle bells LOW
int melody_low[] = {

  NOTE_E3, NOTE_E3, NOTE_E3,
  NOTE_E3, NOTE_E3, NOTE_E3,
  NOTE_E3, NOTE_G3, NOTE_C3, NOTE_D3, NOTE_E3,
  NOTE_F3, NOTE_F3, NOTE_F3, NOTE_F3,
  NOTE_F3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3,
  NOTE_E3, NOTE_D3, NOTE_D3, NOTE_E3,
  NOTE_D3, NOTE_G3
};

int noteDurations_low[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8, 2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};


void setup() {

  // initialize serial monitor
  Serial.begin(9600);
  
  // set pins mode
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
}

void loop() {
  // Get the distance from the Ultrasonic Sensor
  float distance = sonar.ping_cm();

  if (distance > 10 ) {
    // turn on built in LED
    digitalWrite(LED_PIN, HIGH);
    noTone(BUZZER_PIN);
  } else if (distance <= 10 && distance >= 5) {
    // turn off built in LED
    digitalWrite(LED_PIN, LOW);
    // play high tone Jingle-Bells Iterate over the notes of the melody_high:
    for (int thisNote = 0; thisNote < 24; thisNote++) {
      int noteDuration = 1000 / noteDurations_high[thisNote];
      tone(BUZZER_PIN, melody_high[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZER_PIN);
    }
  } else if (distance < 5 ) {
    // turn off built in LED
    digitalWrite(LED_PIN, LOW);
    // play low tone Jingle-Bells Iterate over the notes of the melody_low
    for (int thisNote = 0; thisNote < 24; thisNote++) {
      int noteDuration = 1000 / noteDurations_low[thisNote];
      tone(BUZZER_PIN, melody_low[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZER_PIN);
    }
  }
  delay(100);
}
