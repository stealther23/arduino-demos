#include <TonePlayer.h>
#include "pitches.h"
#include "IRremote.h"
#include <elapsedMillis.h>

boolean gameRunning;
int lightOnInterval = 2000;
int score;

int LED_BLUE = 4;   // pin 4
int LED_YELLOW = 5; // pin 5
int LED_RED = 6;    // pin 6
int lights[] =  {LED_BLUE, LED_YELLOW, LED_RED};

TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L);

elapsedMillis timeElapsed;
elapsedMillis lightTimer;

IRrecv irrecv(2); // IR Receiver

decode_results results;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int melodyGameStart[] = {
  NOTE_G3, 0, NOTE_C4, NOTE_C4, NOTE_GS2
};

int noteDurationsStart[] = {
  4, 8, 8, 4, 4
};

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(9, OUTPUT); // speaker
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  playToneGameStart();
  lightTimer = 0;
  gameRunning = true;
  score = 0;
}

void loop() {
  if (!gameRunning) {
    return;
  }
  
  if (lightTimer >= lightOnInterval) {
    lightTimer = lightTimer - lightOnInterval;
    lightOnInterval = (lightOnInterval >= 500) ? (lightOnInterval - 100) : 500;
    lightOn();
  }
  // watch IR sensor input
  /* you can use any codes you want to,
   these are just the codes I used 
   that worked for my remote */
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 16728765:
        pressedButton(LED_BLUE);
        break;
      case 16730805:
        pressedButton(LED_YELLOW);
        break;
      case 16724175:
        pressedButton(LED_RED);
        break;
      default:
        break;
    }
    irrecv.resume(); // Receive the next IR value
  }
  // wait between 0.8 - 1.5s for the player to act
  int wait = rand()%((1500 - 800) + 1) + 800; 
  if (timeElapsed > wait) {
    if (digitalRead(LED_BLUE) == HIGH and digitalRead(LED_YELLOW) == HIGH and digitalRead(LED_RED) == HIGH) {
      playToneGameOver();
      Serial.print("Final score: ");
      Serial.println(score);
      gameRunning = false;
    }
  }
}

void lightOn() {
  int light = rand()%((4 - 1) + 1);
  if (!checkLight(lights[light])) {
    digitalWrite(lights[light], HIGH);
  } else {
    lightOn();
  }
}

boolean checkLight(int light) {
  return digitalRead(light) == HIGH;
}

void pressedButton(int led) {
  if (checkLight(led)) {
    digitalWrite(led, LOW);
    timeElapsed = 0;
    increaseScore();
    playToneCorrect();
  } else {
    playToneWrong();  
  }
}

void increaseScore() {
  score++;
  Serial.print("Score: ");
  Serial.println(score);
}

void playToneWrong() {
  tone1.tone(NOTE_FS2);
  delay(100);
  tone1.noTone();
}

void playToneCorrect() {
  tone1.tone(NOTE_C4);
  delay(100);
  tone1.noTone();
}

void playToneGameOver() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone1.tone(melody[thisNote]);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    tone1.noTone();
  }
}

void playToneGameStart() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 5; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurationsStart[thisNote];
    tone1.tone(melodyGameStart[thisNote]);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    tone1.noTone();
  }
}


