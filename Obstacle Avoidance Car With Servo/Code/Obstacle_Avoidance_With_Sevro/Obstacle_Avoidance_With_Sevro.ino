#include <Servo.h>

// Pin Definitions
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 5;
const int IN4 = 6;

// Ultrasonic Sensor Pins
const int trigPin = 13;
const int echoPin = 12;

// Servo Pin
const int servoPin = 9;

// Servo Positions
const int FRONT_POSITION = 90;
const int LEFT_POSITION = 180;
const int RIGHT_POSITION = 0;

// defines variables
long duration;
int distanceFront;
int distanceLeft;
int distanceRight;

// Direction Constants
const int FORWARD = 1;
const int BACKWARD = 0;

// Create Servo Object
Servo myServo;

void setup() {
  // Set all the motor control pins to output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Set the trigPin and echoPin as an Output and Input, respectively
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach the servo to the specified pin
  myServo.attach(servoPin);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Scan surroundings
  scanSurroundings();

  // Decide direction based on distances
  if (distanceFront > 30) {
    forward();
    delay(50);
  } else if (distanceLeft > distanceRight) {
    left();
    delay(50);
  } else {
    right();
    delay(50);
  }
  stop();
  delay(50); // Short pause before the next scan
}

// Function to scan surroundings by moving the servo
void scanSurroundings() {
  // Look front
  myServo.write(FRONT_POSITION);
  delay(500);
  distanceFront = calculateDistance();

  // Look left
  myServo.write(LEFT_POSITION);
  delay(500);
  distanceLeft = calculateDistance();

  // Look right
  myServo.write(RIGHT_POSITION);
  delay(500);
  distanceRight = calculateDistance();

  // Return to front position
  myServo.write(FRONT_POSITION);
}

// Function to calculate the distance using the ultrasonic sensor
int calculateDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  int distance = duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  return distance;
}

// Function to move the car forward
void forward() {
  runMotorA(FORWARD);
  runMotorB(FORWARD);
}

// Function to turn the car left
void left() {
  runMotorA(BACKWARD);
  runMotorB(FORWARD);
}

// Function to turn the car right
void right() {
  runMotorA(FORWARD);
  runMotorB(BACKWARD);
}

// Function to stop the car
void stop() {
  stopMotorA();
  stopMotorB();
}

// Function to run Motor A
void runMotorA(int direction) {
  if (direction == FORWARD) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

// Function to run Motor B
void runMotorB(int direction) {
  if (direction == FORWARD) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

// Function to stop Motor A
void stopMotorA() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// Function to stop Motor B
void stopMotorB() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
