#include <AFMotor.h>
#include <TimerFreeTone.h>
#include "pitches.h"

#define SPEAKER_PIN 2

AF_DCMotor motorFL(1, MOTOR34_1KHZ);
AF_DCMotor motorBL(2, MOTOR34_1KHZ);
AF_DCMotor motorBR(3, MOTOR34_1KHZ);
AF_DCMotor motorFR(4, MOTOR34_1KHZ);

char instruction;
bool singing = false;
unsigned long noteStartTime = 0;
int currentNote = 0;

void setup() {
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);

  // Connect the speaker on pin SPEAKER_PIN
  pinMode(SPEAKER_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    instruction = Serial.read();
    // Serial.print("Received instruction: ");
    // Serial.println(instruction); // Debug output for received instruction
    switch (instruction) {
      case 'U':
        forward();
        break;
      case 'D':
        backward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'S':
        startSong();
        break;
      case '0':
        stop();
        break;
      case 'Y':
        motorFR.setSpeed(255);
        motorFR.run(FORWARD);
        break;
      case 'X':
        motorFL.setSpeed(255);
        motorFL.run(FORWARD);
        break;
      case 'B':
        motorBR.setSpeed(255);
        motorBR.run(FORWARD);
        break;
      case 'A':
        motorBL.setSpeed(255);
        motorBL.run(FORWARD);
        break;
    }
  }

  if (singing) {
    playSong();
  }
}

void startSong() {
  singing = true;
  currentNote = 0;
  noteStartTime = millis();
  stop();  // Stop motors before playing the song
}

void playSong() {
  unsigned long currentTime = millis();
  if (currentNote < notes * 2) {
    if (currentTime - noteStartTime >= noteDuration) {
      // Stop the previous note
      TimerFreeTone(SPEAKER_PIN, 0, 0);

      // Proceed to the next note
      divider = pgm_read_word_near(melody + currentNote + 1);
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // Increase the duration in half for dotted notes
      }

      // Play the note for 90% of the duration, leaving 10% as a pause
      TimerFreeTone(SPEAKER_PIN, pgm_read_word_near(melody + currentNote), noteDuration * 0.9);

      // Set the start time for the next note
      noteStartTime = currentTime;
      currentNote += 2;
    }
  } else {
    // Song is finished
    singing = false;
    TimerFreeTone(SPEAKER_PIN, 0, 0); // Ensure the tone is turned off
  }
}

void forward() {
  // Serial.println("Moving forward"); // Debug output
  motorFL.setSpeed(255);
  motorFL.run(FORWARD);
  motorBL.setSpeed(255);
  motorBL.run(FORWARD);
  motorBR.setSpeed(255);
  motorBR.run(FORWARD);
  motorFR.setSpeed(255);
  motorFR.run(FORWARD);
}

void backward() {
  // Serial.println("Moving backward"); // Debug output
  motorFL.setSpeed(255);
  motorFL.run(BACKWARD);
  motorBL.setSpeed(255);
  motorBL.run(BACKWARD);
  motorBR.setSpeed(255);
  motorBR.run(BACKWARD);
  motorFR.setSpeed(255);
  motorFR.run(BACKWARD);
}

void left() {
  // Serial.println("Turning left"); // Debug output
  motorFL.setSpeed(255);
  motorFL.run(BACKWARD);
  motorBL.setSpeed(255);
  motorBL.run(BACKWARD);
  motorBR.setSpeed(255);
  motorBR.run(FORWARD);
  motorFR.setSpeed(255);
  motorFR.run(FORWARD);
}

void right() {
  // Serial.println("Turning right"); // Debug output
  motorFL.setSpeed(255);
  motorFL.run(FORWARD);
  motorBL.setSpeed(255);
  motorBL.run(FORWARD);
  motorBR.setSpeed(255);
  motorBR.run(BACKWARD);
  motorFR.setSpeed(255);
  motorFR.run(BACKWARD);
}

void stop() {
  // Serial.println("Stopping all motors"); // Debug output
  motorFL.setSpeed(0);
  motorFL.run(RELEASE);
  motorBL.setSpeed(0);
  motorBL.run(RELEASE);
  motorBR.setSpeed(0);
  motorBR.run(RELEASE);
  motorFR.setSpeed(0);
  motorFR.run(RELEASE);
  // Serial.println("All motors stopped"); // Debug confirmation
}
