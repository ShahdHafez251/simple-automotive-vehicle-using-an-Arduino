#include <NewPing.h>

// Motor Pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

// Ultrasonic Sensor Pins
#define trig_pin A1 // analog input 1
#define echo_pin A2 // analog input 2
#define maximum_distance 200

// Control Variables
boolean goesForward = false;
int distance_forward = 0;
int rotated_distance = 0;

NewPing sonar(trig_pin, echo_pin, maximum_distance); // Ultrasonic sensor object

void setup() {
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
}
void loop() {
  distance_forward = readPing(); // Read forward distance

  if (distance_forward <= 50) {
    moveStop(); // Stop the car

    // Look right and sense the distance
    rotated_distance = readPing_rotated();
    delay(100);

    // Look left and sense the distance
    if (distance_forward >= rotated_distance) {
      rotation();
      delay(100);
    }
  } else {
    // Move forward
    moveForward();
  }
}
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

int readPing_rotated() {
  // Move right and sense the distance
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(250);

  int cm = readPing();

  // Move back to the center position
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(250);

  return cm;
}
void moveStop() {
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() {
    goesForward = true;
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
}

void rotation() {
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, HIGH);
    delay(250);
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
}