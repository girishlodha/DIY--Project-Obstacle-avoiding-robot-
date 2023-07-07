#include <NewPing.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

SoftwareSerial bluetooth(2, 3);  // Bluetooth RX (2) and TX (3) pins

int motor1Pin1 = 4;  // Motor 1 control pin 1
int motor1Pin2 = 5;  // Motor 1 control pin 2
int motor2Pin1 = 6;  // Motor 2 control pin 1
int motor2Pin2 = 7;  // Motor 2 control pin 2

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  bluetooth.begin(9600);  // Set the baud rate for Bluetooth communication
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopMoving() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(500);
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(500);
}

void parseVoiceCommand(String command) {
  if (command == "forward") {
    moveForward();
  } else if (command == "backward") {
    moveBackward();
  } else if (command == "stop") {
    stopMoving();
  } else if (command == "left") {
    turnLeft();
  } else if (command == "right") {
    turnRight();
  }
}

void loop() {
  // Check if there is any incoming data from Bluetooth
  if (bluetooth.available()) {
    String command = bluetooth.readStringUntil('\n');
    parseVoiceCommand(command);
  }

  unsigned int distance = sonar.ping_cm();

  if (distance > 0 && distance <= 10) {
    stopMoving();
    delay(500);
    turnRight();
  } else {
    moveForward();
  }
}
