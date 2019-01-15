/*
   Metronome Receiver
   DIGF 6003 Ubiquitous Computing - Kate Hartman & Nick Puckett

   Based on the Physical Pixel example:
   http://www.arduino.cc/en/Tutorial/PhysicalPixel

   Changes:
   - "Serial1" is used to allow the data to be sent via the Arduino Micro hardware serial pins
    to the XBee radio.
   - "makeSomethingHappen" function has been added as a spot to put the response to the metronome.
*/

/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// Static variable to output on Pin 8
const int ledPin = 8;
int incomingByte;      // a variable to read incoming serial data into

// notes in the melody:
int melody[] = {
    NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4, 
    0, 
    NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5, 
    0,  
    NOTE_G4, NOTE_G4, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_A4,
    0,
    NOTE_F5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5
};

// ** ** ** ** SONAR VARIABLES ** ** ** ** ** //
//  NOTE_A3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G5


// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8, 16, 4, 4, 4, 2,
  8,
  8, 16, 4, 4, 4, 2,
  8,
  8, 16, 4, 4, 4, 4, 2,
  8,
  8, 16, 4, 4, 4, 2
//  4, 4, 4, 4, 4, 4, 4, 4, 4, 4
  //4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  // initialize serial communication:
  Serial1.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // see if there's incoming serial data:
  if (Serial1.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial1.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      digitalWrite(ledPin, HIGH);
      happyBirthday();
      delay(2000);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(ledPin, LOW);
    }
  }
}

void happyBirthday() {
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 28; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }
}
